#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "ls.c"  // 引入ls.c中的函数

void sort_and_list(const char *path, int show_long, int show_hidden, int show_recursive, int reverse, int show_inode, int show_size);

int main(int argc, char *argv[]) {
    int list_a = 0;
    int list_l = 0;
    int list_R = 0;
    int list_r = 0;
    int list_i = 0;
    int list_s = 0;
    char *path = ".";  // 默认路径是当前目录

    int option;
    while ((option = getopt(argc, argv, "alRtrsi")) != -1) {
        switch (option) {
            case 'a':
                list_a = 1;
                break;
            case 'l':
                list_l = 1;
                break;
            case 'R':
                list_R = 1;
                break;
            case 'r':
                list_r = 1;
                break;
            case 'i':
                list_i = 1;
                break;
            case 's':
                list_s = 1;
                break;
            case 't':   // 可以添加排序功能
                break;
            default:
                fprintf(stderr, "Usage: %s [-a] [-l] [-R] [-r] [-i] [-s] [-t] [path]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    return 0;
}
