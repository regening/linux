## 0. 拼命的企鹅

一只企鹅在爬山，每隔一段路都会遇到一块石头。第 1 块石头重量是 `a`，每往上走一段路，石头重量就会变成上一段的平方。企鹅可以选择把某些石头捡起来，最后把捡到的石头重量相乘。

它怎样捡石头，才能得到重量乘积恰好是 `a` 的 `b` 次方的石头？（比如 `b = 173` 时， 要捡哪些石头？）

## 题解

本题主要考察二进制。

| 第几块石头 | 石头重量 | 
| --- | --- | 
| 第一块 | a^(2^0) | 
| 第二块 | a^(2^1) | 
| 第三块 | a^(2^2) | 
| ... | ... |
| 第二块 | a^(2^(n-1)) | 
---
<br>
本题的主要思路为：   <br>
选择一些 2 的幂的和，使得它们的和等于 b。似于二进制表示：我们可以将 b 表示成若干个 2 的幂的和。例如，b = 173 的二进制表示是 10101101 ，173 = 2^7 + 2^5 + 2^4 + 2^2 + 2^0，因此企鹅需要捡起第 1、3、4、6、8 块石头。

---

## 1. 西邮Linux欢迎你啊

请解释以下代码的运行结果。

```c
int main() {
    if (printf("Hi guys! ") || printf("Xiyou Linux ")) {
        printf("%d\n", printf("Welcome to Xiyou Linux 2%d", printf("")));
    }
    return 0;
}
```

## 题解

本题主要考察printf函数和逻辑操作符||。

|| 是逻辑“或”运算符。它用于判断两个条件之一是否为真。

printf两个核心特性:<br>
1.输出行为:
printf() 会将字符串中的内容原样打印到标准输出<br>
2.返回值
它返回的是成功输出的字符数（不包括字符串结束符 \0）。

---
<br>
本题主要思路：<br>
`printf("Hi guys! ") `返回 9，一个非零值，相当于 true。由于 || 运算符的短路性，第二个printf不会被执行。

if 语句的条件成立，程序进入 if 判断。

| 层级 | 内容 | 作用 |
| --- | --- | --- |
| 最内层 | ```printf("") ```| 返回值是 0 |
| 中间层 | ```printf("Welcome to Xiyou Linux 2%d", printf("")) ```| 要打印字符串，并在 %d 处替换上面那个返回值 0 |
| 最外层 |``` printf("%d\n", printf(...)) ```| 要打印中间层的返回值 |

最后输出代码``` Welcome to Xiyou Linux 2025 ```

---

## 2. 可以和 `\0` 组一辈子字符串吗？

你能找到成功打印的语句吗？你能看出每个 `if` 中函数的返回值吗？这些函数各有什么特点？

```c
int main() {
    char p1[] = { 'W', 'e', 'l', 'c', 'o', 'm', 'e', '\0' };
    char p2[] = "Join us\0", p4[] = "xiyou_linux_group";
    const char* p3 = "Xiyou Linux Group\0\n2025\0";
    if (strcmp(p1, p2)) {
        printf("%s to %s!\n", p1, p2);
    }
    if (strlen(p3) > sizeof(p3)) {
        printf("%s", p3);
    }
    if (sizeof(p1) == sizeof(p2)) {
        printf("%s", p4);
    }
    return 0;
}
```

## 题解

本题主要考察strcmp, strlen, 和 sizeof 函数。

strcmp 是一个字符串比较函数，返回值为 0 表示两个字符串相同；如果返回值非 0，则表示字符串不同。
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
p1 的值是 {'W', 'e', 'l', 'c', 'o', 'm', 'e', '\0'}，也就是 "Welcome"（一个字符数组）。p2 的值是 "Join us\0"，这是一个字符数组，包含了 "Join us" 和一个 \0 结束符。<br>
由于 "Welcome" 和 "Join us" 不相同，因此 strcmp(p1, p2) 的返回值为 非零值（负数），条件成立。

sizeof(p3) 返回的是char类型指针大小8字节；strlen(p3) 返回的是25(Xiyou Linux Group\0\n2025\0 有25个字符)。strlen(p3) > sizeof(p3) 为 真，条件成立。

