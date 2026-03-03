#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "ls.h"  // 引入ls.h中的函数声明

int main(int argc, char *argv[]) {
    int show_long = 0;
    int show_hidden = 0;
    int show_recursive = 0;
    int reverse = 0;
    int show_inode = 0;
    int show_size = 0;  
    int show_time = 0;    // 判断是否按时间排序
    char *path = ".";  // 默认 是当前目录

    int option;
    while ((option = getopt(argc, argv, "alRtrsi")) != -1) {
        switch (option) {
            case 'a':   //实现-a
                show_hidden = 1;
                break;
            case 'l':   //实现-l
                show_long = 1;
                break;
            case 'R':   //实现-R
                show_recursive = 1;
                break;
            case 't':   //实现-t
                show_time = 1;
                break;
            case 'r':   //实现-r
                reverse = 1;
                break;
            case 'i':   //实现-i
                show_inode = 1;
                break;
            case 's':   //实现-s
                show_size = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-a] [-l] [-R] [-r] [-t] [-s] [-i] [path]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (optind < argc) {    // 如果指定了路径，使用它
        path = argv[optind];
    }

    sort_and_list(path, show_long, show_hidden, show_recursive, reverse, show_inode, show_size, show_time);  // 按照指定参数列出目录内容

    return 0;
}
