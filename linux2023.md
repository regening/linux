## 0. 鼠鼠我啊，要被祸害了

有1000瓶水，其中有一瓶有毒，小白鼠只要尝一点带毒的水，24小时后就会准时死亡。至少要多少只小白鼠才能在24小时内鉴别出哪瓶水有毒？

## 题解

本题主要思路：<br>

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

本题主要考察

---
<br>
本题主要思路：<br>


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

本题主要考察

---
<br>
本题主要思路：<br>


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

本题主要考察

---
<br>
本题主要思路：<br>


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

本题主要考察

---
<br>
本题主要思路：<br>


---

## 7. 静…态…

1. 如何理解关键字`static`？
2. `static`与变量结合后有什么作用？
3. `static`与函数结合后有什么作用？
4. `static`与指针结合后有什么作用？
5. `static`如何影响内存分配？

## 题解

本题主要考察静态函数static。<br>
static表示所的的定义变量为静态变量，静态变量指程序开始运行后，只在第一次运用时进行初始化处理，后面运行即使再经过初始化该静态变量，该值保持程序运行的结果，不再进行初始化。


---

## 8. 救命！指针！

数组指针是什么？指针数组是什么？函数指针呢？用自己的话说出来更好哦，下面数据类型的含义都是什么呢？

```c
int (*p)[10];
const int* p[10];
int (*f1(int))(int*, int);
```

## 题解

本题主要考察

---
<br>
本题主要思路：<br>


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

本题主要考察

---
<br>
本题主要思路：<br>


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

本题主要考察

---
<br>
本题主要思路：<br>


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

本题主要考察

---
<br>
本题主要思路：<br>


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

本题主要考察

---
<br>
本题主要思路：<br>


---

## 13. GNU/Linux (选做)

注：嘿！你或许对Linux命令不是很熟悉，甚至你没听说过Linux。但别担心，这是选做题，了解Linux是加分项，但不了解也不扣分哦！

你知道`cd`命令的用法与 `/` `.` `~` 这些符号的含义吗？
请问你还懂得哪些与 GNU/Linux 相关的知识呢~

1、`cd` ：切换目录；`/` ：根目录； `~` ：家目录 ；`.` ：当前目录。<br>
2、GNU项目是一个完全自由的操作系统，提供新新许多基础工具和软件包。<br>
Linux是操作系统的内核，负责管理计算机硬件资源，并提供与硬件的接口。

---