sizeof(p1):
p1 的大小是数组中所有字符的总大小，也就是 7 个字符 + 1 个 \0 字符 = 8 字节。<br>
sizeof(p2):
p2 是一个字符数组，包含了 "Join us\0" 字符串。
p2 的大小是数组中所有字符的总大小，也就是 8 个字符（包括结尾的 \0）= 9 字节。<br>
sizeof(p1) 是 8，sizeof(p2) 是 9，因此 sizeof(p1) == sizeof(p2) 为 假，条件不成立。

---

## 3. 数学没问题，浮点数有鬼

这个程序的输出是什么？解释为什么会这样？

```c
int main() {
    float a1 = 0.3, b1 = 6e-1, sum1 = 0.9;
    printf("a1 + b1 %s sum1\n", (a1 + b1 == sum1) ? "==" : "!=");
    float a2 = 0x0.3p0, b2 = 0x6p-4, sum2 = 0x0.9p0;
    printf("a2 + b2 %s sum2\n", (a2 + b2 == sum2) ? "==" : "!=");
    return 0;
}
```

## 题解

本题主要考察浮点数运算、打印以及十六进制浮点数表示。

浮点数的精度问题：<br>
浮点数在计算机中是以二进制近似表示的，某些十进制或十六进制数字在计算机内部无法精确表示，导致存在精度误差。<br>
浮点数表示问题：<br>
在浮点数运算中，十六进制表示法有时存在一些与十进制表示法不同的精度误差，不同的数值系统在存储和运算时有不同的精度表现。<br>
十六进制表示：0x<整数>.<小数>p<指数>

---
<br>
本题主要思路：<br>
a1 = 0.3: 这是一个十进制浮点数，表示 0.3。<br>
b1 = 6e-1: 这是科学计数法表示的浮点数，表示 6 × 10^-1 = 0.6。<br>
sum1 = 0.9: 这是另一个十进制浮点数，表示 0.9。

由于浮点数存储精度的限制，a1 和 b1 的加法结果可能略有误差，导致 a1 + b1 的值并不完全等于 0.9。所以输出“a1 + b1 != sum1“

十六进制浮点数：<br>
a2 = 0x0.3p0: 表示 a2 = 0.3 / 16 * 2^0 = 0.1875。<br>
b2 = 0x6p-4: 表示 b2 = 6 * 2^-4 = 0.375。<br>
sum2 = 0x0.9p0: 表示 sum2 = 0.9 / 16 * 2^0 = 0.5625。<br>
由于十六进制浮点数和十进制浮点数的精度误差，a2 + b2 和 sum2 不完全相等， a2 + b2 ！= sum2 。

---

## 4. 不合群的数字

在一个数组中，所有数字都出现了偶数次，只有两个数字出现了奇数次，请聪明的你帮我看看以下的代码是如何找到这两个数字的呢？

```c
void findUndercoverIDs(int nums[], int size) {
    int xorAll = 0,id_a = 0,id_b = 0;
    for (int i = 0; i < size; i++) {
        xorAll ^= nums[i];
    }
    int diffBit = xorAll & -xorAll;
    for (int i = 0; i < size; i++) {
        if(nums[i] & diffBit){
            id_a ^= nums[i];
        } else {
            id_b ^= nums[i];
        }
    }
    printf("These nums are %d %d\n", id_a, id_b);
}
```

## 题解

本题主要考察逻辑运算异或。

常见逻辑运算：<br>
与：&& 两个都为真，结果才是真。<br>
或：|| 只要一个真，结果就是真。<br>
非：！ 对操作的布尔值取反，<br>
异或：^  用于二进制运算，当两个输入值不同时，输出1；相同时，输出0。

---
<br>
本题主要思路：<br>
在第一步中，``` xorAll ^= nums[i] ```对所有数组元素进行异或操作。数组中出现偶数次的数字会被完全抵消掉，它们会与自己异或为 0，最终 xorAll 只包含两个出现奇数次的数字的异或结果。

```int diffBit = xorAll & -xorAll;```找到 xorAll 中最低位的 1，用来将数组中的两个奇数次出现的数字分开。在xorAll 的二进制表示中，两个数字的不同之处就在于某一位上。

-xorAll 计算的是 xorAll 的二进制补码，即 xorAll 的负数。

