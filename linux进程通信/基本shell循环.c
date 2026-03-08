#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD 1024  // 命令最大长度 用于储存用户输入命令的缓冲区
#define MAX_ARG 64    // 命令参数最大数量 用于储存解析后的参数数组
#define MAX_PATH 1024 // 路径字符串最大长度 用于储存当前工作目录和上一次目录

void parse(char *cmd, char **argv) {  // 解析命令：把输入的命令字符串拆分成程序名和参数列表
    int i = 0; 
    argv[i] = strtok(cmd, " \t\n");
        // strtok把输入的命令字符串按照空格 制表符或换行符拆分成多个参数
        // argv[i]用来储存拆分后的参数 比如 "ls -l/ home" --> argv[0]="ls" argv[1]="-l" argv[2]="/home"
    while (argv[i] != NULL && i < MAX_ARG - 1) { // 防止空数组或者数组越界
        i++;
        argv[i] = strtok(NULL, " \t\n");
            // 最后一个元素必须是NULL 因为execvp需要以NULL结尾的参数数组
    }
}

int main() {
    char cmd[MAX_CMD];      // cmd储存用户输入的命令行
    char *argv[MAX_ARG];    // argv储存解析后的命令及参数

    char prev_dir[MAX_PATH] = ""; // 保存上一次目录，实现cd功能

    // shell主循环
    while(1) {  // 一直运行到输入exit或ctrl+d
        // 打印提示符
        char cwd[MAX_PATH];
        getcwd(cwd, sizeof(cwd));  // 输入当前目录，并存入cwd
        printf("my-shell:%s$ ", cwd);  // 打印shell提示符，包括当前目录

        // 读取用户输入
        if (fgets(cmd, sizeof(cmd), stdin) == NULL) {
            printf("\n");
            break; // ctrl+d退出
        }

        // 去掉换行符
        cmd[strcspn(cmd, "\n")] = 0; // 找到回车在字符串中的位置，并替换成\0

        // 内置命令 exit
        if (strcmp(cmd, "exit") == 0) {
            break;
        }
        // 解析命令
        parse(cmd, argv);

        // 内置命令 cd
        if (strcmp(argv[0], "cd") == 0) { // 检查argv[0]是否是cd 是的话进入内置处理
            char *target_dir = argv[1]; // argv[1]是想要切换到的目录
            if (!target_dir || strcmp(target_dir, "~") == 0) {
                target_dir = getenv("HOME");  // 回到HOME
            } else if (strcmp(target_dir, "-") == 0) {
                target_dir = prev_dir;        // 回到上次目录
            }
            char current [MAX_PATH];
            getcwd(current, sizeof(current)); // 获取当前目录 
            if (chdir(target_dir) != 0) {
                perror("cd failed");
            } else {
                strcpy(prev_dir, current);
            }
            continue;
        }

        // 创建子进程执行命令
        pid_t pid = fork();
      /*子进程 pid==0 
        父进程 pid>0
        失败 pid<0*/
        if (pid == 0) {
            execvp(argv[0], argv);
            perror("exec failed");
            exit(1);
        } else if (pid > 0) {
            waitpid(pid, NULL, 0);
        } else {
            perror("fork failed");
        }
    }

    return 0;
}