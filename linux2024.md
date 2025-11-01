## 0. 聪明的吗喽

一个小猴子边上有 100 根香蕉，它要走过 50 米才能到家，每次它最多搬 50 根香蕉，（多了就拿不动了），它每走 1 米就要吃掉一根，请问它最多能把多少根香蕉搬到家里。

（提示：他可以把香蕉放下往返走，但是必须保证它每走一米都能有香蕉吃。也可以走到 n 米时，放下一些香蕉，拿着 n 根香蕉走回去重新搬 50 根。）

## 题解

本题主要思路：<br>
为了最大程度保留香蕉数，就要减少来回次数。<br>
| 阶段 | 剩余香蕉数 | 单次来回次数 |
| --- | --- | --- |
| 起点-25米 | 100根 | 3次 |
| 25米-50米 | 50根 | 2次 |
| 最后一程 | 25根 | 1次 |

最后剩余25根。

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

本题主要考察sizeof、strlen和strcmp。

| | sizeof运算符 | strlen()函数 |
| --- | --- | --- |
| 本质 | 关键字，编译时运算符 | 标准库函数 |
| 头文件 | 不需要 | <string .h> |
| 计算时间 | 编译时 | 运算时 |
| 参数类型 | 数据类型,变量,表达式 | 字符串指针(必须\0结尾)
| 返回值内容 | 占用的总字节数 | \0前的字符个数 |
| 处理\0 | 包含\0 | 不包含\0 |

` strcmp ` 用来比较两个字符串，如果相等，结果为0。

---
<br>
本题主要思路：

` char p0[] = "I love Linux" `
<br> sizeof(p0) = 13 
<br> strlen(p0) = 12 

` const char *p1 = "I love Linux\0Group"; `
<br> p1是指向字符串常量的指针
<br> sizeof(p1) = 8 
<br> strlen(p1) = 12 

 ` char p2[] = "I love Linux\0"; `
<br> p2是一个字符数组
<br> sizeof(p2) = 14 
<br strlen(p2) = 12 

最后输出：
```
0 0 
0 1
```

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

本题主要考察浮点数表示：某些十进制小数在二进制系统中无法准确表示。

---
<br>
本题主要思路：

` b - a ` 值为 0.1 ，但由于 0.1 用二进制无法精准表示，所以实际在程序中 b - a 的值和 0.1 有误差 ，输出` b - a == ex is false `。<br>
` B - A ` 值为 1 ， 用二进制表示没有误差，所以程序算出的值和 B - A 的值没有误差，输出` B - A == EX is true `。

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

本题主要运用分治递归求平均值思想以及位运算。<br>
分治疗递归求平均值：<br>
把数组拆成左右两半各自求平均，最后再把两个平均求一个平均。<br>
位运算求平均值：<br>
` a + b = (a & b)*2 + (a ^ b) `<br>
右移一位就是除以2。

---
<br>
本题主要思路：
```c
int mid = (start + end) / 2;
int leftAvg = average(nums, start, mid);
int rightAvg = average(nums, mid + 1, end);
```
实现把数组拆成左右两半各自求平均值。

然后将得到的两个数求平均： ` return (leftAvg & rightAvg) + ((leftAvg ^ rightAvg) >> 1); `

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

本题中：<br>
全局变量：

` int i = 1; ` <br>
` static int j = 15; `

调用func()函数：<br>
函数内部定义一个局部变量` int i = 10 `，在func函数中使用的i是这个局部变量i，遮蔽了全局变量。
```c
if (i > 5) i++; // i 自增为 11。
printf("i = %d, j = %d\n", i, j); // 打印局部 i和全局静态 j。
return i % j; // 计算 11 % 15，结果是 11。
```

返回main函数：<br>
a 接收 func() 的返回值，所以 a = 11。<br>
` printf("i = %d, j = %d\n", i, j); ` 使用的是全局 i（仍然是 1）和 j（15）。

最后输出：
```c
i = 11, j = 15
a = 11
i = 1, j = 15
```

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

本题主要考察：<br>

| 写法 | 谁是const |
| --- | --- |
| `const int *p` | *p 是 const，p可变 |
| `int * const p` | p 是 const，*p 可变 |
| `const int * const p` | p 和 *p 都 const |

本题主要思路：<br>
` const int *p = &a; ` p指向的内容不能改，*p 本身可改。<br>
` int * const q = &b; `q 本身不能改,值能改,*q 是可改。<br>
` *p = 3, q = &a; ` 存在错误：` *p = 3 `不能改内容，` q = &a `不能改指针。<br>
` const int * const r = &a; `r 本身不能改、内容也不能改，两个方向都锁死。<br>
` *r = 4, r = &b; `：` *r=4 `不能改值，` r=&b `不能改指针。<br>

