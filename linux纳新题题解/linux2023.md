## 0. 鼠鼠我啊，要被祸害了

有1000瓶水，其中有一瓶有毒，小白鼠只要尝一点带毒的水，24小时后就会准时死亡。至少要多少只小白鼠才能在24小时内鉴别出哪瓶水有毒？

## 题解

本题主要思路：  <br>

因为只有 24 小时，只有一次“测验”机会（喝了有毒就死、24 小时后才能看结果），用 n 只老鼠可以区分 2^n 种不同情况，即每只老鼠存活/死亡两种状态组合。要能区分 1000 瓶，就需要满足 2^n >= 1000。

2^10 = 1024，所以最小 n = 10。

把瓶子编号为 0 到 999，写成 10 位二进制。第 1 只老鼠喝所有第 1 位为 1 的瓶子混合物，第 2 只老鼠喝所有第 2 位为 1 的瓶子，以此类推。24 小时后读出哪几只老鼠死亡，把死亡（1）/存活（0）按位组成一个二进制数，就是被毒瓶的编号。


---

## 1. 先预测一下~

按照函数要求输入自己的姓名试试~

```c
char *welcome() {
    // 请你返回自己的姓名
}
int main(void) {
    char *a = welcome();
    printf("Hi, 我相信 %s 可以面试成功!\n", a);
    return 0;
}
```

## 题解

```c
char *welcome() {  
    return "李泽莹";
}
int main(void) {
    char *a = welcome();
    printf("Hi, 我相信 %s 可以面试成功!\n", a);
    return 0;
}
```
这种写法主要运用了返回字符串字面量。<br>
或者写成：
```c
char *welcome() {
    static char name[] = "李泽莹";
    return name;
}
int main(void) {
    char *a = welcome();
    printf("Hi, 我相信 %s 可以面试成功!\n", a);
    return 0;
}
```
这种写法运用了` static `，其会使数组在静态区，有整个程序生命周期，不会因为函数退出而结束。

---

## 2. 欢迎来到Linux兴趣小组

有趣的输出，为什么会这样子呢~

```c
int main(void) {
    char *ptr0 = "Welcome to Xiyou Linux!";
    char ptr1[] = "Welcome to Xiyou Linux!";
    if (*ptr0 == *ptr1) {
      printf("%d\n", printf("Hello, Linux Group - 2%d", printf("")));
    }
    int diff = ptr0 - ptr1;
    printf("Pointer Difference: %d\n", diff);
}
```

## 题解

本题主要考察字符串常量区和局部数组、printf返回值、指针减法。<br>
只读常量区：放编译期就确定、运行期间不会改变、也不应该被改的数据，这块内存在运行时通常是只读。

---
<br>
本题主要思路：

` char *ptr0 = "Welcome to Xiyou Linux!"; `这句不会新开数组，只会把内容放在只读常量区。` ptr0 `指针直接储存那块常量的地址。<br>
` char ptr1[] = "Welcome to Xiyou Linux!"; `这句是定义数组，在栈上开出空间储存数组。<br>
这两个地方的字符内容一样，但是内存位置完全不是同一块。

对于` if (*ptr0 == *ptr1) `：<br>
` *ptr0 `就是取 ptr0 指向的第一个字符` w `，` *ptr1 `取 ptr1 数组的首元素` w `。所以 if 条件成立。进行第一句输出。
| 层级 | 内容 | 作用 |
| --- | --- | --- |
| 最内层 | ``printf("") ``| 返回值是 0 |
| 中间层 | `printf("Hello, Linux Group - 2%d", printf("")) ` | 要打印字符串，并在 %d 处替换上面那个返回值 0 |
| 最外层 |``` printf("%d\n", printf(...)) ```| 要打印中间层的返回值23 |

---

## 3. 一切都翻倍了吗

1. 请尝试解释一下程序的输出。
2. 请谈谈对`sizeof()`和`strlen()`的理解吧。
3. 什么是`sprintf()`，它的参数以及返回值又是什么呢？

