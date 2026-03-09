// 输出重定向
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    pid_t pid = fork(); // 创建子进程
    if (pid == 0) {
        int fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        // file.txt：文件名，相对路径；O_WRONLY：以写入模式打开；O_CREAT：如果文件不存在，自动创建；O_TRUNC：如果文件存在，清空内容；0644：文件权限；6：所有者可以读写；4：同组用户可读；4：其他用户可读
        dup2(fd, STDOUT_FILENO);
        // dup2(oldfd, newfd) 把new指向old
        // STDOUT_FILENO：标准输出，通常指终端；fd：打开的文件
        // 程序写到标准输出的内容会被写入文件
        close(fd);

        char *argv[] = {"echo", "hello world", NULL}; // 创建命令参数数组
        execvp("echo", argv); // 用echo命令替换子进程当前的内容，命令的输出重定向到file.txt
        perror("exec failed"); // 只有上一步执行失败才会运行
        exit(1);
    } else {
        waitpid(pid, NULL, 0); // 父进程等待子进程结束
    }

    return 0;
}