正确改法：<br>
```c
int main(int argc, char **argv) {
    int a = 1, b = 2;
    const int *p = &a;   // p可以换指向，但不能改a
    int * const q = &b;  // q不能换指向，但能改b

    p = &b;       

    *q = 3;       

    const int * const r = &a;

    return 0;
}
```

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

本题主要考察argc和argv。<br>
argc：argument count，命令行参数个数。<br>
argv：argument vector，字符串数组，保存每一个参数字符串。<br>
int溢出：<br>
因为 C 的有符号整型是 二进制补码储存。<br>
最大正数加 1。<br>
就会变成最高位 1（二进制）。<br>
那在补码表示里就是一个负数。<br>
所以一定会从正 → 正 → 正 → 最后变负。

---
<br>
本题主要思路：<br>
在while 循环：

| 判定次数 | argc值 |
| --- | --- |
| 第一次判定 | 1 > 0 为真，然后 argc++ => 变成 2 |
| 第二次判定 | 2 > 0 为真，然后 argc 就变 3 |
| ... | 永远都 > 0 |
重复执行直到int 溢出，变负数为止。

对于` --a `：a 从 1 变 0，` --a ` 结果是 0 → 为假<br>
对于` b++ && c-- `：b 是一个溢出来的负数，非 0 ，是 true。所以` c-- `被求值，c 从 0 变 -1。<br>
整个 if 条件 = 1 为真。

进入 for 迭代打印 argv。

由于 argv 只有一个元素（argv[0]），循环只会打印` argv[0] = ./a.out `。

最后输出：
```c
argv[0] = ./a.out
a = 0, b = (某个负数+1), c = -1
```

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

a 是一个 整数数组，其类型是 int[3]。

| 表达式        | 含义 / 输出解释                              |
| ---------- | -------------------------------------- |
| a          | 数组首地址，即 `&a[0]`                        |
| a + 1      | 指向 `a[1]`，即 `&a[1]`，因为步进一个 int         |
| &a         | 指向整个数组的指针，类型是 `int(*)[2]`              |
| &a + 1     | 指向下一个同样长度 int[2] 数组，即 `&a + sizeof(a)` |
| *(a+1)     | 即 `a[1]` ，本题值 = 8                      |
| sizeof(a)  | 数组大小 = 2 * sizeof(int) = 8 字节          |
| sizeof(&a) | &a 是指针，指针大小=8字节（64 bit）                |
<br>
b 是一个指向整个数组 a 的指针，即数组指针。

| 表达式        | 含义 / 输出解释                          |
| ---------- | ---------------------------------- |
| *b         | 代表数组 a 本身，地址=&a[0]                 |
| *b + 1     | 指向 a[1]，即 &a[1]                    |
| b          | 等于 &a                              |
| b + 1      | 跳过整个数组 2*4 = 8 字节，即 &a + sizeof(a) |
| *(*b + 1)  | a[1] = 8                           |
| sizeof(*b) | 指整个数组大小 = 8 (2个 int)               |
| sizeof(b)  | b 是指针，指针大小=8 (64bit)               |
<bt>
c 是一个 指针数组，里面包含2个 int* 类型元素，每一个都指向 a 内的元素。

| 表达式          | 含义 / 输出解释                       |
| ------------ | ------------------------------- |
| c            | 数组首地址 = &c[0]                   |
| c + 1        | 指向 c[1] ，步进一个指针大小               |
| c[0]         | = a = &a[0]                     |
| c[1]         | = a+1 = &a[1]                   |
| *c[1]        | a[1] = 8                        |
| sizeof(c)    | 整个数组大小 = 2个指针 = 16 字节 (64bit平台) |
| sizeof(c[0]) | 是一个指针 = 8字节                     |

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

本题主要考察宏的展开。<br>
` a##b `将两个变量名粘在一起，即有新的变量名：ab。

---
<br>
本题主要思路：<br>

