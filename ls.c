#include "ls.h"

// -t -r 
int compare_time(const void *a, const void *b) {
    struct dirent *entryA = *(struct dirent **)a;
    struct dirent *entryB = *(struct dirent **)b;

    struct stat statA, statB;
    stat(entryA->d_name, &statA);  // 获取文件状态
    stat(entryB->d_name, &statB);  

    return difftime(statA.st_mtime, statB.st_mtime);  // 比较修改时间
}

// -l
struct passwd {
    char *pw_name;  // 用户名
};

struct group {
    char *gr_name;  // 组名
};
 struct passwd *getpwuid(uid_t uid);
 struct group *getgrgid(gid_t gid);

void print_long_format(struct dirent *entry, const char *path, int show_size, int show_inode, int show_long) {
    struct stat file_stat;
    char full_path[512];
    snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

    // 获取文件信息
    if (stat(full_path, &file_stat) != 0) {
        perror("stat");
        return;
    }

    // 打印 inode
    if (show_inode) {
        printf("%ld ", file_stat.st_ino);  
    }

    // 打印文件类型和权限
    printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");

    // 打印链接数
    printf(" %ld ", file_stat.st_nlink);

    // 打印文件所属用户
    struct passwd *user = getpwuid(file_stat.st_uid);
    if (user != NULL) {
        printf("%s ", user->pw_name);
    } else {
        printf("%d ", file_stat.st_uid);  
    }

    // 打印文件所属组
    struct group *grp = getgrgid(file_stat.st_gid);
    if (grp != NULL) {
        printf("%s ", grp->gr_name);
    } else {
        printf("%d ", file_stat.st_gid); 
    }

    // 打印文件大小
    if (show_inode || show_size || show_long) {
        printf("%ld ", file_stat.st_size);
    }

    // 打印修改时间
    struct tm *time_info = localtime(&file_stat.st_mtime);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%b %d %H:%M", time_info);
    printf("%s ", time_str);

    // 打印文件名
    printf("%s\n", entry->d_name);
}



// -R
void list_directory(const char *path, int show_long, int show_hidden, int show_recursive, int show_inode, int show_size, int reverse, int show_time) {
    DIR *dp = opendir(path);  // 打开目录
    if (dp == NULL) {
        perror("opendir");
        return;
    }

    struct dirent **entries = NULL;
    int count = 0;
    struct dirent *entry;

    // 获取所有文件
    while ((entry = readdir(dp)) != NULL) {
        if (!show_hidden && entry->d_name[0] == '.') {
            continue;  // 跳过隐藏文件
        }
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;  // 跳过当前目录和父目录
        }
        entries = realloc(entries, sizeof(struct dirent *) * (count + 1));
        entries[count++] = entry;
    }

    // -t
    if (show_time) {
        qsort(entries, count, sizeof(struct dirent *), compare_time);
    }

    // -r
    if (reverse) {
        for (int i = 0; i < count / 2; ++i) {
            struct dirent *temp = entries[i];
            entries[i] = entries[count - i - 1];
            entries[count - i - 1] = temp;
        }
    }

    // 列出文件（先列出当前目录的文件）
    for (int i = 0; i < count; ++i) {
        if (show_long) {
            print_long_format(entries[i], path, show_size, show_inode, show_long);
        } else {
            if (show_inode) {
                struct stat file_stat;
                char full_path[512];
                snprintf(full_path, sizeof(full_path), "%s/%s", path, entries[i]->d_name);
                if (stat(full_path, &file_stat) == 0) {
                    printf("%ld ", file_stat.st_ino);
                }
            }
            if (show_size) {
                struct stat file_stat;
                char full_path[512];
                snprintf(full_path, sizeof(full_path), "%s/%s", path, entries[i]->d_name);
                if (stat(full_path, &file_stat) == 0) {
                    printf("%ld ", file_stat.st_size);
                }
            }
            printf("%s ", entries[i]->d_name);
        }
    }

    // 递归进入子目录
    if (show_recursive) {
        for (int i = 0; i < count; ++i) {
            struct stat file_stat;
            char full_path[512];
            snprintf(full_path, sizeof(full_path), "%s/%s", path, entries[i]->d_name);
            if (stat(full_path, &file_stat) == 0 && S_ISDIR(file_stat.st_mode)) {
                printf("\n%s:\n", entries[i]->d_name);
                list_directory(full_path, show_long, show_hidden, show_recursive, show_inode, show_size, reverse, show_time);
            }
        }
    }

    free(entries);
    closedir(dp);
}

void sort_and_list(const char *path, int show_long, int show_hidden, int show_recursive, int reverse, int show_inode, int show_size, int show_time) {
    list_directory(path, show_long, show_hidden, show_recursive, show_inode, show_size, reverse, show_time);
}
