// 方法一：资源顺序法，先拿编号小的筷子

// 给筷子编号 0~4
// 哲学家按顺序拿筷子：
// 总是先拿 编号小的筷子，再拿编号大的筷子
// 保证不会循环等待 → 防止死锁

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

pthread_mutex_t chopsticks[N];

void* philosopher(void* num) {
    int id = *(int*)num;
    int left = id;
    int right = (id + 1) % N;

    int first = left < right ? left : right;
    int second = left < right ? right : left;

    printf("哲学家 %d 开始思考\n", id);
    usleep(rand() % 1000); // 模拟思考时间

    pthread_mutex_lock(&chopsticks[first]);
    printf("哲学家 %d 拿起筷子 %d\n", id, first);
    pthread_mutex_lock(&chopsticks[second]);
    printf("哲学家 %d 拿起筷子 %d\n", id, second);

    printf("哲学家 %d 正在吃饭\n", id);
    usleep(rand() % 1000); // 模拟吃饭时间

    pthread_mutex_unlock(&chopsticks[first]);
    pthread_mutex_unlock(&chopsticks[second]);
    printf("哲学家 %d 放下筷子，继续思考\n", id);

    return NULL;
}

int main() {
    pthread_t tid[N];
    int ids[N];

    for (int i = 0; i < N; i++)
        pthread_mutex_init(&chopsticks[i], NULL);

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&tid[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(tid[i], NULL);

    for (int i = 0; i < N; i++)
        pthread_mutex_destroy(&chopsticks[i]);

    return 0;
}