[toc]

---
# 前言
&nbsp;&nbsp;&nbsp;&nbsp;std::string是C++标准模板库中的一个类，用于处理字符串。与C语言的字符串相比，std::string 提供了更强大的功能和更安全的操作, 这次我们来简单实现一下
# string接口介绍
## 构造函数
&nbsp;&nbsp;&nbsp;&nbsp;std::string提供了多种构造函数，允许灵活地创建字符串对象, 下面举例几个最常用的
``` cpp
std::string();//默认构造函数, 创建一个空的字符串
std::string(const char* s);//使用C语言字符串创建
std::string(const std::string& str);//拷贝构造
std::string(const char* s, size_t n);//使用C语言字符串构造, 指定长度
std::string(size_t n, char c);//使用n个字符c构造
template <class InputIterator>
std::string(InputIterator first, InputIterator last);//迭代器构造
std::string(const std::string& str, size_t pos, size_t len = npos);//使用另一个string的部分构造
```
## 迭代器
&nbsp;&nbsp;&nbsp;&nbsp;std::string也提供了迭代器来遍历和操作其内容
``` cpp
iterator begin();//返回字符串开头的迭代器
const_iterator begin() const;//常量迭代器
iterator end();//返回字符串结尾的迭代器
const_iterator end() const;
reverse_iterator rbegin();//返回字符串开头的反向迭代器
const_reverse_iterator rbegin() const;
reverse_iterator rend();//返回字符串结尾的反向迭代器
const_reverse_iterator rend() const;
```
&nbsp;&nbsp;&nbsp;&nbsp;std::string::iterator 是string里封装的一个类型, 类似于指针
**使用示例**
``` cpp
std::string str = "123456789";
std::string::iterator it = str.begin();
while (it != str.end())
{
	std::cout << *it << " ";
	it++;
}
std::cout << std::endl;
```
&nbsp;&nbsp;&nbsp;&nbsp;上面是一个使用迭代器遍历的例子, STL的容器几乎都能使用迭代器遍历
it++移动迭代器, *it获取当前迭代器的引用, 使用起来和指针差不多, 当然如果绝对这个类型太长, 也可以
``` cpp
auto it=str.begin();
```
反向迭代器使用一样, 不够是从字符串的末尾开始遍历。
至于const迭代器, 不能通过*it等方式修改迭代器指向的值
## 常用容量操作
``` cpp
size_t size() const;//获取字符串的字符个数
size_t length() const;//同上
void resize (size_t n);//开n个字符的空间
void resize (size_t n, char c);//开n个字符的空间, 并都初始化为 c
void clear();//清空字符串
bool empty() const;//判断字符串是否为空
```
&nbsp;&nbsp;&nbsp;&nbsp;size和length没有区别, 都是获取字符串的字符个数, resize一般用于提前开空间, string的数据是一个动态管理内存开辟的, 会自动扩容(扩容是有代价的), 提前开取足够的空间可以减少扩容的次数, clear可以清空字符串为空串
## 元素访问操作
``` cpp
char& operator[] (size_t pos);
const char& operator[] (size_t pos) const;
```
&nbsp;&nbsp;&nbsp;&nbsp;string实现了[]重载, 使得可以像使用数组一样访问该下标的元素
``` cpp
char& at (size_t pos);
const char& at (size_t pos) const;
```
&nbsp;&nbsp;&nbsp;&nbsp;取pos位置的元素
``` cpp
char& back();
const char& back() const;
char& front();
const char& front() const;
```
&nbsp;&nbsp;&nbsp;&nbsp;访问第一个位置的元素和最后一个位置的元素
## 常用操作
``` cpp
string& operator+= (const string& str);
string& operator+= (const char* s);
string& operator+= (char c);
string& operator+= (initializer_list<char> il);
```
&nbsp;&nbsp;&nbsp;&nbsp;string也实现了+=操作符重载, 使得拼接字符串更方便

``` cpp
void push_back (char c);
void pop_back();
```
&nbsp;&nbsp;&nbsp;&nbsp;尾插尾删操作, 经典