```c
int main(void) {
    char arr[] = {'L', 'i', 'n', 'u', 'x', '\0', '!'}, str[20];
    short num = 520;
    int num2 = 1314;
    printf("%zu\t%zu\t%zu\n", sizeof(*&arr), sizeof(arr + 0),
           sizeof(num = num2 + 4));
    printf("%d\n", sprintf(str, "0x%x", num) == num);
    printf("%zu\t%zu\n", strlen(&str[0] + 1), strlen(arr + 0));
}
```

## 题解

本题主要考察sizeof运算符、strlen()函数和sprintf()。
| | sizeof运算符 | strlen()函数 |
| --- | --- | --- |
| 本质 | 关键字，编译时运算符 | 标准库函数 |
| 头文件 | 不需要 | <string .h> |
| 计算时间 | 编译时 | 运算时 |
| 参数类型 | 数据类型,变量,表达式 | 字符串指针(必须\0结尾)
| 返回值内容 | 占用的总字节数 | \0前的字符个数 |
| 处理\0 | 包含\0 | 不包含\0 |
sprintf函数返回值为实际输出或写入的字符数量（不含‘\0’）


---
<br>
本题主要思路：

` sizeof(*&arr) `:<br>
 &arr --> int (*)[7] ，*&arr --> arr 本体 (数组)，* & 抵消，所以还是数组本体 --> char[7]。<br>
 ` sizeof(arr) ` 值为 7。

` sizeof(arr + 0) `:<br>
运算符 + 会自动把 ` arr `变成指针` char* `指向` arr[0] `，只有指针才能参与算术运算，数组本题不能做 + 运算。<br>
` sizeof(char*) `值为 8。

` sizeof(num = num2 + 4) `:<br>
不会执行里面的表达式，只会看表达式类型为：int。<br>
所以` sizeof(int) `值为 4。

第一句输出：` 7 8 4 `。

` sprintf(str, "0x%x", num) `:<br>
sprintf根据格式化字符串 "0x%x"，把 num（十六进制）格式化出来，然后把这个格式化后的内容 写入 str 数组。520 的十六进制等于 0x208，格式化 "0x%x" --> 结果 "0x208"，写进字符串，共有 5 个字符。

` printf("%d\n", sprintf(str, "0x%x", num) == num); `

---

## 4. 奇怪的输出

程序的输出结果是什么？解释一下为什么出现该结果吧~

```c
int main(void) {
    char a = 64 & 127;
    char b = 64 ^ 127;
    char c = -64 >> 6;
    char ch = a + b - c;
    printf("a = %d b = %d c = %d\n", a, b, c);
    printf("ch = %d\n", ch);
}
```

## 题解

本题主要考察位运算和位移运算。

---
<br>
本题主要思路：<br>
64 的二进制表示：01000000<br>
127 的二进制表示：01111111<br>
按位与运算(&)：只有两个对应的二进制位都是 1 时，结果才是 1，否则是 0。运算后得到：01000000，即64。<br>
按位异或运算(^)：如果两个对应的二进制位不同，结果为 1，相同则为 0。运算后得到：00111111，即63。<br>
右移运算符(>>)：-64 在 二补码表示下是 11111111 11111111 11111111 11000000，右移 6 位时，由于符号位扩展（对于负数，C 使用算术右移），高位填充的是符号位 1：得到 11111100，即-1。<br>
现在得到；

```
a = 64
b = 63
c = -1
```
` 所以：ch = 64 + 63 - (-1) = 64 + 63 + 1 = 128 `
但是，由于 char 是 8 位的，范围是 -128 到 127，所以 128 会发生 溢出，而在二进制表示中：128 = 10000000 (超出 `char` 最大范围)，这个值会溢出并变为 -128，因此 ch = -128。

---

## 5. 乍一看就不想看的函数

*“人们常说互联网凛冬已至，要提高自己的竞争力，可我怎么卷都卷不过别人，只好用一些奇技淫巧让我的代码变得高深莫测。”*

这个`func()`函数的功能是什么？是如何实现的？

```c
int func(int a, int b) {
    if (!a) return b;
    return func((a & b) << 1, a ^ b);
}
int main(void) {
    int a = 4, b = 9, c = -7;
    printf("%d\n", func(a, func(b, c)));
}
```

