#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_THREADS 4

// 搜索配置结构体
typedef struct {
    char root_path[512];       // 根目录
    char file_type[16];        // 文件类型，如 ".txt"
    int max_depth;             // 最大搜索深度
    int skip_hidden;           // 是否跳过隐藏文件
} SearchConfig;

// 线程池相关
pthread_mutex_t thread_lock;
int active_threads = 0;
SearchConfig config;

// 判断文件是否匹配类型
int match_type(const char *filename) {
    size_t len = strlen(filename);
    size_t type_len = strlen(config.file_type);
    if (len < type_len) return 0;
    return strcmp(filename + len - type_len, config.file_type) == 0;
}

// 判断是否隐藏文件
int is_hidden(const char *name) {
    return name[0] == '.';
}

// 递归搜索函数
void search_directory(const char *path, int depth) {
    if (depth > config.max_depth) return;

    DIR *dir = opendir(path);
    if (!dir) return;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (config.skip_hidden && is_hidden(entry->d_name)) continue;

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(full_path, &st) == -1) continue;

        if (S_ISDIR(st.st_mode)) {
            // 控制线程数量
            pthread_mutex_lock(&thread_lock);
            if (active_threads < MAX_THREADS) {
                active_threads++;
                pthread_mutex_unlock(&thread_lock);

                // 创建新线程搜索子目录
                pthread_t tid;
                char *sub_path = strdup(full_path); // 传给线程的路径
                pthread_create(&tid, NULL, (void*(*)(void*))search_directory, sub_path);
                pthread_detach(tid); // 分离线程

            } else {
                pthread_mutex_unlock(&thread_lock);
                search_directory(full_path, depth + 1);
            }
        } else if (S_ISREG(st.st_mode)) {
            if (match_type(entry->d_name)) {
                printf("%s\n", full_path);
            }
        }
    }

    closedir(dir);

    pthread_mutex_lock(&thread_lock);
    if (active_threads > 0) active_threads--;
    pthread_mutex_unlock(&thread_lock);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: %s <root_path> <file_type> <max_depth>\n", argv[0]);
        return 1;
    }

    strncpy(config.root_path, argv[1], sizeof(config.root_path));
    strncpy(config.file_type, argv[2], sizeof(config.file_type));
    config.max_depth = atoi(argv[3]);
    config.skip_hidden = 1; // 跳过隐藏文件

    pthread_mutex_init(&thread_lock, NULL);

    search_directory(config.root_path, 0);

    sleep(2);

    pthread_mutex_destroy(&thread_lock);
    return 0;
}