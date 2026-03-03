#include "test.h"

int a = 0;  
int l = 0;  
int R = 0;  
int t = 0;  
int r = 0;  
int i = 0;  
int s = 0; 

int hidden(char *file){
    if (file[0] == '.'){
        return 1; 
    }
    else{
        return 0;
    }
}

void major(char *WAY){
    DIR *dir;  
    struct dirent *ent;  
    struct stat st;  
    char buf[PATH_MAX]; 

    dir = opendir(WAY);                                                                         // 打开目录
    if (dir == NULL) {
        perror("opendir");  
        return;
    }

    struct information{
        char name[256]; 
        time_t mod_time; 
        ino_t inode_num; 
        off_t file_size; 
    };

    struct information entries[1024];   
    int num = 0;  
    
    while ((ent = readdir(dir)) != NULL) {                                                     // 读取目录 
        if (!a && hidden(ent->d_name)){
            continue;
        }
        strcpy(entries[num].name, ent->d_name);

        snprintf(buf, PATH_MAX, "%s/%s", WAY, ent->d_name);
        if (stat(buf, &st) == 0){
            entries[num].mod_time = st.st_mtime;
            entries[num].inode_num = st.st_ino;
            entries[num].file_size = st.st_size;
        }
        num++;

        if (num >= 1024){
            break;
        }
    }

    closedir(dir);

    for (int i = 0; i < num - 1; i++){                                                         //  排序:时间 or 文件名
        for (int j = 0; j < num - 1 - i; j++){
            int temp = 0;

            if (t){  
                if (!r && entries[j].mod_time > entries[j + 1].mod_time){
                    temp = 1;
                }
                if (r && entries[j].mod_time < entries[j + 1].mod_time){
                    temp = 1;
                }
            }
            else{ 
                if (!r && strcmp(entries[j].name, entries[j + 1].name) > 0){
                    temp = 1;
                }
                if (r && strcmp(entries[j].name, entries[j + 1].name) < 0){
                    temp = 1;
                }
            }

            if (temp){
                struct information temp = entries[j];
                entries[j] = entries[j + 1]; 
                entries[j + 1] = temp;
            }
        }
    }

    
    for (int i = 0; i < num; i++){                                                              // 输出文件信息
        snprintf(buf, PATH_MAX, "%s/%s", WAY, entries[i].name);
        if (stat(buf, &st) != 0){                                                               // 跳过隐藏文件
            continue;
        }

        if (i) {                                                                                // 输出idone号 
            printf("%lu ", (unsigned long)entries[i].inode_num);
        }

        if (s) {                                                                                // 输出文件大小
            printf("%ld ", (long)entries[i].file_size);
        }

        if (l){                                                                                 // 输出详细文件信息
            if (S_ISDIR(st.st_mode)){
                printf("d");
            }
            else{
                printf("-");
            }

            printf("%c%c%c%c%c%c%c%c%c", st.st_mode & S_IRUSR ? 'r' : '-',
                st.st_mode & S_IWUSR ? 'w' : '-',
                st.st_mode & S_IXUSR ? 'x' : '-',
                st.st_mode & S_IRGRP ? 'r' : '-',
                st.st_mode & S_IWGRP ? 'w' : '-',
                st.st_mode & S_IXGRP ? 'x' : '-',
                st.st_mode & S_IROTH ? 'r' : '-',
                st.st_mode & S_IWOTH ? 'w' : '-',
                st.st_mode & S_IXOTH ? 'x' : '-');

            printf("%lu ", (unsigned long)st.st_nlink);
            struct passwd *pw = getpwuid(st.st_uid);  
            struct group *gr = getgrgid(st.st_gid);
            printf("%s %s ", pw ? pw->pw_name : "", gr ? gr->gr_name : "");
            printf("%8ld ", (long)st.st_size);

            char tbuf[64];
            struct tm *tmx = localtime(&st.st_mtime);
            strftime(tbuf, sizeof(tbuf), "%b %d %H:%M", tmx);
            printf("%s ", tbuf);
        }

        if (S_ISDIR(st.st_mode)){                                                                 // 输出文件名
            printf("\033[1;34m%s\033[0m", entries[i].name);
        }
        else if (st.st_mode & S_IXUSR){
            printf("\033[1;32m%s\033[0m", entries[i].name);
        }
        else{
            printf("%s", entries[i].name);
        }
        
        printf("\n");
    }

   
    if (R){                                                                                       // 递归列出目录
        for (int i = 0; i < num; i++){
            if (strcmp(entries[i].name, ".") == 0 || strcmp(entries[i].name, "..") == 0){
                continue;
            }

            snprintf(buf, PATH_MAX, "%s/%s", WAY, entries[i].name);
            if (stat(buf, &st) == 0 && S_ISDIR(st.st_mode)){
                printf("\n%s:\n", buf);
                major(buf);
            }
        }
    }
}