## 题解

本题主要考察位运算和递归。

---
<br>
本题主要思路：

对于 `func` 函数：使用了递归和位运算来实现加法。<br>
a & b： 计算两个数的按位与操作，得到两数中各位都为 1 的位置。<br>
a ^ b： 计算两个数的按位异或操作，得到两数不同的各位。 <br>
(a & b) << 1：将按位与的结果左移 1 位，模拟进位。<br>
这个函数是模拟逐位加法的过程：<br>
a ^ b 计算的是不考虑进位的部分。<br>
a & b 计算的是进位，左移后加到下一位。

当 a == 0 时，意味着没有进位了，返回 b。因为 a ^ b 中的每一位已经是正确的和，且没有进位需要处理了。即递归终止。

9 的二进制表示是：00000000 00000000 00000000 00001001<br>
-7 的二进制表示是：11111111 11111111 11111111 11111001（二补码）<br>


```
第一次递归：
a = 9, b = -7
a & b = 00000000 00000000 00000000 00001001 & 11111111 11111111 11111111 11111001 = 00000000 00000000 00000000 00001001 = 9
a ^ b = 00000000 00000000 00000000 00001001 ^ 11111111 11111111 11111111 11111001 = 11111111 11111111 11111111 11110000 = -16
(a & b) << 1 = 9 << 1 = 18
递归调用 func(18, -16)。
```
```
第二次递归：
a = 18, b = -16
a & b = 00000000 00000000 00000000 00010010 & 11111111 11111111 11111111 11110000 = 00000000 00000000 00000000 00010000 = 16
a ^ b = 00000000 00000000 00000000 00010010 ^ 11111111 11111111 11111111 11110000 = 11111111 11111111 11111111 11100010 = -30
(a & b) << 1 = 16 << 1 = 32
递归调用 func(32, -30)。
```
```
第三次递归：
a = 32, b = -30
a & b = 00000000 00000000 00000000 00100000 & 11111111 11111111 11111111 11100000 = 00000000 00000000 00000000 00100000 = 32
a ^ b = 00000000 00000000 00000000 00100000 ^ 11111111 11111111 11111111 11100000 = 11111111 11111111 11111111 11000000 = -64
(a & b) << 1 = 32 << 1 = 64
递归调用 func(64, -64)。
```
```
第四次递归：
a = 64, b = -64
a & b = 00000000 00000000 00000000 01000000 & 11111111 11111111 11111111 11000000 = 00000000 00000000 00000000 01000000 = 64
a ^ b = 00000000 00000000 00000000 01000000 ^ 11111111 11111111 11111111 11000000 = 11111111 11111111 11111111 10000000 = -128
(a & b) << 1 = 64 << 1 = 128
递归调用 func(128, -128)。
```
```
第五次递归：
a = 128, b = -128
a & b = 00000000 00000000 00000000 01000000 & 11111111 11111111 11111111 10000000 = 00000000 00000000 00000000 01000000 = 128
a ^ b = 00000000 00000000 00000000 01000000 ^ 11111111 11111111 11111111 10000000 = 11111111 11111111 11111111 00000000 = -256
(a & b) << 1 = 128 << 1 = 256
递归调用 func(256, -256).
```
```
第六次递归：
a = 256, b = -256
a & b = 00000000 00000000 00000000 01000000 & 11111111 11111111 11111111 10000000 = 00000000 00000000 00000000 01000000 = 256
a ^ b = 00000000 00000000 00000000 01000000 ^ 11111111 11111111 11111111 10000000 = 11111111 11111111 11111111 00000000 = -512
(a & b) << 1 = 256 << 1 = 512
func(512, -512)
```
经过几轮递归，当 a 变为 0 时，递归停止，返回值是 b，即递归的最外层会返回 -16，然后逐层传递。
最终从 func(4, -16) 计算出来 func(9, -7) 的返回结果是 -10。

---

## 6. 自定义过滤

请实现`filter()`函数：过滤满足条件的数组元素。

提示：使用函数指针作为函数参数并且你需要为新数组分配空间。

