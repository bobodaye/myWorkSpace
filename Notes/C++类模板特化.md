## 1.C++类模板特化

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

## 2.虚析构函数

问题：

1. 虚析构函数的清除操作