``` cpp
string& insert (size_t pos, const string& str);
...
iterator insert (const_iterator p, char c);
...
string& erase (size_t pos = 0, size_t len = npos);
iterator erase (const_iterator p);
iterator erase (const_iterator first, const_iterator last);
```
&nbsp;&nbsp;&nbsp;&nbsp;insert/erase一系列操作, 指定位置插入/删除或者指定迭代器位置插入/删除

``` cpp
void swap (string& str);
```
&nbsp;&nbsp;&nbsp;&nbsp;用于交换两个字符串的资源

``` cpp
static const size_t npos = -1;
size_t find (const string& str, size_t pos = 0) const noexcept;
size_t find (const char* s, size_t pos = 0) const;
size_t find (const char* s, size_t pos, size_type n) const;
size_t find (char c, size_t pos = 0) const noexcept;
size_t rfind (const string& str, size_t pos = npos) const noexcept;
size_t rfind (const char* s, size_t pos = npos) const;
size_t rfind (const char* s, size_t pos, size_t n) const;
size_t rfind (char c, size_t pos = npos) const noexcept;
```
&nbsp;&nbsp;&nbsp;&nbsp;find系列函数, 返回找到了第一个匹配的下标, 找不到返回npos

``` cpp
string substr (size_t pos = 0, size_t len = npos) const;
```
&nbsp;&nbsp;&nbsp;&nbsp;提取子字符串
``` cpp
char* c_str();
const char* c_str() const;
```
# string简单实现
&nbsp;&nbsp;&nbsp;&nbsp;我们已经认识了string的基本接口使用, 现在我们自己简单模拟实现一下吧
[完整代码(Github)](https://github.com/MindbniM/Data-Structure/tree/main/string)
## 框架
&nbsp;&nbsp;&nbsp;&nbsp;只实现了常用的接口, 这里只介绍一些重点方法实现, 其他的可以去我的GitHub仓库看源码
``` cpp
class string
{
public:
    //迭代器
	typedef char* iterator;
	typedef const char* const_iterator;
	iterator begin();
	iterator end();
	const_iterator begin()const
	const_iterator end()const
    //构造析构函数
	string(const char* str = "");
	string(const string& str);
	~string();
    //空间
	size_t size()const;
	void reserve(size_t capacity);//这个用来扩容
	void resize(size_t size);
	size_t capacity()const;
	void swap(string& str);
	void clear();
    //插入删除
	void push_back(char c);
	string& append(const string str);
	string& insert(size_t pos, const string& str);
	string& insert(size_t pos, char c);
	string& erase(size_t pos, size_t n = npos);
	string& repalce(size_t pos, size_t n, const string& str);
    //获得C风格的字符串
	char* c_str();
	const char* c_str() const;
    //查找
	size_t find(const string& str, size_t pos=0);
    //提取子字符串
	string substr(size_t pos, size_t len = string::npos);
    //运算符重载
	char& operator[](size_t pos);
	const char& operator[](size_t pos) const;
	string& operator+= (const string& str);
	string& operator+= (char c);
	string operator+(const string& str) const;
	string& operator= (string str);
	static size_t npos;
private:
	char* _str;//字符数组
	size_t _size;//字符个数
	size_t _capacity;//容量
};
size_t string::npos = -1;
std::ostream& operator<<(std::ostream& out, M::string& str);
std::istream& operator>>(std::istream& in, M::string& str);
```
## 构造/析构函数
``` cpp
string(const char* str = "")
{
	_capacity = strlen(str);
	_str = new char[_capacity + 1] {0};
	_size = _capacity;
	strcpy(_str, str);
}
string(const string& str)
{
	string s(str.c_str());
	swap(s);
}
~string()
{
	delete[] _str;
	_str = nullptr;
	_size = 0;
	_capacity = 0;
}
```
**注意**
- 这里设定capacity和sized都为不包含'\0'的大小, 所有要多开一个空间给'\0'
- 拷贝构造里面的s是一个临时变量, 函数栈帧销毁后自动释放, 所有我们可以直接交换和它的资源, 既能拿取它的资源, 还能让自己之前的资源释放
- 构造使用了new[],析构也要相应匹配

## 迭代器
``` cpp
typedef char* iterator;
typedef const char* const_iterator;
iterator begin()
{
	return _str;
}
iterator end()
{
	return _str+_size;
}
const_iterator begin()const
{
	return _str;
}
const_iterator end()const
{
	return _str + _size;
}
```
- 这里直接使用char* 可以完成迭代器的功能

## 操作符重载
### []+=重载
``` cpp
char& operator[](size_t pos)
{
	assert(pos <= _size);
	return _str[pos];
}
string& operator+= (const string& str)
{
	if (_size + str.size() > _capacity)
	{
		reserve(_size + str.size());
	}
	strcpy(_str + _size, str.c_str());
	_size += str.size();
	return *this;
}
string& operator+= (char c)
{
	push_back(c);
	return *this;
}
string operator+(const string& str) const
{
	string s(*this);
	s += str;
	return s;
}
string& operator= (string str)
{
	swap(str);
	return *this;
}
```
**注意**
- +=操作符重载要支持连续+=
- +操作符的返回值是两个字符串拼接的结果, 但原本的字符串不能改变
- =操作符要支持连接=
### 流插入/提取操作符重载
``` cpp
std::ostream& operator<<(std::ostream& out, M::string& str)
{
	for (int i = 0; i < str.size(); i++)
	{
		out << str.c_str()[i];
	}
	return out;
}
std::istream& operator>>(std::istream& in, M::string& str)
{
	char ch=in.get();
	char strbuff[128];
	int i = 0;
	while (ch != ' ' && ch != '\n')
	{
		strbuff[i++]=ch;
		if (i == 127)
		{
			strbuff[i] = '\0';
			str += strbuff;
			i = 0;
		}
		ch = in.get();
	}
	if (i != 0)
	{
		strbuff[i] = '\0';
		str += strbuff;
	}
	return in;
}
```
**注意**
- 流插入/提取操作符第一个参数必须是i/ostream对象, 这些函数不能写在类里面, 如果把这些函数写在类里面, 第一个参数会被this指针占用
- 流提取使用了缓冲区, 避免多次调用+=
## 常用操作
### 插入
``` cpp
void push_back(char c)
{
	if (_size == _capacity)
	{
		size_t new_capacity = _capacity == 0 ? 4 : 2 * _capacity;
		reserve(new_capacity);
	}
	_str[_size] = c;
	_size++;
}
string& insert(size_t pos, const string& str)
{
	if (_size + str.size() > _capacity)
	{
		reserve(_size + str.size());
	}
	size_t end = str.size()+_size;
	while (end > pos)
	{
		_str[end] = _str[end - str.size()];
		--end;
	}
	strncpy(_str + pos, str.c_str(),str.size());
	_size += str.size();
	return *this;
}
string& insert(size_t pos, char c)
{
	if (_size + 1 > _capacity)
	{
		reserve(_size + 1);
	}
	size_t end = 1 + _size;
	while (end > pos)
	{
		_str[end] = _str[end - 1];
		--end;
	}
	_str[pos] = c;
	_size ++;
	return *this;
}
string& append(const string str)
{
	(*this)+= str;//直接偷懒复用+=
	return *this;
}
```
**注意**
- 满了需要扩容, 我这里选择的第一次开辟4个空间, 接下面都是2倍扩容
- insert也要提前计算空间大小, 然后移动位置插入
### 删除
``` cpp
string& erase(size_t pos, size_t n = npos)
{
	if (n == npos || n + pos >= _size)
	{
		_str[pos] = '\0';
	}
	else
	{
		strcpy(_str + pos, _str + pos + n);
	}
	return *this;
}
```
**注意**
- 删除的数量大于数据数直接将后面全部清空, 删除不缩容