`xorAll & -xorAll` 可以得到 xorAll 中最低位的 1，这是一个非零的位，它对应了两个数字在这一位上的不同。

diffBit 是用来将两个奇数次出现的数字分开，它表示了这两个数字在该位上的不同。

现在， xorAll 代表了两个奇数次出现的数字的异或结果，它们在 diffBit 这一位上不同。所以，通过 `ums[i] & diffBit`来判断当前数字在这个位上的值。

如果 `nums[i] & diffBit` 为 1，则说明该数字和另一个奇数次出现的数字在 diffBit 这一位上不同，所以将它放到 id_a 中。否则，将其放到 id_b 中。

因为这个位上的差异将数字分成了两个组，所以每组内的数字只包含一个奇数次出现的数字，异或后，最终 id_a 和 id_b 就分别存储了这两个数字。

---

## 5. 会一直循环吗？

你了解 `argc` 和 `argv` 吗，程序的输出是什么？为什么会这样？

```c
int main(int argc, char* argv[]) {
    printf("argc = %d\n", argc);
    while (argc++ > 0) {
        if(argc < 0){
            printf("argv[0] %s\n", argv[0]);
            break;
        }
    }
    printf("argc = %d\n", argc);
    return 0;
}
```
## 题解

本题主要考察argc和argv了两个参数。

argc: 传递给程序的命令行参数的数量，至少为1（程序本身的名称）。<br>
argv: 一个字符串数组，包含了命令行的所有参数。

溢出问题：argc 是一个整数，当它递增到超过最大值时，会溢出，导致 argc 变为负数， 负溢出值为-2147483648。

---
<br>
本题主要思路：<br>
程序通过 argc++ 递增 argc，直到它溢出为负数。<br>
一旦 argc 变成负数，进入 if (argc < 0)，打印 argv[0] 并退出循环。<br>
最后，打印溢出的 argc 值。

`printf("argc = %d\n", argc);`
在程序开始时，这一行打印的是初始的 argc 值，也就是命令行参数的数量：3（包括程序本身的名称、arg1和arg2）。

`while (argc++ > 0)`
这一行是一个 while 循环，argc++ 表示先判断 argc 是否大于 0，然后再增加 argc 的值。即：在第一次循环时，argc = 3，判断 3 > 0 为真，然后 argc 增加到 4。<br>
在第二次循环时，argc = 4，判断 4 > 0 为真，然后 argc 增加到 5。<br>
这个循环一直继续，直到 argc 增加到一个负数，进入if条件判断。

`if (argc < 0)`
在 while 循环中，检查 argc 是否小于 0。如果 argc 小于 0，程序会打印 argv[0] 并跳出循环。<be>
由于 argc 是一个整型变量，它从初始值开始递增，当 argc 达到一个很大的数时，最终会溢出到负数，在32位或64位的负溢出值都为-2147483648。

`printf("argv[0] %s\n", argv[0]);`当 argc 变为负数时，程序打印 argv[0]。

`printf("argc = %d\n", argc);`
程序打印 argc 的值。由于 argc 在循环过程中已经递增到负数，最终打印的是负溢出值。

---

## 6. `const` 与指针：谁能动，谁不能动？

```c
struct P {
    int x;
    const int y;
};

int main() {
    struct P p1 = { 10, 20 }, p2 = { 30, 40 };
    const struct P p3 = { 50, 60 };
    struct P* const ptr1 = &p1;
    const struct P* ptr2 = &p2;
    const struct P* const ptr3 = &p3;
    return 0;
}
```

说说下列操作是否合法，并解释原因：

`ptr1->x = 100`, `ptr2->x = 300`, `ptr3->x = 500`

`ptr1->y = 200`, `ptr1 = &p2`, `ptr2->y = 400`

`ptr2 = &p1`, `ptr3->y = 600`, `ptr3 = &p1`

## 题解

本题主要考察不同情况下关于指针和结构体的合法性操作，以及 const（常量修饰符）在 C 语言中的作用。

const 修饰数据：该数据不能被修改。<br>
const 修饰指针：<br>
const p*：指向的内容是 const，不能修改内容。<br>
p* const：指针本身是 const，不能更改指针的指向。<br>
const p* const：指针和指向的内容都不能修改。

