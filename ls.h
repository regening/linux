#ifndef LS_H
#define LS_H

#include <dirent.h> 
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort_and_list(const char *path, int show_long, int show_hidden, int show_recursive, int reverse, int show_inode, int show_size, int show_time);
void list_directory(const char *path, int show_long, int show_hidden, int show_recursive, int show_inode, int show_size, int reverse, int show_time);
void print_long_format(struct dirent *entry, const char *path, int show_size, int show_inode, int show_long);

#endif

