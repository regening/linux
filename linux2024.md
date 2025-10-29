## 0. 聪明的吗喽

一个小猴子边上有 100 根香蕉，它要走过 50 米才能到家，每次它最多搬 50 根香蕉，（多了就拿不动了），它每走 1 米就要吃掉一根，请问它最多能把多少根香蕉搬到家里。

（提示：他可以把香蕉放下往返走，但是必须保证它每走一米都能有香蕉吃。也可以走到 n 米时，放下一些香蕉，拿着 n 根香蕉走回去重新搬 50 根。）

## 题解

本题主要考察

---
<br>
本题主要思路：<br>


---

## 1. 西邮Linux欢迎你啊

请解释以下代码的运行结果。

```c
int main() {
    unsigned int a = 2024;
    for (; a >= 0; a--)
        printf("%d\n", printf("Hi guys! Join Linux - 2%d", printf("")));
    return 0;
}
```

## 题解

本题主要考察printf函数。

printf两个核心特性:<br>
1.输出行为:
printf() 会将字符串中的内容原样打印到标准输出<br>
2.返回值
它返回的是成功输出的字符数（不包括字符串结束符 \0）。

---
<br>
本题主要思路：<br>

在本题中for循环条件为`a >= 0 ; a--`， a 的初始值为2024, 大于0, 满足for循环的运行条件，进入for循环。<br>
| 层级 | 内容 | 作用 |
| --- | --- | --- |
| 最内层 | ```printf("") ```| 返回值是 0 |
| 中间层 | ```printf("Hi guys! Join Linux - 2%d", printf("")) ```| 要打印字符串，并在 %d 处替换上面那个返回值 0 |
| 最外层 |``` printf("%d\n", printf(...)) ```| 要打印中间层的返回值 |

重复运行for循环，直到 a-- 至 a < 0， 即重复打印`Hi guys! Join Linux - 2024`2024次。

---

## 2. 眼见不一定为实

输出为什么和想象中不太一样？

你了解 `sizeof()` 和 `strlen()` 吗？他们的区别是什么？

```c
int main() {
    char p0[] = "I love Linux";
    const char *p1 = "I love Linux\0Group";
    char p2[] = "I love Linux\0";
    printf("%d\n%d\n", strcmp(p0, p1), strcmp(p0, p2));
    printf("%d\n%d\n", sizeof(p0) == sizeof(p1), strlen(p0) == strlen(p1));
    return 0;
}
```

## 题解

本题主要考察sizeof和strlen。

| | sizeof运算符 | strlen()函数 |
| --- | --- | --- |
| 本质 | 关键字，编译时运算符 | 标准库函数 |
| 头文件 | 不需要 | <string .h> |
| 计算时间 | 编译时 | 运算时 |
| 参数类型 | 数据类型,变量,表达式 | 字符串指针(必须\0结尾)
| 返回值内容 | 占用的总字节数 | \0前的字符个数 |
| 处理\0 | 包含\0 | 不包含\0 |

---
<br>
本题主要思路：<br>


---

## 3. 1.1 - 1.0 != 0.1

为什么会这样，除了下面给出的一种方法，还有什么方法可以避免这个问题？

```c
int main() {
    float a = 1.0, b = 1.1, ex = 0.1;
    printf("b - a == ex is %s\n", (b - a == ex) ? "true" : "false");
    int A = a * 10, B = b * 10, EX = ex * 10;
    printf("B - A == EX is %s\n", (B - A == EX) ? "true" : "false");
}
```

## 题解

本题主要考察

---
<br>
本题主要思路：<br>


---

## 4. 听说爱用位运算的人技术都不太差

解释函数的原理，并分析使用位运算求平均值的优缺点。

```c
int average(int nums[], int start, int end) {
    if (start == end)
        return nums[start];
    int mid = (start + end) / 2;
    int leftAvg = average(nums, start, mid);
    int rightAvg = average(nums, mid + 1, end);
    return (leftAvg & rightAvg) + ((leftAvg ^ rightAvg) >> 1);
}
```

## 题解

本题主要考察

---
<br>
本题主要思路：<br>


---

## 5. 全局还是局部!!!

先思考输出是什么，再动动小手运行下代码，看跟自己想得结果一样不一样 >-<

```c
int i = 1;
static int j = 15;
int func() {
    int i = 10;
    if (i > 5) i++;
    printf("i = %d, j = %d\n", i, j);
    return i % j;
}
int main() {
    int a = func();
    printf("a = %d\n", a);
    printf("i = %d, j = %d\n", i, j);
    return 0;
}
```

## 题解

本题主要考察

---
<br>
本题主要思路：<br>


---

## 6. 指针的修罗场：改还是不改，这是个问题

指出以下代码中存在的问题，并帮粗心的学长改正问题。

```c
int main(int argc, char **argv) {
    int a = 1, b = 2;
    const int *p = &a;
    int * const q = &b;
    *p = 3, q = &a;
    const int * const r = &a;
    *r = 4, r = &b;
    return 0;
}
```

## 题解

本题主要考察

---
<br>
本题主要思路：<br>


---

## 7. 物极必反？

