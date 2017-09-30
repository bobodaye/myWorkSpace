# C++知识点整理

## 1.友元

**友元函数：**允许特定的非成员函数访问一个类的私有成员。

```cpp
#include <iostream>
using namespace std;

class classA {
	int i = 0;
	friend void test() 
	{ 
		classA obj_a; 
		obj_a.i = 100;	//声明为友元函数后，具有对其非公有成员访问的权限
		cout << "test(),i = " << obj_a.i << "\n"; 
    }
};
int main()
{
	//test();	//若test函数使用之前不进行声明，出现error:test找不到标识符
 	void test();  //使用之前在类的外部声明test()
	test();
	return 0;
}
```

**友元类：**如果一个类指定了友元类，则友元类的成员函数可以访问此类包括<u>非公有成员</u>在内的所有成员。

## 2.纯虚函数

将函数定义为纯虚即为子类提供了可以覆盖的接口，而且用户将不能创建包含纯虚函数的类的对象。

**抽象基类：**含一个或多个纯虚函数的类是抽象基类。

## 3.C++类型转换

http://blog.csdn.net/xusiwei1236/article/details/39236595e

## 4.继承中的类作用域

**1.关键概念：名字查找与继承**

假定我们调用p->mem()（或者obj.mem()），则依次执行以下4个步骤：

- 首先确定p（或者obj）的静态类型。因为我们调用的是一个成员，所以该类型必然是类类型。
- 在p（或者obj）的静态类型对应的类中查找mem。**如果找不到**，则依次在其直接基类中不断查找直到到达继承链的顶端。**如果找遍了**该类及其基类仍然找不到，则编译器将报错。
- 一旦找到了mem，就进行常规的类型检查以确认对于当前找到的mem，本次调用是否合法。（检查函数参数以及是否跟const）
- 假设调用合法，则编译器将根据调用的是否是虚函数而产生不同的代码：
  - 如果mem是虚函数且我们通过**引用或指针**进行的调用，则编译器将会在运行时确定到底调用哪个类中的虚函数，依据是对象的<u>动态类型</u>。
  - 反之，mem不是虚函数，或者我们通过对象进行调用，则编译器将产生一个常规函数的调用。

**2.声明在内层作用域的函数并不会重载声明在外层作用域的函数**

换言之，在子类中声明与父类同名的函数，将会覆盖掉父类中所有同名的函数，而不是它们之间形成了重载关系。

**Tips:子类仅需要覆盖父类中部分函数**

如果子类仅需要覆盖父类中的部分函数，其余的函数不用覆盖，并且让子类的对象能够使用，那么我们能做的就是：

1. 重写需要覆盖的那部分函数
2. 父类中剩余的同名函数，在子类中重写该方法，方法体中通过Base::xxx()的形式，调用原来父类中的函数。

看似该方法也OK，但还有更加高效的方法，我们可以使用`using`关键字：

*using's Demo:*

```cpp
class Base {
public:
	void f() { std::cout << "Base f()\n"; }
	void f(int) { std::cout << "Base f(int)\n"; }
};

class Derived : public Base {
public:
	void f() { std::cout << "Derived f()\n"; }
	using Base::f;	//通过using，就将Base类中与f同名的重载函数添加到Derived类中的作用域
};

int main()
{
	Derived d1;
	d1.f(12);	//结果：Base f(int)
	d1.f();		//结果：Derived f()，覆盖了原来Base::f()
}
```

**小结：**

1. `using`声明语句指定一个名字而不指定形参列表，所以一条基类成员函数的using声明语句就可以把该函数的所有重载函数实例添加到派生类的作用域中。
2. 有一点要注意，使用`using Base::f`时，<u>基类函数的每个实例在派生类中都必须是可访问的</u>。

## 5.C++类模板特化

1. vector类模板声明如下：

```cpp
template<class T, class Allocator = allocator<T> >
class vector{...};
```

为bool类型的对象进行特化如下：

```cpp
template<> class vector<bool, allocator<bool> >
{...};
```

[注]：1. `template<>`告诉编译器接下来是模板特化。

​	  2. 模板特化的类型必须出现在紧跟类名后面的`<>`中。

2.半特化

```cpp
template<class Allocator> class vector<bool, Allocator>{...};
```

1. 这种情况限定了对象类型(bool类型)，但并没有指定参数allocator的类型，用户可以提供自定义的allocator类型。
2. 类模板的特化和这种特别的半特化，构成一种重载的“类模板”。

3.防止模板代码膨胀

​	无论何时，对某个类模板进行实例化，只有被调用的成员函数才生成代码。

*Stack Demo:*

>  **额外增加代码体积：**模板化的Stack容器，用int、int*、char\*对它进行特化，会生成三个版本的Stack代码，并链接为程序的一部分。
>  为了缩小代码体积，可以通过使用`完全特化`和`半特化模板`，将指针类型存储到某个独立的类中。
>
>  关键步骤：
>
>  1. 对void*进行完全特化。
>  2. 从void*中派生出所有其他的指针类型。

**小结：**这样一旦有关于指针的特化，它们都会共享对void*完全特化的代码，节省了代码空间。

4.模板和友元

*Demo1:*

```cpp
// Necessary forward declarations:
template<class T> class Friendly;
template<class T> void f(const Friendly<T>&);

template<class T> class Friendly {
  T t;
public:
  Friendly(const T& theT) : t(theT) {}
  // 1."<>"告诉编译器这是一个模板
  // 2.否则，编译器就会去寻找一个名为f的普通函数而不会找到它
  friend void f<>(const Friendly<T>&);
  void g() { f(*this); }
};

template<class T> void f(const Friendly<T>& fo) {
  cout << fo.t << endl;
}
```

*Demo2:*

```cpp
template<class T> class Friendly {
  T t;
public:
  Friendly(const T& theT) : t(theT) {}
  // 1.在这里f不再是一个模板，而是一个普通函数
  // 2.Friendly类模板每次实例化时，就会生成一个新的带有当前Friendly特化参数的普通重载函数
  friend void f(const Friendly<T>& fo) {
    cout << fo.t << endl;
  }
  void g() { f(*this); }
};
```
