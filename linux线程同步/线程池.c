#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define MAX_THREADS 10
#define QUEUE_SIZE 20

typedef struct Task {
    void (*function)(void *arg);
    void *arg;
    void (*callback)(void *arg);
} Task;

typedef struct ThreadPool {
    pthread_t threads[MAX_THREADS];
    Task task_queue[QUEUE_SIZE];
    int head, tail, count;
    pthread_mutex_t lock;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
    int stop;
} ThreadPool;

void *worker(void *arg) {
    ThreadPool *pool = (ThreadPool *)arg;

    while (1) {
        pthread_mutex_lock(&pool->lock);
        while (pool->count == 0 && !pool->stop) {
            pthread_cond_wait(&pool->not_empty, &pool->lock);
        }
        if (pool->count == 0 && pool->stop) {
            pthread_mutex_unlock(&pool->lock);
            break; // 退出线程
        }
        // 取任务
        Task task = pool->task_queue[pool->head];
        pool->head = (pool->head + 1) % QUEUE_SIZE;
        pool->count--;
        pthread_cond_signal(&pool->not_full);
        pthread_mutex_unlock(&pool->lock);

        // 执行任务
        task.function(task.arg);
        if (task.callback) {
            task.callback(task.arg);
        }
    }
    return NULL;
}
void pool_init(ThreadPool *pool) {
    pool->head = pool->tail = pool->count = 0;
    pool->stop = 0;
    pthread_mutex_init(&pool->lock, NULL);
    pthread_cond_init(&pool->not_empty, NULL);
    pthread_cond_init(&pool->not_full, NULL);
    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_create(&pool->threads[i], NULL, worker, pool);
    }
}
void pool_add_task(ThreadPool *pool, void (*function)(void *), void *arg, void (*callback)(void *)) {
    pthread_mutex_lock(&pool->lock);
    while (pool->count == QUEUE_SIZE) {
        pthread_cond_wait(&pool->not_full, &pool->lock);
    }
    pool->task_queue[pool->tail].function = function;
    pool->task_queue[pool->tail].arg = arg;
    pool->task_queue[pool->tail].callback = callback;
    pool->tail = (pool->tail + 1) % QUEUE_SIZE;
    pool->count++;
    pthread_cond_signal(&pool->not_empty);
    pthread_mutex_unlock(&pool->lock);
}
void pool_destroy(ThreadPool *pool) {
    pthread_mutex_lock(&pool->lock);
    pool->stop = 1;
    pthread_cond_broadcast(&pool->not_empty);
    pthread_mutex_unlock(&pool->lock);

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(pool->threads[i], NULL);
    }

    pthread_mutex_destroy(&pool->lock);
    pthread_cond_destroy(&pool->not_empty);
    pthread_cond_destroy(&pool->not_full);
}


// 矩阵阶乘计算任务
void compute_matrix(void *arg) {
    int n = *(int*)arg;
    long result = 1;
    for (int i = 1; i <= n; i++) result *= i;
    printf("线程 %lu 计算 %d 的阶乘 = %ld\n", pthread_self(), n, result);
}
// 矩阵任务完成回调
void matrix_done(void *arg) {
    printf("线程 %lu 矩阵任务完成\n", pthread_self());
}
// 模拟下载任务
void download_file(void *arg) {
    char **params = (char**)arg; 
    char *url = params[0];
    char *path = params[1];
    printf("线程 %lu 下载文件 %s 到 %s\n", pthread_self(), url, path);
    sleep(2); 
}
// 下载任务完成回调
void download_done(void *arg) {
    printf("线程 %lu 下载任务完成\n", pthread_self());
}

int main() {
    ThreadPool pool;
    pool_init(&pool);

    int nums[5] = {5, 6, 7, 8, 9};
    for (int i = 0; i < 5; i++) {
        pool_add_task(&pool, compute_matrix, &nums[i], matrix_done);
    }

    char *files[3][2] = {
        {"http://example.com/file1", "file1.txt"},
        {"http://example.com/file2", "file2.txt"},
        {"http://example.com/file3", "file3.txt"}
    };
    for (int i = 0; i < 3; i++) {
        pool_add_task(&pool, download_file, files[i], download_done);
    }

    sleep(10);

    pool_destroy(&pool);
    printf("线程池已关闭\n");

    return 0;
}