```c
typedef int (*Predicate)(int);
int *filter(int *array, int length, Predicate predicate,
            int *resultLength); /*补全函数*/
int isPositive(int num) { return num > 0; }
int main(void) {
    int array[] = {-3, -2, -1, 0, 1, 2, 3, 4, 5, 6};
    int length = sizeof(array) / sizeof(array[0]);
    int resultLength;
    int *filteredNumbers = filter(array, length, isPositive,
                                  &resultLength);
    for (int i = 0; i < resultLength; i++) {
      printf("%d ", filteredNumbers[i]);
    }
    printf("\n");
    free(filteredNumbers);
    return 0;
}
```

## 题解

本题主要考察函数指针和动态内存分配。

---
<br>
本题主要思路：

filter()函数实现：<br>
遍历原始数组，对每个元素应用传入的 predicate 函数。<br>
统计符合条件的元素数量，为符合条件的元素分配足够的内存。<br>
再次遍历原始数组，将符合条件的元素放入新数组中。

```c
#include <stdio.h>
#include <stdlib.h>

typedef int (*Predicate)(int);

int *filter(int *array, int length, Predicate predicate, int *resultLength) {
    int count = 0;  // 统计符合条件的元素数量
    for (int i = 0; i < length; i++) {
        if (predicate(array[i])) {
            count++;
        }
    }
    
    // 为符合条件的元素分配内存
    int *result = (int *)malloc(count * sizeof(int));
    if (result == NULL) {
        *resultLength = 0; // 如果内存分配失败，返回NULL
        return NULL;
    }

    int index = 0; // 将符合条件的元素复制到新数组中
    for (int i = 0; i < length; i++) {
        if (predicate(array[i])) {
            result[index++] = array[i];
        }
    }
    
    *resultLength = count;
    return result;
}

// Predicate 函数，判断数字是否为正数
int isPositive(int num) {
    return num > 0;
}

int main(void) {
    int array[] = {-3, -2, -1, 0, 1, 2, 3, 4, 5, 6};
    int length = sizeof(array) / sizeof(array[0]);
    int resultLength;
    
    // 调用 filter 函数，过滤正数
    int *filteredNumbers = filter(array, length, isPositive, &resultLength);
    
    // 输出过滤后的结果
    for (int i = 0; i < resultLength; i++) {
        printf("%d ", filteredNumbers[i]);
    }
    printf("\n");

    // 释放分配的内存
    free(filteredNumbers);

    return 0;
}
```

---

## 7. 静…态…

1. 如何理解关键字`static`？
2. `static`与变量结合后有什么作用？
3. `static`与函数结合后有什么作用？
4. `static`与指针结合后有什么作用？
5. `static`如何影响内存分配？

## 题解

1.` static `理解：<br>
对于变量：可以改变变量的生命周期，在第一次调用时分配内存，直到程序结束时才释放。<br>
对于函数：可以改变函数的作用域，使得该函数仅在当前文件内可见，避免了被外部文件访问。

2.` static `与变量结合作用：<br>
延长变量的生命周期：变量的生命周期从函数执行结束变为整个程序运行期间。即使函数返回，static 变量的值会保持不变，下次调用该函数时，static 变量会继续使用上次的值。<br>
作用域限制：static 变量只能在定义它的函数或文件中访问，不能在其他函数或文件中访问。

3.` static `与函数结合作用：<br>
作用域限制：静态函数的作用域仅限于当前源文件。它在文件外部不可见，也不能被其他文件中的代码调用。<br>
避免命名冲突：static的作用域仅限于各自的源文件，可以避免不同文件中的同名函数发生冲突。

4.` static `与指针结合作用：<br>
指针指向的内存是静态的：如果一个指针是静态的，它指向的指针本身的地址在程序整个运行期间都保持不变。<br>
指针类型的静态变量：当 static 用于指针类型的变量时，它指向的地址在函数执行完后仍然存在，而不会被销毁。

