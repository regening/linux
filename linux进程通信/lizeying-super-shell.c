#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_CMD 1024
#define MAX_ARG 128
 
char prev_dir[1024];                        // 保存上一次目录

char* ini(char* str) {                      // 初始处理：去掉字符串两端空白
    while(*str == ' ' || *str == '\t') str++;
    if(*str == 0) return str;
    char* end = str + strlen(str) - 1;
    while(end > str && (*end == ' ' || *end == '\t' || *end == '\n')) {
        *end = 0;
        end--;
    }
    return str;
}

void bcd (char *cmd, char **argv) {        // 解析命令字符串
    int i = 0;
    argv[i] = strtok(cmd, " \t");
    while (argv[i] != NULL && i < MAX_ARG - 1) {
        i++;
        argv[i] = strtok(NULL, " \t");
    }
    argv[i] = NULL;
}

void redir(char** params) {                // 处理重定向
    int fd_in = -1, fd_out = -1, append_mode = 0;
    for(int i=0; params[i]; i++) {
        if(strcmp(params[i], ">") == 0 || strcmp(params[i], ">>") == 0) {
            append_mode = (strcmp(params[i], ">>") == 0);
            fd_out = open(params[i+1], append_mode ? O_WRONLY|O_CREAT|O_APPEND : O_WRONLY|O_CREAT|O_TRUNC, 0644);
            if(fd_out < 0) { perror("open"); return; }
            params[i] = NULL;
        }
        else if(strcmp(params[i], "<") == 0) {
            fd_in = open(params[i+1], O_RDONLY);
            if(fd_in < 0) { perror("open"); return; }
            params[i] = NULL;
        }
    }

    pid_t pid = fork();
    if(pid == 0) {
        if(fd_in != -1) { dup2(fd_in, STDIN_FILENO); close(fd_in); }
        if(fd_out != -1) { dup2(fd_out, STDOUT_FILENO); close(fd_out); }
        execvp(params[0], params);
        perror("execvp failed");
        exit(1);
    } else {
        waitpid(pid, NULL, 0);
        if(fd_in != -1) close(fd_in);
        if(fd_out != -1) close(fd_out);
    }
}

void run_pipe(char* line) {                 // 管道处理
    char* cmds[128];
    int count = 0;
    char* token = strtok(line, "|");
    while(token != NULL) {
        cmds[count++] = ini(token);
        token = strtok(NULL, "|");
    }

    int input_fd = 0;
    for(int i=0; i<count; i++) {
        int pipe_fd[2];
        if(i < count-1) pipe(pipe_fd);

        char* params[MAX_ARG];
        bcd(cmds[i], params);

        pid_t pid = fork();
        if(pid == 0) {
            if(input_fd != 0) { dup2(input_fd, STDIN_FILENO); close(input_fd); }
            if(i < count-1) { dup2(pipe_fd[1], STDOUT_FILENO); close(pipe_fd[0]); close(pipe_fd[1]); }
            redir(params);
            exit(0);
        } else {
            waitpid(pid, NULL, 0);
            if(input_fd != 0) close(input_fd);
            if(i < count-1) { close(pipe_fd[1]); input_fd = pipe_fd[0]; }
        }
    }
}

int main() {
    char cmd_line[MAX_CMD];
    char cwd[1024];
    getcwd(prev_dir, sizeof(prev_dir));

    while(1) {
        getcwd(cwd, sizeof(cwd));

        char *user = getpwuid(getuid())->pw_name;
        char hostname[64];
        gethostname(hostname, sizeof(hostname));
        printf("\033[1;32m%s\033[0m@\033[1;32m%s\033[0m:\033[1;34m%s\033[0m$ ", user, hostname, cwd);
        fflush(stdout);

        if(!fgets(cmd_line, sizeof(cmd_line), stdin)) break;
        char* cmd = ini(cmd_line);
        if(strlen(cmd) == 0) continue;

        if(strncmp(cmd, "cd", 2) == 0) {        // cd
            char* dir = ini(cmd+2);
            if(strlen(dir) == 0 || strcmp(dir, "~") == 0) dir = getenv("HOME");
            else if(strcmp(dir, "-") == 0) {
                char tmp[1024];
                strcpy(tmp, prev_dir);
                getcwd(prev_dir, sizeof(prev_dir));
                dir = tmp;
            } else { getcwd(prev_dir, sizeof(prev_dir)); }
            if(chdir(dir) != 0) perror("cd failed");
            continue;
        }

        if(strcmp(cmd, "exit") == 0) break;

        if(strchr(cmd, '|')) {
            run_pipe(cmd);
        } else {
            char* params[MAX_ARG];
            bcd(cmd, params); 
            redir(params);
        }
    }
    return 0;
}