[toc]

---
# 前言
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;C++ 的内存管理是程序设计中的一个关键部分，涉及到内存的分配、使用和释放。理解内存管理对于编写高效和稳定的C++程序至关重要
# C/C++内存分布
&nbsp;&nbsp;&nbsp;&nbsp;在C/C++程序中，内存的分布方式通常可以分为一下几个主要区域
1. **代码段（Text Segment / Code Segment）**
&nbsp;&nbsp;&nbsp;&nbsp;存储程序的机器代码，即编译后的可执行代码。
**特点**：通常是只读的，以防止程序意外修改代码。对于某些系统，可以将代码段标记为只读，从而避免程序自修改。
1. **数据段（Data Segment）**
- **静态/全局变量区（Initialized Data Segment）**
&nbsp;&nbsp;&nbsp;&nbsp;存储已初始化的全局变量和静态变量。
**特点**：这些变量在程序启动时即分配内存，并在程序的整个生命周期内保持其分配。
- **未初始化数据段（BSS Segment）** 
&nbsp;&nbsp;&nbsp;&nbsp;存储未初始化的全局变量和静态变量（在程序启动时被初始化为零）。
**特点**：BSS段的内存只在运行时被分配，但初始值为零。
3. **堆（Heap）**
&nbsp;&nbsp;&nbsp;&nbsp;用于动态内存分配，即在程序运行时通过 malloc、calloc、realloc（C语言）或 new（C++） 分配的内存。
**特点**：堆的大小并不固定，可以动态增长或缩小；然而，堆内存的管理是程序员的责任，必须通过 free（C语言） 或 delete（C++） 释放不再使用的内存，以避免内存泄漏。
4. **栈（Stack）**
&nbsp;&nbsp;&nbsp;&nbsp;存储局部变量、函数参数和返回地址。每当一个函数被调用时，会为其分配一个栈帧，包含该函数的局部变量、参数以及返回地址。
**特点**：栈内存的分配和释放是自动的，随着函数的调用和返回而自动进行。栈的大小通常是有限的，因此过深的递归或过大的局部数组可能导致栈溢出（stack overflow）。
5. **常量区（Literal Pool/Constant Segment）**
&nbsp;&nbsp;&nbsp;&nbsp;存储程序中的常量数据，如字符串常量和一些不可修改的变量。
**特点**：常量区通常是只读的，用于防止意外修改这些常量。

# C语言内存管理
&nbsp;&nbsp;&nbsp;&nbsp;我们先来回顾一下C语言的内存管理, 在C语言中，动态内存管理主要是通过几个内存管理函数完成的

## malloc
向内存申请指定大小内存
``` c
#include <stdlib.h>
void *malloc(size_t size);
```
size : 需要申请的内存大小(字节)
申请内存成功返回一个指向这块空间的起始地址, 申请失败返回NULL

**示例**
``` c
int main()
{
    int size=255;
    int* arr=(int*)malloc(sizeof(int)*size);
    //...
    free(arr);
    return 0;
}
```
## calloc
向内存申请指定大小内存, 并初始化为0
``` c
#include <stdlib.h>
void *calloc(size_t nmemb, size_t size);
```
nuemb : 数据的个数
size : 每个数据的大小
申请内存成功返回一个指向这块空间的起始地址, 申请失败返回NULL

**示例**
``` c
int main()
{
    int len=100;
    //等同于malloc(len*sizeof(char));
    char* str=(char*)calloc(len,sizeof(char));
    //...
    free(str);
    return 0;
}
```
## realloc
控制已经申请的空间大小
``` c
#include <stdlib.h>
void *realloc(void *ptr, size_t size)
```
ptr : 指向要调整大小的内存块的指针
size : 新的内存块的大小
成功返回指向新内存块的指针，类型为 void*。如果调整失败，返回 NULL, 原内存块依然有效，未被释放

**示例**
``` c
int main()
{
    int* arr=(int*)malloc(10*sizeof(int));
    int *new_arr = (int *)realloc(arr, 20 * sizeof(int)); // 调整数组大小到20个整数
    if(new_arr!=NULL) arr=new_arr;
    return 0;
}
```
## reallocarray
``` c
#include <stdlib.h>
void *reallocarray(void *ptr, size_t nmemb, size_t size);
```
ptr : 指向要调整大小的数组的指针。
nmemb : 表示新的数组元素的数量。
size : 表示每个元素的大小(字节)

与realloc几乎相同, reallocarray的不同之处在于它安全地处理nmemb和size的乘积
## free
释放内存
``` c
#include <stdlib.h>
void free(void *ptr);
```
ptr : 要释放内存的起始地址