5.` static `影响内存分配：<br>
静态存储区：被 static 修饰的变量都会在程序开始时分配内存，程序结束时释放。它们不会随着函数的调用和返回而创建或销毁。<br>
全局变量和静态局部变量：被 static 修饰的全局变量和局部变量在静态存储区分配内存。它们的值在程序的整个生命周期内都保持不变。<br>
静态函数：静态函数的代码段存在于程序的只读存储区，而不是栈区。<br>
栈区和堆区的区别：栈区中的局部变量在函数执行时分配内存，函数返回时销毁。而静态变量则始终存储在静态存储区，不会被销毁。

---

## 8. 救命！指针！

数组指针是什么？指针数组是什么？函数指针呢？用自己的话说出来更好哦，下面数据类型的含义都是什么呢？

```c
int (*p)[10];
const int* p[10];
int (*f1(int))(int*, int);
```

## 题解

| 名称 | 含义 |
|---|---|
| 数组指针 | 指针指向一个数组整体 | 
| 指针数组 | 数组里每个元素都是指针 |
| 函数指针 | 指针指向一个函数 | 


| 类型 | 中文解释 | 分类 |
|---|---|---|
| int (*p)[10]; | `p` 指向一个有 10 个 int 的数组 | 数组指针 |
| const int* p[10]; | `p` 是一个数组，数组中每个元素是指针 | 指针数组 |
| int (*f1(int))(int*, int); | `f1` 是一个函数，返回一个函数指针，该函数指针指向函数：参数 `(int*, int)` 返回 `int` | 函数指针 |



---

## 9. 咋不循环了

程序直接运行，输出的内容是什么意思？

```c
int main(int argc, char* argv[]) {
    printf("[%d]\n", argc);
    while (argc) {
      ++argc;
    }
    int i = -1, j = argc, k = 1;
    i++ && j++ || k++;
    printf("i = %d, j = %d, k = %d\n", i, j, k);
    return EXIT_SUCCESS;
}
```

## 题解

本题主要考察int 溢出 和 && || 短路求值。

---
<br>
本题主要思路：

```c
printf("[%d]\n", argc);
while (argc) {
  ++argc;
}
```
程序运行时 argc 至少是 1，即程序名。所以第一行输出 1。<br>
while(argc) 是死循环增长 int，直到溢出变成负数，当变成 0 时退出，所以最后 argc 变成 0。<br>
第二段中，刚开始：
```c
i = -1;
j = 0;
k = 1;
```
` i++ && j++ || k++; `:<br>
i++: 返回 -1（非0），i 自增后变 0。左边 true && j++ ⇒ 必须看 j++。<br>
j++：返回 0（false），j 自增后变 1。true && false --> false。<br>
因此 || 右边必须执行 k++，返回 1（true），k 自增后变 2。

最终值：
```c
i = 0;
j = 1;
k = 2;
```

---

## 10. 到底是不是TWO

```c
#define CAL(a) a * a * a
#define MAGIC_CAL(a, b) CAL(a) + CAL(b)
int main(void) {
  int nums = 1;
  if(16 / CAL(2) == 2) {
    printf("I'm TWO(ﾉ>ω<)ﾉ\n");
  } else {
    int nums = MAGIC_CAL(++nums, 2);
  }
  printf("%d\n", nums);
}
```

## 题解

本题主要思路：<br>
先看if：<br>
` if(16 / CAL(2) == 2) `宏展开得到` if (16 / 2 * 2 * 2 == 2) `，算出 32 == 2，结果为false。进入else。<br>
` int nums = MAGIC_CAL(++nums, 2); `宏展开` int nums = ++nums * ++nums * ++nums + 2 * 2 * 2; `<br>
` int nums = ... `创建了一个新的局部nums。<br>
外层nums:` int nums = 1; `，这个nums在else中不能改变，所以最后打印 1。

---

## 11. 克隆困境

试着运行一下程序，为什么会出现这样的结果？

直接将`s2`赋值给`s1`会出现哪些问题，应该如何解决？请写出相应代码。

```c
struct Student {
    char *name;
    int age;
};

void initializeStudent(struct Student *student, const char *name,
                       int age) {
    student->name = (char *)malloc(strlen(name) + 1);
    strcpy(student->name, name);
    student->age = age;
}
int main(void) {
    struct Student s1, s2;
    initializeStudent(&s1, "Tom", 18);
    initializeStudent(&s2, "Jerry", 28);
    s1 = s2;
    printf("s1的姓名: %s 年龄: %d\n", s1.name, s1.age);
    printf("s2的姓名: %s 年龄: %d\n", s2.name, s2.age);
    free(s1.name);
    free(s2.name);
    return 0;
}
```

