// 实现的效果是在终端中执行`ls -l | grep txt`
// ls -l 输出文件列表
// 管道了把ls -l的输出传给下一个命令
// grep txt 从输出中过滤包含txt的行
/* 
子进程1：ls -l
      | 
      |
     管道
      |
      |
子进程2：grep txt 
      |
  终端（标准输出）
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    int fd[2];
    pipe(fd); // 创建一个无名管道
    // 返回两个文件描述符 fd[0]用于读 fd[1]用于写

    pid_t pid1 = fork();  // 创建第一个子进程
    // 第一个子进程：生产者
    if (pid1 == 0) { 
        // 子进程 1：ls -l
        dup2(fd[1], STDOUT_FILENO); // 输出重定向到管道写端
        close(fd[0]);
        close(fd[1]);

        char *argv[] = {"ls", "-l", NULL}; // 执行ls -l
        execvp("ls", argv); // 输出通过管道传递
        perror("exec failed"); // 如果失败 打印错误并退出
        exit(1);
    }

    pid_t pid2 = fork(); // 创建第二个子进程
    // 第二个子进程：消费者
    if (pid2 == 0) {
        // 子进程 2：grep txt
        dup2(fd[0], STDIN_FILENO); // 输入重定向到管道读端
        close(fd[0]);
        close(fd[1]);

        char *argv[] = {"grep", "txt", NULL}; // 执行grep txt
        execvp("grep", argv); // 读取管道输入，输出到标准输出（终端）
        perror("exec failed");
        exit(1);
    }

    // 父进程关闭管道，等待子进程
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}