[toc]

---
# 前言
&nbsp;&nbsp;&nbsp;&nbsp;C++泛型编程（Generic Programming）是一种通过编写与数据类型无关的代码，以提高代码的重用性和灵活性的编程方式。在C++中，泛型编程主要通过模板（Template）来实现
# 函数模板
&nbsp;&nbsp;&nbsp;&nbsp;函数模板代表了一个函数家族，该函数模板与类型无关，在使用时被参数化，根据调用时传递的参数类型生成相应的具体函数。
``` cpp
template<typename/class T1, typename/class T2,......,typename/class Tn>
返回值类型 函数名(参数列表){}
```
下面是一个模板函数示例
**示例**
``` cpp
template<class T>
void func(T num)
{
	std::cout << typeid(num).name()<< std::endl;
}
int main()
{
	func(1);
	func(1.1);
	func('a');
	return 0;
}
```
&nbsp;&nbsp;&nbsp;&nbsp;根据调用时传参生成不同的函数
## 函数模板的实例化
&nbsp;&nbsp;&nbsp;&nbsp;用不同类型的参数使用函数模板时，称为函数模板的实例化。模板参数实例化分为：隐式实例化和显式实例化
### 隐式实例化
&nbsp;&nbsp;&nbsp;&nbsp;让编译器根据实参推演模板参数的实际类型
``` cpp
template<class T>
T add(const T& left,const T& right)
{
	return left + right;
}
int main()
{
	std::cout << add(1,2) << std::endl;
	std::cout << add('A','1') << std::endl;
	std::cout << add(1.3,2.4) << std::endl;
	return 0;
}
```
### 显示实例化
&nbsp;&nbsp;&nbsp;&nbsp;在模板中，编译器一般不会进行类型转换操作, 所以以下代码会报错
``` cpp
template<class T>
T add(const T& left,const T& right)
{
	return left + right;
}
int main()
{
	std::cout << add(1,2) << std::endl;
	std::cout << add(1,1.1) << std::endl;//E0304	没有与参数列表匹配的 函数模板 "add" 实例
	std::cout << add('a',1) << std::endl;//E0304	没有与参数列表匹配的 函数模板 "add" 实例		
	return 0;
}
```
&nbsp;&nbsp;&nbsp;&nbsp;这时我们就需要显示实例化, 指定类型
``` cpp
template<class T>
T add(const T& left,const T& right)
{
	return left + right;
}
int main()
{
	std::cout << add(1,2) << std::endl;
	std::cout << add<int>(1,1.1) << std::endl;//指定int
	std::cout << add<int>('a',1) << std::endl;//指定int
	return 0;
}
```
如果类型不匹配，编译器会尝试进行隐式类型转换，如果无法转换成功编译器将会报错
``` cpp
template<class T>
T add(const T& left,const T& right)
{
	return left + right;
}
int main()
{
	std::string str;
	std::cout << add<int>(str, 1) << std::endl;//C2664	“T add<int>(const T &,const T &)”: 无法将参数 1 从“std::string”转换为“const T &”
	return 0;
}
```
# 类模板
&nbsp;&nbsp;&nbsp;&nbsp;除了函数模板, 还有类模板
``` cpp
template<class T1, class T2, ..., class Tn>
class 类模板名
{
 // 类内成员定义
}; 
```
下面是一个简单实现vector的框架
**示例**
``` cpp
template<class T>
class Vector
{ 
public :
    Vector(size_t capacity = 10)
    : _pData(new T[capacity])
    , _size(0)
    , _capacity(capacity)
    {}
    ~Vector();
    void PushBack(const T& data)；
    void PopBack()；
    size_t Size() {return _size;}
    T& operator[](size_t pos)
    {}

private:
    T _data;//使用模板参数
    size_t _size;
    size_t _capacity;
};
```
## 实例化
&nbsp;&nbsp;&nbsp;&nbsp;与函数模板不同, 类模板如果没有设定缺省值, 就要显示实例化, 在C++17以后, 引入类模板参数推导, 使用列表初始化时可以自动推导模板参数
``` cpp
int main()
{
	vector<int> v;
	vector<double> v;
	vector v = { 1,2,3,4,5 };//C++17的类模板参数推导
	return 0;
}
```
# 非类型模板参数
&nbsp;&nbsp;&nbsp;&nbsp;模板参数分类类型形参与非类型形参
**类型形参**：出现在模板参数列表中，跟在class或者typename之类的参数类型名称, 上文提到的都是类型形参
**非类型形参**: 就是用一个常量作为类(函数)模板的一个参数，在类(函数)模板中可将该参数当成常量来使用

**示例**
``` cpp
template<class T,size_t N>
class A
{
private:
	T arr[N];
};
```
**注意**
1. 浮点数、类对象以及字符串是不允许作为非类型模板参数的。
2. 非类型的模板参数必须在编译期就能确认结果。
# 模板特化
&nbsp;&nbsp;&nbsp;&nbsp;通常情况下，使用模板可以实现一些与类型无关的代码，但对于一些特殊类型的可能会得到一些错误的结果，需要特殊处理
比如下面是一个比较函数
``` cpp
template<class T>
bool Comp(T left, T right)
{
    return left < right;
}
int main()
{
    cout << Comp(1, 2) << endl; // 可以比较，结果正确
    int *p1=new int(4);
    int *p2=new int(1);
    cout << Comp(p1, p2) << endl;// 比较的是指针本身的值, 有时候不符合预期
    return 0;
}
```
## 函数模板特化
&nbsp;&nbsp;&nbsp;&nbsp;承接上文, 我们想对指针之间进行比较的时候, 应该比较指针所指向的内容, 而不是指针本身, 这时使用模板特化
``` cpp
bool Comp(T left, T right)
{
    cout << "比较" << endl;
    return left < right;
}
template<class T>
bool Comp(T* left, T* right)
{
    cout << "特化指针比较" << endl;
    return *left < *right;
}
int main()
{
    cout << Comp(1, 2) << endl; // 可以比较，结果正确
    int* p1 = new int(4);
    int* p2 = new int(1);
    cout << Comp(p1, p2) << endl;// 比较的是指针本身的值, 不符合预期
    return 0;
}
```
## 类模板特化
### 全特化
&nbsp;&nbsp;&nbsp;&nbsp;全特化即是将模板参数列表中所有的参数都确定化
``` cpp
template<class K,class V>
class A
{
	K _n1;
	V _n2;
};
template<int ,char>
class A
{
	int _n1;
	char _n2;
};
```
### 偏特化
&nbsp;&nbsp;&nbsp;&nbsp;只对部分参数确定
``` cpp
template<class K,class V>
class A
{
	K _n1;
	V _n2;
};
template<int ,class V>
class A
{
	int _n1;
	V _n2;
};
```
