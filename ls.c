#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void list_all(const char *path, int show_all) {
    struct dirent *entry;
    DIR *dp = opendir(path);  // 打开目录

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp)) != NULL) {  // 读取目录
        if (show_all || entry->d_name[0] != '.') {  // 如果是 -a 或者文件名不是以 . 开头，打印文件名
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dp);  // 关闭目录
}



 
int main(int argc, char *argv[]) {
    int show_all = 0;

    if (argc > 1 && strcmp(argv[1], "-a") == 0) {   // 检查命令行参数，是否有 -a 参数
        show_all = 1;  // 如果有 -a 参数，设置 show_all 为 1
    }

    list_all(".", show_all);  // 默认显示当前目录的文件

    return 0;
}