---
<br>
本题主要思路：<br>
struct P* const ptr1：ptr1 是一个指向 struct P 的常量指针，即指针的值不可变，不能更改 ptr1 指向的对象，但指针所指向对象的内容是可以修改的。<br>
const struct P* ptr2：ptr2 是一个指向常量结构体的指针，即指针所指向的内容不可修改，不能通过 ptr2 修改结构体成员，但指针本身是可以改变的。<br>
const struct P* const ptr3：ptr3 是一个常量指针，且指向的内容也是常量，即指针和指针所指向的内容都不能修改。

ptr1->x = 100：<br>
ptr1 是 常量指针，指向的结构体内容是 可以修改的，合法。


ptr2->x = 300：<br>
ptr2 是 指向常量结构体的指针，意味着不能修改指向的结构体中的任何成员，非法。

ptr3->x = 500：<br>
ptr3 是 常量指针 且指向的结构体是 常量结构体，所以不能修改 ptr3 指向的结构体中的任何成员，非法。

ptr1->y = 200：<br>
ptr1 是常量指针指向 p1，但 p1 的 y 是 常量，非法。

ptr1 = &p2：<br>
ptr1 是 常量指针，意味着指针的值不能改变，非法。

ptr2->y = 400：<br>
ptr2 是 指向常量结构体的指针，通过 ptr2 不能修改 y，y 是常量，非法。

ptr2 = &p1：<br>
ptr2 是 指向常量结构体的指针，可以指向 p1，p1 并没有被声明为常量，合法。

ptr3->y = 600：<br>
ptr3 是 常量指针，且指向的结构体是常量，非法。

ptr3 = &p1：<br>
ptr3 是 常量指针，指针本身不能改变指向，非法。

---

## 7. 指针！数组!

在主函数中定义如下变量:

```c
int main() {
    int a[3] = { 2, 4, 8 };
    int(*b)[3] = &a;
    int* c[3] = { a, a + 1, a + 2 };
    int (*f1(int))(int*, int);
    return 0;
}
```
说说这几个表达式的输出分别是什么？

`a`, `*b`, `*b + 1`, `b`, `b + 1`, `* (*b + 1)`, `c`, `sizeof(a)`, `sizeof(b)`, `sizeof(&a)`, `sizeof(f1)`

## 题解

本题主要考察C语言的表达式，主要包括指针、数组和函数指针等。

---
<br>
本题主要思路：<br>
a 是一个 整数数组，其类型是 int[3]。在 C 中，数组名 a 表示数组的 首元素的地址，即 &a[0]。

<br>a 输出的是数组 a 的首地址，即 &a[0]。

b 是一个指向整个数组 a 的指针；<br> b + 1 是指向 数组 a 后面的位置，即指向 a 后面的一个 int[3] 类型的空间；<br> *b 表示解引用该指针，得到数组 a 本身；<br> *b + 1 表示数组 a 从第一个元素开始，偏移一个位置，指向 a[1]。<br> *(*b + 1) 是对 a[1] 的解引用，即取 a[1] 的值。<br>

*b 输出的值和 a 的输出一样，即 a的首地址，&a[0]。<br> *b + 1 输出的是数组a的第二个元素的地址，即 &a[1]。<br> b 输出的是 a 的地址，即 &a，这与 a的首地址是相同的。<br> b+1 输出的是指向下一个 int[3] 数组位置的地址，即 b 之后的内存位置: &a + sizeof(a)。<br> *(*b + 1) 输出的是 a[1]，即 4。<br>

c 是一个 指针数组，里面包含3个 int* 类型元素，每一个都指向 a 内的元素
 
c 输出的是 c 数组的首地址，即&c[0]，指向 a 数组的指针数组。

sizeof运算符计算所占字节数。<br>
a 是整数数组。<br>
b 是指针数组，所占字节数为8。<br>
&a 类型是 int (*)[3]，即指向包含 3 个整数的数组的指针。

sizeof(a) 输出a数组所占的全部字节数，即 3 * sizeof(int) = 3 * 4 = 12。
sizeof(b) 输出指针数组所占的字节数， 即 8 字节。
sizeof(&a) 输出的是指针 &a 的大小，也就是指针 b 的大小， 即 8 字节。

f1 是一个函数指针的声明，表示 f1 是一个函数，接受一个 int 参数，并返回一个指向接受 int* 和 int 参数的函数的指针，返回值类型是 int。

