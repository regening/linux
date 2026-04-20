#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREADS 4
#define MAX_TASKS 10

typedef struct {
    void (*function)(void *);
    void *arg;
} Task;

Task taskQueue[MAX_TASKS];
int taskCount = 0;
pthread_mutex_t queueLock;
pthread_cond_t queueCond;
int shutdown = 0; // 线程池关闭

// 工作线程函数
void* worker(void *arg) {
    while (1) {
        pthread_mutex_lock(&queueLock);

        while (taskCount == 0 && !shutdown) {
            pthread_cond_wait(&queueCond, &queueLock);
        }

        if (taskCount == 0 && shutdown) {
            pthread_mutex_unlock(&queueLock);
            break;
        }

        Task task = taskQueue[0];
        for (int i = 0; i < taskCount - 1; i++)
            taskQueue[i] = taskQueue[i + 1];
        taskCount--;

        pthread_mutex_unlock(&queueLock);

        task.function(task.arg);

        free(task.arg);
    }
    return NULL;
}

// 提交任务
void submitTask(void (*func)(void *), void *arg) {
    pthread_mutex_lock(&queueLock);

    if (taskCount < MAX_TASKS) {
        taskQueue[taskCount].function = func;
        taskQueue[taskCount].arg = arg;
        taskCount++;
        pthread_cond_signal(&queueCond);
    } else {
        free(arg); 
    }

    pthread_mutex_unlock(&queueLock);
}

// 关闭线程池
void shutPool(pthread_t threads[], int threadNum) {
    pthread_mutex_lock(&queueLock);
    shutdown = 1;           // 设置关闭
    pthread_cond_broadcast(&queueCond); 
    pthread_mutex_unlock(&queueLock);

    for (int i = 0; i < threadNum; i++) {
        pthread_join(threads[i], NULL); // 等待线程退出
    }
}

// 示例任务函数
void printTask(void *arg) {
    int num = *(int *)arg;
    printf("线程 %lu 执行任务 %d\n", pthread_self(), num);
    sleep(1);
}

int main() {
    pthread_t threads[MAX_THREADS];
    pthread_mutex_init(&queueLock, NULL);
    pthread_cond_init(&queueCond, NULL);

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_create(&threads[i], NULL, worker, NULL);
    }

    for (int i = 0; i < 10; i++) {
        int *num = malloc(sizeof(int));
        *num = i + 1;
        submitTask(printTask, num);
    }

    sleep(12);

    shutPool(threads, MAX_THREADS);

    pthread_mutex_destroy(&queueLock);
    pthread_cond_destroy(&queueCond);

    printf("线程池已关闭\n");
    return 0;
}