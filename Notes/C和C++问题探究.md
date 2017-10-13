2017.10.13

**原文链接**：[https://coolshell.cn/articles/9543.html](https://coolshell.cn/articles/9543.html)

1.基类指针指向一个派生类对象指针数组，当使用`delete []`时能否调用虚析构函数？阐述的问题用代码体现如下：

```cpp
class Base {
public:
    virtual ~B(){ cout <<"B::~B()"<<endl; }
};

class Derived : public Base {
public:
    virtual ~D() { cout <<"D::D~()"<<endl; }
};

Base* pBase = new Derived[n]；
delete [] pBase;
//在这种情况下，调用delete [] pBase会不会调用虚析构函数？
```
**关键问题**：`sizeof(Base)` 可能不等于`sizeof(Derived)`。
**分析：**
1. 如果能够调用虚析构函数，那么需要获取虚函数表vptr的地址，基于这个逻辑，要调用所有的虚析构函数，就要能够找到对应的vptr，那么主要问题就是考虑如何来找这个vptr了。

2. `delete [] pBase`，它是根据pBase指针的步长，来找vptr的，pBase[0]能够第一个vptr，那么这里需要注意了，pBase[1]究竟能否找到第二个vptr，由于`sizeof(Derived)`并不一定等于`sizeof(Base)`，因此有可能pBase[1]指向的并不是vptr，那么也就无法调用子类的虚函数，此时会出现Segmentation fault。

而对于Visual Studio 2010/2013，情况就不同了，即使`sizeof(Base) != sizeof(Derived)`，也能够正确的调用子类的析构函数。在C++标准中，这样的用法是undefined。

---

**原文链接**：[https://coolshell.cn/articles/11377.html](https://coolshell.cn/articles/11377.html)

2.结构体成员相对地址以及柔性数组

代码如下：
```c
#include <stdio.h>
struct str {
    int len;
    char s[0];
};

struct foo {
    struct str *a;
};

int main(int argc, char** argv) {
    struct foo f = { 0 };
    if (f.a->s) {
    	printf( f.a->s);	//该处会crash
    }
    return 0;
}
```
问题：

1.main函数中，为什么f.a是NULL，而在if条件中用它访问str中的s程序未crash？

这里问题先留下，后边解决。讲解一下结构体中成员是如何被访问的，其实非常简单，通过获取结构体的实例的地址，再加上成员的偏移量offset，（它也称为相对地址，相对于实例的首地址）就能访问到相应的成员。

对于上边的问题，需要我们了解**指针和数组的一些差别**：

> 如果把源代码中的struct str结构体中的char s[0];改成char *s;会发>现，在13行if条件的时候，程序因为Cannot access memory就直接挂掉了。为什么声明成char s[0]，程序会在14行挂掉，而声明成char *s，程序会在13行挂掉呢？那么char *s 和 char s[0]有什么差别呢？

> 在说明这个事之前，有必要看一下汇编代码，用GDB查看后发现：
> 
> - 对于char s[0]来说，汇编代码用了lea指令，lea 0x04(%rax),%rdx
> - 对于char*s来说，汇编代码用了mov指令，mov 0x04(%rax),%rdx
> 
> lea全称load effective address，是把地址放进去，而mov则是把地址里的内容放进去。所以，就crash了。

通过上面可以了解到，如果访问结构体成员中的数组得到的只是数组的相对地址，而访问成员指针的话其实是相对地址里的内容。

因此通过上面的讲解我们来分析解决提出的问题，刚才访问f.a虽然是NULL但是访问s得到的是s的相对地址，并没有去取它里面的内容，因此程序不会crash。

关于柔性数组(Flexible Array,C99的玩法)，我已有了解，那么为什么要使用柔性数组呢？

首先看下面的代码：
```c
#include <stdlib.h>
#include <string.h>
struct line {
   int length;
   char contents[0]; // C99的玩法是：char contents[]; 没有指定数组长度
};
int main() {
    int this_length = 10;
    struct line *thisline = (struct line *)
                     malloc (sizeof (struct line) + this_length);
    thisline->length = this_length;
    memset(thisline->contents, 'a', this_length);
    return 0;
}
```
1. 柔性数组（零长度数组）的好处在于它不增加结构体的size，只起到一个占位符的作用，redis的sds就很好的利用了柔性数组，构造了十分好用的简单动态字符串。

2. 方便内存释放，如果我们的代码是在一个给别人用的函数中，你在里面做了二次内存分配，并把整个结构体返回给用户。用户调用free可以释放结构体，但是用户并不知道这个结构体内的成员也需要free，所以你不能指望用户来发现这个事。所以，如果我们把结构体的内存以及其成员要的内存一次性分配好了，并返回给用户一个结构体指针，用户做一次free就可以把所有的内存也给释放掉。