sizeof(f1) 输出的是 f1 函数指针的大小。函数指针的大小为 8 字节。

---

## 8. 全局还是局部！！！

观察程序输出，思考为什么？

```c
int g;
int func() {
    static int j = 98;
    j += g;
    return j;
}

int main() {
    g += 3;
    char arr[6] = {};
    arr[1] = func();
    arr[0] = func();
    arr[2] = arr[3] = func() + 1;
    arr[4] = func() + 1;
    printf("%s linux\n",arr);
    return 0;
}
```

## 题解

本题主要考察局部变量、全局变量和静态变量。

全局变量：在函数外定义，初始值默认为0，全局变量在函数中不能直接赋值，但可以通过重新定义改变值。作用域为整个程序，定义域从定义处到程序结束。<br>
局部变量：在函数或代码块内定义，作用域为所在函数或代码块区间，定义域为所在函数调用区间。<br>
静态变量：只在程序开始时初始化一次，后续不再初始化，保持程序运行的值。

---

本题主要思路：<br>
进入 main 函数， g = g + 3， 即 g = 3。<br>
从`arr[1] = func()`开始，调用 funs 函数。<br>
在 funs 函数中，首先定义一个静态变量(`static int j = 98`) j = 98，j = j + g，即j = 98 + 3 = 101，所以返回 j = 101 ，arr[1] 取 101 对应的 ACSII 值，为`e`。<br>
同理，arr[0]、 arr[2]、 arr[3]、 arr[4]分别对应 `h` `l` `l` `o`。<br>
最后输出`hello linux`。

---

## 9. 宏函数指针

观察程序结果，说说程序运行的过程：

```c
#define CALL_MAIN(main, x) (*(int (*)(int))*main)(x);
#define DOUBLE(x) 2 * x
int (*registry[1])(int);
int main(int argc) {
    if (argc > 2e3) return 0;
    printf("%d ", argc + 1);
    *registry = (int(*)(int))main;
    CALL_MAIN(registry, DOUBLE(argc + 1));
    return 0;
}
```

## 题解

本题主要考察宏函数指针和递归。

---
<br>
本题主要思路：<br>

对于宏` #define DOUBLE(x) 2 * x ` 在 main 函数中调用时，运行 2*argc + 1 ，如果要实现 2*(argc + 1) ，则将该宏改为` #define DOUBLE(x) 2 * (x) `。

对于 ` (*(int (*)(int))*main)(x) `:<br>
` (int(*)(int)) ` 表示函数指针类型，接收int并返回int。<br>
` *main `: 解引用main指针， main 在这里被当作指针传递。<br>

` *registry = (int(*)(int))main ` 声明一个大小为1的函数指针数组， 每个元素都是指向 int func(int) 类型函数的指针。

` *registry = (int(*)(int))main `: 将 main 函数地址存入 registry 数组。

程序运行：<br>
第一次调用` main(1) `：<br>
argc = 1 ， 第一行输出 2 (1 + 1)。<br>
`CALL_MAIN `调用宏` DOUBLE(x) `运行 2 * 1 + 1 ，得到3 ， 相当于调用 `registry[0](3) `， 即` main(3) `。<br> 

第二次调用` main(3) `：<br>
argc = 3 ， 第一行输出 4 (3 + 1)。<br>
`CALL_MAIN `调用宏` DOUBLE(x) `运行 2 * 3 + 1 ，得到7 ， 相当于调用 `registry[0](7) `， 即` main(7) `。<br> 
git
即 1 3 7 15 31 63 127 255 511 1023 2047 ，当` argc > 2000 `跳出该递归。

最后程序输出 2 4 8 16 32 64 128 256 512 1024 2048。

---

## 10. 拼接 排序 去重

本题要求你编写以下函数，不能改动 `main` 函数里的代码。实现对 `arr1` 和 `arr2` 的拼接、排序和去重。你需要自行定义 `result` 结构体并使用 `malloc` 手动开辟内存。

```c
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
```
## 题解

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

## 11. 指针魔法

用你智慧的眼睛，透过这指针魔法的表象，看清其本质：

