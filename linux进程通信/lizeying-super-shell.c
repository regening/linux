#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_CMD 1024
#define MAX_ARG 64
#define MAX_PATH 1024

void abc (char *str) {                   // 去除换行符
    str[strcspn(str, "\n")] = 0;
}

void bcd (char *cmd, char **argv) {      // 解析命令字符串
    int i = 0;
    argv[i] = strtok(cmd, " \t");
    while (argv[i] != NULL && i < MAX_ARG - 1) {
        i++;
        argv[i] = strtok(NULL, " \t");
    }
    argv[i] = NULL;
}

int check_bg (char **argv) {              // 检查是否后台
    int i = 0;
    while (argv[i] != NULL) i++;
    if (i > 0 && strcmp(argv[i-1], "&") == 0) {
        argv[i-1] = NULL;
        return 1;
    }
    return 0;
}

int lmn(char **argv) {                     // 处理重定向
    int i = 0;
    while (argv[i] != NULL) {
        if (strcmp(argv[i], ">") == 0 || strcmp(argv[i], ">>") == 0) { // 输出
            int append = (strcmp(argv[i], ">>") == 0);
            char *filename = argv[i+1];
            if (!filename) { perror("No file specified"); return -1; }
            int fd = open(filename, O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC), 0644);
            if (fd < 0) { perror("open failed"); return -1; }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            argv[i] = NULL;
        }
        if (strcmp(argv[i], "<") == 0) { // 输入
            char *filename = argv[i+1];
            if (!filename) { perror("No file specified"); return -1; }
            int fd = open(filename, O_RDONLY);
            if (fd < 0) { perror("open failed"); return -1; }
            dup2(fd, STDIN_FILENO);
            close(fd);
            argv[i] = NULL;
        }
        i++;
    }
    return 0;
}

int main() {

    char cmd[MAX_CMD];
    char *argv[MAX_ARG];
    char pre[MAX_PATH] = {0}; 

    signal(SIGINT, SIG_IGN); 
    

    while (1) {
        // 打印提示符 
        char cwd[MAX_PATH];
        getcwd(cwd, sizeof(cwd)); 
        char *username = getpwuid(getuid())->pw_name; 
        char hostname[64];
        gethostname(hostname, sizeof(hostname));  
        printf("\033[1;32m%s@%s\033[0m:\033[1;34m%s\033[0m$ ", username, hostname, cwd);
		fflush(stdout); 

        // 读取命令
        if (fgets(cmd, sizeof(cmd), stdin) == NULL) {
            printf("\n");
            break; 
        }
        abc(cmd);
        if (cmd[0] == '\0') continue; 

        // 内置命令 exit
        if (strcmp(cmd, "exit") == 0) break;

        // 解析命令
        bcd(cmd, argv);
        if (!argv[0]) continue;

        // 内置命令 cd  
        if (strcmp(argv[0], "cd") == 0) {
            char *target = argv[1];
            if (!target || strcmp(target, "~") == 0) target = getenv("HOME");
            else if (strcmp(target, "-") == 0) target = pre;

            char current[MAX_PATH];
            getcwd(current, sizeof(current));
            if (chdir(target) != 0) perror("cd failed");
            else strcpy(pre, current);
            continue;
        }

        // 检查后台运行 &  
        int background = check_bg(argv);

        // 处理管道 
        int upipe = -1;
        for (int i = 0; argv[i]; i++) if (strcmp(argv[i], "|") == 0) upipe = i;

        if (upipe != -1) {
            // 分割命令
            argv[upipe] = NULL;
            char **argv1 = argv;
            char **argv2 = argv + upipe + 1;

            int fd[2];
            if (pipe(fd) < 0) { perror("pipe failed"); continue; }

            pid_t pid1 = fork();
            if (pid1 == 0) {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]); close(fd[1]);
                if (lmn(argv1) < 0) exit(1);
                execvp(argv1[0], argv1);
                perror("exec failed"); exit(1);
            }

            pid_t pid2 = fork();
            if (pid2 == 0) {
                dup2(fd[0], STDIN_FILENO);
                close(fd[0]); close(fd[1]);
                if (lmn(argv2) < 0) exit(1);
                execvp(argv2[0], argv2);
                perror("exec failed"); exit(1);
            }

            close(fd[0]); close(fd[1]);
            if (!background) { waitpid(pid1, NULL, 0); waitpid(pid2, NULL, 0); }
            continue;
        }

        // 命令 
        pid_t pid = fork();
        if (pid == 0) {
            signal(SIGINT, SIG_DFL); 
            if (lmn(argv) < 0) exit(1);
            execvp(argv[0], argv);
            perror("exec failed");
            exit(1);
        } else if (pid > 0) {
            if (!background) waitpid(pid, NULL, 0);
            else printf("[后台] pid=%d\n", pid);
        } else perror("fork failed");
    }

    return 0;
}