你了解 `argc` 和 `argv` 吗，这个程序里的 `argc` 和 `argv` 是什么？

程序输出是什么？解释一下为什么。

```c
int main(int argc, char *argv[]) {
    while (argc++ > 0);
    int a = 1, b = argc, c = 0;
    if (--a || b++ && c--)
        for (int i = 0; argv[i] != NULL; i++)
            printf("argv[%d] = %s\n", i, argv[i]);
    printf("a = %d, b = %d, c = %d\n", a, b, c);
    return 0;
}
```

## 题解

本题主要考察

---
<br>
本题主要思路：<br>


---

## 8. 指针？数组？数组指针？指针数组？

在主函数中定义如下变量：

```c
int main() {
    int a[2] = {4, 8};
    int(*b)[2] = &a;
    int *c[2] = {a, a + 1};
    return 0;
}
```

说说这些输出分别是什么？

```c
a, a + 1, &a, &a + 1, *(a + 1), sizeof(a), sizeof(&a)
*b, *b + 1, b, b + 1, *(*b + 1), sizeof(*b), sizeof(b)
c, c + 1, &8. 指针？数组？数组指针？指针数组？
```

## 题解

本题主要考察

---
<br>
本题主要思路：<br>


---

## 9. 嘻嘻哈哈，好玩好玩

在宏的魔法下，数字与文字交织，猜猜结果是什么？

```c
#define SQUARE(x) x *x
#define MAX(a, b) (a > b) ? a : b;
#define PRINT(x) printf("嘻嘻，结果你猜对了吗，包%d滴\n", x);
#define CONCAT(a, b) a##b

int main() {
    int CONCAT(x, 1) = 5;
    int CONCAT(y, 2) = 3;
    int max = MAX(SQUARE(x1 + 1), SQUARE(y2))
    PRINT(max)
    return 0;
}
```

## 题解

本题主要考察

---
<br>
本题主要思路：<br>


---

## 10. 我写的排序最快

写一个 `your_sort` 函数，要求不能改动 `main` 函数里的代码，对 `arr1` 和 `arr2` 两个数组进行升序排序并剔除相同元素，最后将排序结果放入 `result` 结构体中。

```c
int main() {
    int arr1[] = {2, 3, 1, 3, 2, 4, 6, 7, 9, 2, 10};
    int arr2[] = {2, 1, 4, 3, 9, 6, 8};
    int len1 = sizeof(arr1) / sizeof(arr1[0]);
    int len2 = sizeof(arr2) / sizeof(arr2[0]);

    result result;
    your_sort(arr1, len1, arr2, len2, &result);
    for (int i = 0; i < result.len; i++) {
        printf("%d ", result.arr[i]);
    }
    free(result.arr);
    return 0;
}
```

## 题解

本题主要考察

---
<br>
本题主要思路：<br>


---

## 11. 猜猜我是谁

在指针的迷宫中，五个数字化身为神秘的符号，等待被逐一揭示。

```c
int main() {
    void *a[] = {(void *)1, (void *)2, (void *)3, (void *)4, (void *)5};
    printf("%d\n", *((char *)a + 1));
    printf("%d\n", *(int *)(char *)a + 1);
    printf("%d\n", *((int *)a + 2));
    printf("%lld\n", *((long long *)a + 3));
    printf("%d\n", *((short *)a + 4));
    return 0;
}
```

## 题解

本题主要考察

---
<br>
本题主要思路：<br>


---

## 12. 结构体变小写奇遇记

计算出 `Node` 结构体的大小，并解释以下代码的运行结果。

```c
union data {
    int a;
    double b;
    short c;
};
typedef struct node {
    long long a;
    union data b;
    void (*change)( struct node *n);
    char string[0];
} Node;
void func(Node *node) {
    for (size_t i = 0; node->string[i] != '\0'; i++)
        node->string[i] = tolower(node->string[i]);
}

int main() {
    const char *s = "WELCOME TO XIYOULINUX_GROUP!";
    Node *P = (Node *)malloc(sizeof(Node) + (strlen(s) + 1) * sizeof(char));
    strcpy(P->string, s);
    P->change = func;
    P->change(P);
    printf("%s\n", P->string);
    return 0;
}
```

## 题解

本题主要考察

---
<br>
本题主要思路：<br>


---

## 13. GNU/Linux (选做)

注：嘿！你或许对Linux命令不是很熟悉，甚至没听说过Linux。\
但别担心，这是选做题，了解Linux是加分项，不了解也不扣分哦！

- 你知道 `ls` 命令的用法与 `/` `.` `~` 这些符号的含义吗？
- 你知道 Linux 中权限 `rwx` 的含义吗？
- 请问你还懂得哪些与 GNU/Linux 相关的知识呢~

## 题解

1、`ls` ：列出指定目录中的文件；`/` ：根目录； `~` ：家目录 ；`.` ：当前目录。<br>
2、`r` ：read，允许读取文件内容； `w` ： write，允许修改文件内容`x`。<br>
3、GNU项目是一个完全自由的操作系统，提供新新许多基础工具和软件包。<br>
Linux是操作系统的内核，负责管理计算机硬件资源，并提供与硬件的接口。

---