```c
void magic(int(*pa)[6], int** pp) {
    **pp += (*pa)[2];
    *pp = (*pa) + 5;
    **pp -= (*pa)[0];
    *pp = (*pa) + ((*(*pa + 3) & 1) ? 3 : 1);
    *(*pp) += *(*pp - 1);
    *pp = (*pa) + 2;
}
int main() {
    int a[6] = { 2, 4, 6, 8, 10, 12 };
    int* p = a + 1,** pp = &p;
    magic(&a, pp);
    printf("%d %d\n%d %d %d\n%d %d\n",*p,**pp,a[1],a[2],a[3],a[5],p-a);
    return 0;
}
```

## 题解

本题主要考察指针相关知识。<br>
& 1 是一个用来检查整数的最低有效位（奇偶性）的技巧。<br>
p - a = 指针偏移量。

---
<br>
本题主要思路：<br>

` int(*pa)[6] ` pa是指向整个数组的指针， ` (*pa) ` 相当于 ` a[i] `。<br>
` int** p ` 是指针的指针，` *pp `得到 p 的值，即指向的地址，
` **pp `得到 p 指向的值。

#### 程序分析：<br>
初始：
```c
int a[6] = { 2, 4, 6, 8, 10, 12 };
int* p = a + 1;     // p 指向 a[1] 
int** pp = &p;      // pp 指向指针p
```
 a = { 2, 4, 6, 8, 10, 12 }， p 指向 a[1] 。

#### 进入 magic 函数：<br>
```c
**pp = **pp + (*pa)[2]
     = *p + a[2] 
     = 4 + 6 = 10
```
 a = { 2, 10, 6, 8, 10, 12 }， p 仍指向 a[1] 。<br>
 `*pp = a + 5 ` ，即让 p 指向a[5] 。

```c
**pp = **pp - (*pa)[0]
     = *p - a[0]
     = 12 - 2 = 10
```
 a = { 2, 10, 6, 8, 10, 10 }， p 仍指向 a[5] = 10 。<br>
```c
*(*pa + 3) = *(a + 3) = a[3] = 8
8 & 1 = 0 ，选择 : 后面的 1
*pp = a + 1  // 让p指向a[1]
```
 a = { 2, 10, 6, 8, 10, 10 }， p 指向 a[1] = 10 。<br>
```c
*(*pp) = *p = a[1]
*(*pp - 1) = *(p - 1) = a[0] = 2
a[1] = a[1] + a[0] = 10 + 2 = 12
```
 a = { 2, 12, 6, 8, 10, 10 }， p 指向 a[1] = 12 。<br>
` *pp = a + 2 ` ，让p指向a[2] 。<br>
 a = {2, 12, 6, 8, 10, 10} ，p 指向 a[2] = 6 。

#### 输出：
*p = a[2] = 6<br>
 **pp = *p = 6 (pp指向p) <br>
 a[1] = 12 <br>
 a[2] = 6 <br>
 a[3] = 8 <br>
 a[5] = 10 <br>
 p - a = 2 (p指向a[2])

---

## 12. 奇怪的循环

你能看明白这个程序怎样运行吗？试着理解这个程序吧！

```c
union data {
    void**** p;
    char arr[20];
};
typedef struct node {
    int a;
    union data b;
    void (*use)(struct node* n);
    char string[0];
} Node;
void func2(Node* node);

void func1(Node* node) {
    node->use = func2;
    printf("%s\n", node->string);
}
void func2(Node* node) {
    node->use = func1;
    printf("%d\n", ++(node->a));
}
int main() {
    const char* s = "Your journey begins here!";
    Node* P = (Node*)malloc(sizeof(Node) + (strlen(s) + 1) * sizeof(char));
    strcpy(P->string, s);
    P->use = func1;
    P->a = sizeof(Node) * 50 + sizeof(union data);
    while (P->a < 2028) {
        P->use(P);
    }
    free(P);
    return 0;
}
```

## 题解

本题主要考察结构体，联合体， 柔性数组。 <br>
柔性数组：<br>
char string[0] ， 不占结构体空间，允许动态扩展。<br>
要求：必须是结构体最后一个成员； 分配内存时计算总需求：sizeof(Node) + 字符串长度 + 1。<br>
联合体内存布局：
```c
union data {
    void**** p;   // 任何指针类型都占用相同空间
    char arr[20]; // 共享同一块内存
};
```
联合体所有成员共享内存，大小为最大成员的大小。