```c
int CONCAT(x, 1) = 5;
int CONCAT(y, 2) = 3;
```
宏展开得到：
```c
int x1 = 5;
int y2 = 3;
```
```c
SQUARE(x1 + 1)  ---->  x1 + 1 * x1 + 1
SQUARE(y2)      ---->  y2 * y2
```
```c
#define MAX(a, b) (a > b) ? a : b; // 有分号，分号参与展开
```
带入得到：
```c
MAX(SQUARE(x1 + 1), SQUARE(y2))
----> ( x1 + 1 * x1 + 1 > y2 * y2 ) ? x1 + 1 * x1 + 1 : y2 * y2;
```
` SQUARE(x1 + 1) `：x1 + 1 * x1 + 1 = 5 + 1 * 5 + 1 = 11。<br>
` SQUARE(y2) `：3 * 3 = 9。<br>
` PRINT `：` printf("嘻嘻，结果你猜对了吗，包%d滴\n", max); `

最终输出："嘻嘻，结果你猜对了吗，包11滴"

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

本题主要考察数组合并、排序和去重。

---
<br>
本题主要思路：<br>

合并数组，排序，剔除相同元素，结果写入 res 。<br>
```c
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

```

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

本题主要考察指针 + 类型 + 对齐 + 地址偏移，即指针类型决定 +n 是移动多少字节。<br>
加多少由cast类型决定，不由数组决定。<br>
小端存储就是低字节放低地址，比如数字2真正的储存内存为0x02 00 00 00 00 00 00 00....最前面那个 0x02 在最低地址，后面全是 00 填着。

---
<br>
本题主要思路：<br>

` void *a[] = {(void *)1, (void *)2, (void *)3, (void *)4, (void *)5}; ` <br>
这个 a 是一个数组，每个元素是 void * ，一个指针 = 8字节，所以数组 a 占 5 * 8 = 40字节。 <br>
` *((char *)a + 1) ` (char*)a → 按字节移动， a 数组首地址，当作 char* ，+1 就是往后移动1字节，第一字节就是 0x01 ，输出1。<br>
` *(int *)(char *)a + 1 ` 先 (char*)a，再 cast 成 (int*) → 4 byte步长读取，(int) a = 前4字节是 00 00 00 00 00 00 00 01 (小端排 1)，输出 1+1=2 。<br>
` *((int *)a + 2) ` (int*)a → 每次 +2 是 2 * 4 bytes = 8 bytes，8 bytes 刚好就是一个指针大小，所以这是等价 (int)(&a[1])
，每指针8 bytes ，而a[1] = 2， 输出2。<br>
` *((long long *)a + 3) ` (long long) 8bytes，+3 = 3 * 8 = 24byte = a[3] = 4 ，输出4。<br>
` *((short *)a + 4) `(short*) → 步长2 byte，+4 = 8 bytes = a[1]位置，a[1] = 2 → 小端低2字节就是2，输出2。

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
char string[0] 的含义与使用

char string[0] 是 GNU 扩展（zero-length array）。现代标准 C（C99）里推荐使用 char string[];（灵活数组成员，flexible array member）。两者用途相同：作为结构体尾部附加可变长度数据的占位符，不占据 sizeof 的空间。

因为 string 不占空间，所以 sizeof(Node) 不包含字符串所需的额外字节。程序中通过 malloc(sizeof(Node) + (strlen(s) + 1) * sizeof(char)) 分配了结构体本体加上字符串所需的空间。

P->string 的地址就是紧接在结构体实际成员后面的内存，strcpy 可以把字符串拷进去，这是常用的“struct with trailing data”技巧。

---
<br>
本题主要思路：<br>
结构体定义：

```c
typedef struct node {
    long long a;         // 8 字节
    union data b;        // 占用 8 字节（double 最大决定大小）
    void (*change)(struct node *n); // 函数指针， 8 字节
    char string[0];      // 零长度数组（GCC 扩展）/ flexible array member 类似成员（大小为0）
} Node;
```
` const char *s = "WELCOME TO XIYOULINUX_GROUP!"; `计算该字符串长度：` strlen(s) = 28 `不含“\0”，字符串长度为28 + 1 = 29。<br>
` Node *P = (Node *)malloc(sizeof(Node) + (strlen(s) + 1) * sizeof(char)); `，因为sizeof(Node) = 24，所以开辟总空间大小：24 + 29 = 53。<br>
相对于p的地址偏移为：<br>
0..7    : long long a <br>
8..15   : union data b <br>
16..23  : 函数指针 change <br>
24..52  : string 的存放空间（29 字节）<br>
` strcpy(P->string, s); ` 将字符拷贝到偏移 24 处开始的内存中，包含终止符。<br>
` P->change = func; ` 把函数指针指向 func。 <br>
` P->change(P);` 调用 func(P)，函数遍历 node->string 的每个字符并调用 tolower，将大写字母变小写。

最后输出` welcome to xiyoulinux_group! `

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