# C++内存管理
&nbsp;&nbsp;&nbsp;&nbsp;C语言内存管理方式在C++中可以继续使用，但有些地方就无能为力，而且使用起来比较麻烦，因
此C++又提出了自己的内存管理方式
## new/delete
&nbsp;&nbsp;&nbsp;&nbsp;C++使用new操作符来申请内存, delete操作符释放内存
### 内置类型
**示例**
``` cpp
int main()
{
  // 动态申请一个int类型的空间
  int* p1 = new int;
  
  // 动态申请一个int类型的空间并初始化为10
  int* p2 = new int(10);
  
  // 动态申请10个int类型的空间
  int* p3 = new int[10];

  delete ptr4;
  delete ptr5;
  delete[] ptr6;
  return 0;
}
```
**注意** : new与delete, new[]与delete[]要匹配使用, 否则会出现未定义行为, 发生难以预料的后果
### 自定义类型
&nbsp;&nbsp;&nbsp;&nbsp;new/delete 和 malloc/free最大区别是 new/delete对于【自定义类型】除了开空间还会调用构造函数和析构函数
**示例**
``` cpp
class A
{
public:
	A(int a = 0)
		: _a(a)
	{
		cout <<  this <<"->A()"<< endl;
	}
	~A()
	{
		cout << this<<"->~A()" << endl;
	}
private:
	int _a;
};

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	cout << "malloc:";
	A* p1 = (A*)malloc(sizeof(A));
	cout << endl;
	cout << "new:";
	A* p2 = new A(1);
	cout << "free:";
	free(p1);
	cout << endl;
	cout << "delete:";
	delete p2;
	cout << "malloc申请数组:";
	A* p5 = (A*)malloc(sizeof(A) * 3);
	cout << endl;
	cout << "new[]申请数组";
	A* p6 = new A[3];
	cout << "free释放数组:";
	free(p5);
	cout << endl;
	cout << "delete释放数组:";
	delete[] p6;
	return 0;
}
```

## operator new/operator delete
&nbsp;&nbsp;&nbsp;&nbsp;new和delete是用户进行动态内存申请和释放的操作符，operator new 和operator delete是系统提供的全局函数，new在底层调用operator new全局函数来申请空间，delete在底层通过operator delete全局函数来释放空间。
``` cpp
void* operator new(std::size_t size) throw(std::bad_alloc);
```
operator new只申请空间, 不调用构造函数, 底层调用malloc
**区别**
operator new 是一个函数，仅负责内存分配，可以被重载以提供自定义行为
new 是一个运算符，不仅分配内存，还调用构造函数来初始化对象
``` cpp
void operator delete(void* ptr) throw();
```
operator delete仅负责释放内存，而不会调用对象的析构函数, 底层调用free
**区别**
operator delete 是一个函数，仅负责内存的释放，可以被重载以提供自定义行为
delete 是一个运算符，它不仅释放内存，还负责调用对象的析构函数进行资源清理
## 定位new
&nbsp;&nbsp;&nbsp;&nbsp;定位new表达式是在已分配的原始内存空间中调用构造函数初始化一个对象
**使用格式** : new (ptr) type;
**示例**
``` cpp
class A
{
public:
	A(int a )
		: _num(a)
	{}
	~A()
	{
		cout << _num << endl;
	}
private:
	int _num;
};
int main()
{
	// p1现在指向的只不过是与A对象相同大小的一段空间，还不能算是一个对象，因为构造函数没有执行
	A* p1 = (A*)malloc(sizeof(A));
	new(p1)A(10);  // 定位new
	delete p1;
	return 0;
}
```
# 内存泄漏
&nbsp;&nbsp;&nbsp;&nbsp;内存泄漏指因为疏忽或错误造成程序未能释放已经不再使用的内存的情况。内存泄漏并不是指内存在物理上的消失，而是应用程序分配某段内存后，因为设计错误，失去了对该段内存的控制，因而造成了内存的浪费, 内存泄漏会导致响应越来越满
- **堆内存泄漏(Heap leak)**
&nbsp;&nbsp;&nbsp;&nbsp;堆内存指的是程序执行中通过malloc/calloc/realloc/new等从堆中分配的一块内存，用完后必须通过调用相应的free或者delete回收, 假设程序的设计错误导致这部分内存没有被释放，那么以后这部分空间将无法再被使用，就会产生Heap Leak
- **系统资源泄漏**
&nbsp;&nbsp;&nbsp;&nbsp;指程序使用系统分配的资源，比方套接字、文件描述符、管道等没有使用对应的函数释放掉，导致系统资源的浪费，严重可导致系统效能减少，系统执行不稳定