补充：<br>
结构体内存对齐规则:<br>
每个成员按照其对齐要求对齐。<br>
结构体的总大小是最大对齐要求的倍数。<br>
可能需要填充字节来保证对齐。<br>
联合体内存对齐规则:<br>
联合体总大小是其最大基础成员大小的倍数。<br>
所有成员共享同一块内存，不需要填充字节，除非最大成员需要更高的对齐。

---
<br>
本题主要思路：<br>

```c
union data {
    void**** p;    // 4级指针 8字节
    char arr[20];  // 字符数组 20字节
};                 // union为24字节（取最大成员，且为8的整数倍）

typedef struct node {
    int a;                    // 4字节
    union data b;             // 24字节  
    void (*use)(struct node* n); // 函数指针，8字节
    char string[0];           // 柔性数组，不占空间
} Node;
```

结构体大小计算（8字节对齐）：

 int a：4字节，占用1-4,和8对齐<br>
 union data b：20字节，占用8-28，和32对齐 <br>
 void (*use)：8字节，占用32-40 <br>
 char string[0]：不占空间  <br>
 总大小40是8的倍数，不需要额外填充。<br>
 总大小：40字节。
```c
void func1(Node* node) {
    node->use = func2;        // 下次调用func2
    printf("%s\n", node->string);  // 打印字符串
}

void func2(Node* node) {
    node->use = func1;        // 下次调用func1  
    printf("%d\n", ++(node->a));   // 打印并递增a
}
```

创建了一个函数交替调用的模式：

```
func1 → func2 → func1 → func2 → ...
```
```c
const char* s = "Your journey begins here!";
Node* P = (Node*)malloc(sizeof(Node) + (strlen(s) + 1) * sizeof(char));
strcpy(P->string, s);        // 复制字符串到柔性数组
P->use = func1;              // 初始函数指针指向func1
P->a = sizeof(Node) * 50 + sizeof(union data);
sizeof(Node) = 40
sizeof(union data) = 24
P->a = 40 * 50 + 24 = 2000 + 24 = 2024
```
开始循环：<br>
第1次：调用 func1(P) <br>
P->use 从 func1 改为 func2 <br>
输出："Your journey begins here!" <br>
P->a 保持 2024

第2次：调用 func2(P) <br>
P->use 从 func2 改为 func1 <br>
P->a 从 2024 增加到 2025 <br>
输出：2025

第3次：调用 func1(P) <br>
P->use 从 func1 改为 func2 <br>
输出："Your journey begins here!" <br>
P->a 保持 2025

第4次：调用 func2(P) <br>
P->use 从 func2 改为 func1 <br>
P->a 从 2025 增加到 2026 <br>
输出：2026

循环继续直到 P->a >= 2028：<br>
初始值：2024 <br>
每次 func2 调用时 a 增加1 <br>
func1 调用时 a 不变 

需要增加的次数：2028 - 2024 = 4，<br>
但每2次循环中只有1次增加a，所以需要：4 * 2 = 8 次循环。

输出：
```
Your journey begins here!
2024
Your journey begins here! 
2025
Your journey begins here!
2026
Your journey begins here!
2027
Your journey begins here!
2028
```

---

## 13. GNU/Linux (选做)

注：嘿！你或许对 Linux 命令不是很熟悉，甚至你没听说过 Linux。但别担心，这是选做题，了解 Linux 是加分项，但不了解也不扣分哦！

1. 你知道 `cd` 命令的用法与 `/` `~` `-` 这些符号的含义吗？
2. 你知道 Linux 系统如何创建和删除一个目录吗？
3. 请问你还懂得哪些与 GNU/Linux 相关的知识呢？

## 题解

1、`cd` ：切换目录；`/` ：根目录； `~` ：家目录 ； `-` ：表示选项、标准输入输出、当前目录或父目录，也可以做分割符。<br>
除此之外`.` ：当前目录； `..` ：上级目录。<br>
2、创建目录：`mkdir` ； 删除空目录：`rmdir` ； 删除非空目录：`rm -r` 。<br>
3、GNU项目是一个完全自由的操作系统，提供新新许多基础工具和软件包。<br>
Linux是操作系统的内核，负责管理计算机硬件资源，并提供与硬件的接口。

---

