# 头文件
```c
#include <dirent.h>     // 操作目录
#include <stdio.h>      // 标准输入输出函数
#include <stdlib.h>     // 标准库函数 处理一些基本操作
#include <string.h>     // 字符串操作函数

#include <dirent.h>:
    /*struct dirent 结构体：用于描述目录中每一个条目的结构体，包含了目录中每一个文件或子目录的基本信息。*/
    struct dirent{
        ino_t d_ino;              //文件的inode编号
        off_t d_off;              //文件的偏移量
        unsigned short d_reclen;  //记录的长度
        unsigned char d_type;     //文件类型如目录、普通文件等
        char d_name[256];         //文件或目录名称
    }
```
# -a
```c
struct dirent *entry;
/* 定义一个指向 struct dirent 结构体的指针，命名为 entry，用来保存目录中每一个文件或子目录的信息。*/
/*当使用readdir()函数读取目录时，返回一个 struct dirent* 类型的指针，指向当前目录项的结构体，可以通过这个指针访问当前目录项的文件名、文件类型等信息*/
```