## 题解

本题存在问题：<br>
s1 = s2; 是浅拷贝：只复制指针值，不复制指针所指向的数据。<br>
当结构体包含动态分配的指针时，必须做深拷贝，否则无法进行赋值。

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char *name;
    int age;
};

void initial(struct Student *student, const char *name, int age) {
    student->name = malloc(strlen(name) + 1);
    if (!student->name) { perror("malloc"); exit(1); }
    strcpy(student->name, name);
    student->age = age;
}

void copy(struct Student *dst, const struct Student *src) {
    dst->name = malloc(strlen(src->name) + 1);
    if (!dst->name) { perror("malloc"); exit(1); }
    strcpy(dst->name, src->name);
    dst->age = src->age;
} // copy为目标分配了独立内存，两个结构互不影响，释放各自内存安全。

void free(struct Student *s) {
    free(s->name);
    s->name = NULL;
}

int main(void) {
    struct Student s1, s2;
    initial(&s1, "Tom", 18);
    initial(&s2, "Jerry", 28);

    copy(&s1, &s2); 

    printf("s1的姓名: %s 年龄: %d\n", s1.name, s1.age);
    printf("s2的姓名: %s 年龄: %d\n", s2.name, s2.age);

    free(&s1);
    free(&s2);
    return 0;
}
```

---

## 12. 你好，我是内存

作为一名合格的C-Coder，一定对内存很敏感吧~来尝试理解这个程序吧！

```c
struct structure {
    int foo;
    union {
      int integer;
      char string[11];
      void *pointer;
    } node;
    short bar;
    long long baz;
    int array[7];
};
int main(void) {
    int arr[] = {0x590ff23c, 0x2fbc5a4d, 0x636c6557, 0x20656d6f,
                 0x58206f74, 0x20545055, 0x6577202c, 0x6d6f636c,
                 0x6f742065, 0x79695820, 0x4c20756f, 0x78756e69,
                 0x6f724720, 0x5b207075, 0x33323032, 0x7825005d,
                 0x636c6557, 0x64fd6d1d};
    printf("%s\n", ((struct structure *)arr)->node.string);
}
```

## 题解

本题主要思路：

```c
struct structure {
    int foo;        // 4 byte
    union {         
      int integer;
      char string[11];
      void *pointer;
    } node;         // 8 byte
    short bar;      // 2 byte
    long long baz;  // 8 byte
    int array[7];   // 28 byte
};
```
arr[] 里：<br>
第一个元素是：0x590ff23c，4字节，这是 struct.structure.foo 的内容。<br>
` union node; `  union 从 arr[1]开始，union 占8字节。
剩下的 arr 里面这堆 0x636c6557 … 明显是 ASCII 反转字节序的英文。
|||
| --- | --- |
| 0x63 | 'c' |
| 0x6c | 'l' |
| 0x65 | 'e' |
| 0x57 | 'W' |
C语言是“低位字节”存在内存低地址：
```
0x636c6557  
在 memory里排法变成 (从低地址往高)：  
57 65 6c 63
```
真实输出就是一个正常可读的英文字符串。即` Welcome to Xiyou Linux Group [2023%x]Welcome... `

---

## 13. GNU/Linux (选做)

注：嘿！你或许对Linux命令不是很熟悉，甚至你没听说过Linux。但别担心，这是选做题，了解Linux是加分项，但不了解也不扣分哦！

你知道`cd`命令的用法与 `/` `.` `~` 这些符号的含义吗？
请问你还懂得哪些与 GNU/Linux 相关的知识呢~

## 题解

1、`cd` ：切换目录；`/` ：根目录； `~` ：家目录 ；`.` ：当前目录。<br>
2、GNU项目是一个完全自由的操作系统，提供新新许多基础工具和软件包。<br>
Linux是操作系统的内核，负责管理计算机硬件资源，并提供与硬件的接口。

---
