#include <stdio.h>

struct result {    // 定义结果结构体
    int *arr;
    int len;
};

int compare(const void *a, const void *b) {     // 比较函数
    return (*(int*)a - *(int*)b);
}

void your_concat(int arr1[], int len1, int arr2[], int len2, struct result *res) {    // 拼接函数
    int total_len = len1 + len2;
    res->arr = (int*)malloc(total_len * sizeof(int));
    res->len = total_len;
    
    for (int i = 0; i < len1; i++) {
        res->arr[i] = arr1[i];
    }

    for (int i = 0; i < len2; i++) {
        res->arr[len1 + i] = arr2[i];
    }
}

void your_sort(struct result *res) {      // 排序函数
    qsort(res->arr, res->len, sizeof(int), compare);
}

void your_dedup(struct result *res) {      // 去重函数
    if (res->len == 0) return;
    
    int unique_index = 0;      // 双指针去重
    for (int i = 1; i < res->len; i++) {
        if (res->arr[i] != res->arr[unique_index]) {
            unique_index++;
            res->arr[unique_index] = res->arr[i];
        }
    }
    
    res->len = unique_index + 1;     // 更新长度
    
    int *new_arr = (int*)malloc(res->len * sizeof(int));    // 重新分配内存
    for (int i = 0; i < res->len; i++) {
        new_arr[i] = res->arr[i];
    }
    free(res->arr);
    res->arr = new_arr;
}

void print_result(struct result res) {       // 打印结果函数
    for (int i = 0; i < res.len; i++) {
        printf("%d ", res.arr[i]);
    }
    printf("\n");
}

int main() {
    int arr1[] = { 6, 1, 2, 1, 9, 1, 3, 2, 6, 2 };
    int arr2[] = { 4, 2, 2, 1, 6, 2 };
    int len1 = sizeof(arr1) / sizeof(arr1[0]);
    int len2 = sizeof(arr2) / sizeof(arr2[0]);

    struct result result;
    your_concat(arr1, len1, arr2, len2, result);
    print_result(result);
    your_sort(result);
    print_result(result);
    your_dedup(result);
    print_result(result);
    free(result.arr);
    return 0;
}