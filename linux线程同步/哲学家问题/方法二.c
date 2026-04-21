#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5  // 哲学家人数

pthread_mutex_t chopsticks[N];

void* philosopher3(void* num) {
    int id = *(int*)num;
    int left = id;
    int right = (id + 1) % N;

    printf("哲学家 %d 开始思考\n", id);
    usleep(rand() % 1000); // 模拟思考时间

    while (1) {
        // 尝试拿左筷子
        if (pthread_mutex_trylock(&chopsticks[left]) == 0) {
            // 尝试拿右筷子
            if (pthread_mutex_trylock(&chopsticks[right]) == 0) {
                // 拿到两支筷子，开始吃饭
                printf("哲学家 %d 拿到筷子 %d 和 %d，正在吃饭\n", id, left, right);
                usleep(rand() % 1000); // 模拟吃饭时间

                // 放下筷子
                pthread_mutex_unlock(&chopsticks[right]);
                pthread_mutex_unlock(&chopsticks[left]);
                printf("哲学家 %d 放下筷子，继续思考\n", id);
                break; // 吃完退出循环
            }
            // 拿不到右筷子，放下左筷子
            pthread_mutex_unlock(&chopsticks[left]);
        }
        usleep(rand() % 500); // 随机等待再尝试
    }

    return NULL;
}

int main() {
    pthread_t tid[N];
    int ids[N];

    // 初始化筷子
    for (int i = 0; i < N; i++)
        pthread_mutex_init(&chopsticks[i], NULL);

    // 创建哲学家线程
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&tid[i], NULL, philosopher3, &ids[i]);
    }

    // 等待所有哲学家线程完成
    for (int i = 0; i < N; i++)
        pthread_join(tid[i], NULL);

    // 销毁筷子锁
    for (int i = 0; i < N; i++)
        pthread_mutex_destroy(&chopsticks[i]);

    printf("完成用餐\n");
    return 0;
}