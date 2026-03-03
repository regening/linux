# 实现内容
 `-a` ：显示该目录下所有文件名称及子目录，包括隐藏文件名称。<br>
 `-i`：显示文件的  inode 号。 <br>
 `-s` ： 。<br>
 `-l` ： 。<br>
 `-r` ： 。<br>
 `-t` ： 。<br>
 `-R` ： 。<br>
# 头文件
```c
#include <stdio.h>      // 标准输入输出函数
#include <stdlib.h>     // 标准库函数 处理一些基本操作
#include <dirent.h>     // 操作目录
#include <sys/stat.h>
#include <string.h>     // 字符串操作函数
#include <time.h>
#include <unistd.h>

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

1. #include <stdio.h>

<stdio.h> 是标准输入输出库（Standard Input Output），提供了与输入和输出相关的函数。它包括操作文件、标准输入输出流等常用功能。

常用函数：

printf()：打印输出到控制台。

scanf()：从控制台读取输入。

fopen()：打开文件。

fclose()：关闭文件。

fgets()：读取文件内容。

2. #include <stdlib.h>

<stdlib.h> 是标准库，用于内存管理、进程控制、转换等功能。它包括动态内存分配、随机数生成、程序退出等常用功能。

常用函数：

malloc()：动态分配内存。

free()：释放动态分配的内存。

exit()：终止程序。

atoi()：将字符串转换为整数。

system()：执行系统命令。

3. #include <dirent.h>

<dirent.h> 提供了与目录操作相关的功能。它定义了 DIR 类型和一些用于操作目录的函数，如打开、读取和关闭目录。你可以通过这个头文件遍历文件夹中的内容。

常用函数：

opendir()：打开目录。

readdir()：读取目录中的每一个文件项。

closedir()：关闭打开的目录。

常用结构体：

struct dirent：表示目录中的一个文件项，通常包含文件的名称、类型和其他信息。

4. #include <sys/stat.h>

<sys/stat.h> 头文件提供了与文件和目录属性相关的函数。这些函数通常用于获取文件的详细信息，例如文件大小、权限、修改时间等。

常用函数：

stat()：获取文件或目录的状态（例如文件大小、权限、修改时间等）。

chmod()：修改文件的权限。

mkdir()：创建目录。

remove()：删除文件。

常用结构体：

struct stat：用于存储文件的状态信息，包括权限、所有者、文件大小等。

5. #include <string.h>

<string.h> 头文件提供了与字符串操作相关的函数。它定义了用于处理 C 字符串（即字符数组）的一些常用函数。

常用函数：

strlen()：计算字符串的长度。

strcpy()：复制字符串。

strcmp()：比较两个字符串。

strcat()：连接两个字符串。

strtok()：分割字符串。

6. #include <time.h>

<time.h> 头文件用于处理日期和时间。它提供了与系统时间、日期相关的函数和结构体，用于获取当前时间、格式化时间、计算时间间隔等。

常用函数：

time()：获取当前时间的秒数。

localtime()：将时间戳转换为本地时间。

strftime()：格式化时间。

difftime()：计算两个时间点之间的时间差。

常用结构体：

struct tm：表示时间信息的结构体，包括年、月、日、小时、分钟、秒等字段。

7. #include <unistd.h>

<unistd.h> 头文件提供了对操作系统底层功能的访问，主要包括进程控制、文件操作、系统调用等功能。它通常用于 Unix 系统中的程序开发。

常用函数：

getpid()：获取当前进程的进程ID。

fork()：创建一个子进程。

exec()：在子进程中执行一个新的程序。

sleep()：让程序暂停指定的秒数。

chdir()：改变当前工作目录。

unlink()：删除文件。

总结

这些头文件为你提供了许多在文件和目录操作、时间管理、字符串处理、进程控制等方面的标准库支持，帮助你在 Linux 系统中进行系统编程。

stdio.h：用于标准输入输出操作。

stdlib.h：提供内存管理、程序控制等功能。

dirent.h：用于操作目录和读取文件项。

sys/stat.h：用于获取文件或目录的属性。

string.h：提供字符串处理函数。

time.h：用于时间和日期处理。

unistd.h：提供系统调用和底层操作。    

