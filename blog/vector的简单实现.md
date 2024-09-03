[toc]
---
# 前言
&nbsp;&nbsp;&nbsp;&nbsp;std::vector 是 C++ 标准库中的一个动态数组容器类,std::vector 可以动态调整其大小，因此在需要频繁尾插尾删的场景下非常有用, 这次我们来学习并简单实现一下
# vector接口介绍
## 构造函数
&nbsp;&nbsp;&nbsp;&nbsp;std::vector 提供了多种构造函数, 可以适用很多场景, 以下是常见的构造
``` cpp
vector();//默认构造
explicit vector (size_type n, const allocator_type& alloc = allocator_type());//提前开n个空间
vector (size_type n, const value_type& val,const allocator_type& alloc = allocator_type());//提前开n个空间并初始化为val
template <class InputIterator>
vector (InputIterator first, InputIterator last,const allocator_type& alloc = allocator_type());//迭代器范围构造
vector (const vector& x);//拷贝构造
vector (vector&& x);//右值引用拷贝构造
vector (initializer_list<value_type> il,const allocator_type& alloc = allocator_type());//列表初始化
```
&nbsp;&nbsp;&nbsp;&nbsp;平时我们最常用的就是默认构造和提前开空间的构造
## 迭代器
&nbsp;&nbsp;&nbsp;&nbsp;vector也设计了一套迭代器, 用于遍历和操作vector容器中的元素的工具。它们类似于指针，可以访问vector中的元素。通过迭代器，可以在vector中进行遍历、插入、删除等操作, 以下是常用的迭代器方法
``` cpp
//返回普通或常量迭代器，指向 vector 的第一个元素的位置
iterator begin() noexcept;
const_iterator begin() const noexcept;
//返回普通或常量迭代器，指向 vector 的最后一个元素的位置
iterator end() noexcept;
const_iterator end() const noexcept;
//返回反向迭代器，指向 vector 第一个元素的反向迭代器。
reverse_iterator rbegin() noexcept;
const_reverse_iterator rbegin() const noexcept;
//返回反向迭代器，指向 vector 最后一个元素的反向迭代器。
reverse_iterator rend() noexcept;
const_reverse_iterator rend() const noexcept;`
```

**示例**
``` cpp
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};

    // 使用普通迭代器遍历
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";  // 使用 * 解引用迭代器以访问元素
    }
    std::cout << std::endl;

    return 0;
}
```
要是觉得这个类型太长, 直接auto it=v.begin()即可
## 容量操作
``` cpp
size_type size() const noexcept;//获取当前元素个数
void resize (size_type n);//调整 vector 的大小，使其包含 n 个元素
void resize (size_type n, const value_type& val);//调整 vector 的大小，使其包含 n 个元素, 并初始化为wal
size_type capacity() const noexcept;//获取当前空间大小
bool empty() const noexcept;//判断是否为空
void reserve (size_type n);//调整空间, 如果n比当前空间大, 就调整空间到n, 如果n小, 就什么也不做
```
**注意**
- 在resize中如果 n 小于当前的 size()，则 vector 将被缩小，多余的元素将被移除
- reserve 不改变 size()，只是为未来可能的扩展预留空间。它不会缩减 capacity()，因此也不会释放内存
## 元素访问操作
&nbsp;&nbsp;&nbsp;&nbsp;除了使用迭代器访问元素, 也可以通过vector提供的接口访问指定位置的元素
``` cpp
reference operator[] (size_type n);
const_reference operator[] (size_type n) const;
```
&nbsp;&nbsp;&nbsp;&nbsp;vector也重载了[], 使得能够和使用数组一样访问它
``` cpp
reference at (size_type n);
const_reference at (size_type n) const;
```
&nbsp;&nbsp;&nbsp;&nbsp;如果不想使用[], 也可以使用at获取一个位置元素的引用
``` cpp
reference front();//返回第一个元素的引用
const_reference front() const;//返回第一个元素的const引用
reference back();//返回最后一个元素的引用
const_reference back() const;//返回最后一个元素的cosnt的引用
```
## 常用操作
&nbsp;&nbsp;&nbsp;&nbsp;下面来介绍vector的常见使用操作
``` cpp
void push_back (const value_type& val);
void push_back (value_type&& val);
void pop_back();
```
&nbsp;&nbsp;&nbsp;&nbsp;经典尾插尾删
``` cpp
//在 position 位置插入一个值为 val 的元素。返回指向新插入元素的迭代器。
iterator insert (const_iterator position, const value_type& val);
//在 position 位置插入 n 个值为 val 的元素。返回指向第一个新插入元素的迭代器
iterator insert (const_iterator position, size_type n, const value_type& val);
//在 position 位置插入范围 [first, last) 中的元素。返回指向第一个新插入元素的迭代器
template <class InputIterator>
iterator insert (const_iterator position, InputIterator first, InputIterator last);
//在 position 位置插入一个右值引用 val，返回指向新插入元素的迭代器。
iterator insert (const_iterator position, value_type&& val);
//在 position 位置插入初始化列表中的所有元素。返回指向第一个新插入元素的迭代器。
iterator insert (const_iterator position, initializer_list<value_type> il);
```
&nbsp;&nbsp;&nbsp;&nbsp;经典插入, 这些函数提供了灵活的方式来在 vector 中插入元素
``` cpp
template <class... Args>
iterator emplace (const_iterator position, Args&&... args);//position位置插入, 使用后面的模板可变参数构造对象
template <class... Args>
void emplace_back (Args&&... args);//尾插, 使用模板可变参数构造对象
```
&nbsp;&nbsp;&nbsp;&nbsp;emplace 和 emplace_back 允许你直接在容器中原地构造对象，避免了额外的复制或移动操作。
``` cpp
iterator erase (const_iterator position);//删除position位置元素,返回指向被删除元素后一个位置的迭代器
iterator erase (const_iterator first, const_iterator last);//删除一个范围的元素, 返回last位置元素的迭代器
```
&nbsp;&nbsp;&nbsp;&nbsp;这里会出现迭代器失效的问题, vector是一个顺序表, 删除操作代表着会将其后面所有的元素都移动一位, 所以如果使用一个已经被删除的元素的位置的迭代器, 就会出现迭代器失效的问题, 所以erase才会返回一个有效的迭代器
**示例**
``` cpp
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto it=v.begin();
    while(it!=v.end())
    {
        if(*it==1)  it=erase(it);//删除1后, it失效, 使用erase的返回值重新赋值
        else it++;
    }
    return 0;
}
```
# vector的简单实现
&nbsp;&nbsp;&nbsp;&nbsp;我们已经熟悉了vector的常见操作, 这就是封装了的顺序表, 现在我们来简单实现一下
[完整代码](https://github.com/MindbniM/Data-Structure/tree/main/vector)
## 框架
&nbsp;&nbsp;&nbsp;&nbsp;只实现了常用的接口, 这里只介绍一些重点方法实现, 其他的可以去我的GitHub仓库看源码
``` cpp
template<class T>
class vector
{
public:
    //迭代器部分
	typedef T* iterator;
	typedef const T* const_iterator;
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
    //构造函数
	vector();
	vector(const vector<T>& v);
	vector(vector<T> && v);
	vector(std::initializer_list<T> li);
	template<class ITERATOR>;
	vector(ITERATOR begin, ITERATOR end);
    //析构
	~vector();
    //插入
	void push_back(const T& val);
	void push_back(T&& val);
	void pop_back();
	void insert(iterator pos,const T& val);
	void insert(iterator pos,T&& val);
	template<class... Args>
	void emplace_back(Args... args);
    //删除
	iterator erase(iterator pos);
	void swap(vector<T>& v);
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;
    //空间
	size_t capacity() const;
	size_t size() const;
	void reserve(const size_t n);
	void resize(const size_t n, T val = T());
    //操作符重载
	T& operator[](size_t pos);
	const T& operator[](size_t pos) const;
	vector<T>& operator=(const vector<T>& v);
	vector<T>& operator=(vector<T>&& v);
	vector<T>& operator=(std::initializer_list<T> li);
private:
	iterator _start=nullptr;//指向开辟的空间的头
	iterator _finish=nullptr;//指向使用的空间的元素末尾
	iterator _end=nullptr;//指向开辟的空间的尾位置的下一个
};
```
## 构造/析构
``` cpp
//默认构造
vector()
{}
//拷贝构造
vector(const vector<T>& v)
{
    //开和要拷贝的vector一样的空间
	reserve(v.capacity());
	for (auto& e : v)
	{
		push_back(e);
	}
}
//右值引用版拷贝构造
vector(vector<T> && v)
{
	swap(v);
}
//列表构造
vector(std::initializer_list<T> li)
{
	for (auto& i : li)
	{
		push_back(i);
	}
}
//范围迭代器构造
template<class ITERATOR>
vector(ITERATOR begin, ITERATOR end)
{
	while (begin != end)
	{
		push_back(*begin);
		begin++;
	}
}
//析构
~vector()
{
	delete[] _start;
	_start = _finish = _end = nullptr;
}
```
**注意**
- 如果插入了数据,一定会调用new[],析构也要相应匹配
## 迭代器
``` cpp
typedef T* iterator;
typedef const T* const_iterator;
iterator begin()
{
	return _start;
}
iterator end()
{
	return _finish;
}
const_iterator begin() const
{
	return _start;
}
const_iterator end() const
{
	return _finish;
}
```
&nbsp;&nbsp;&nbsp;&nbsp;这里直接使用指针就能实现迭代器的功能, 不必再过多封装了
## 操作符重载
``` cpp
template<class T>
T& vector<T>::operator[](size_t pos)
{
	assert(pos < size());
	return *(_start + pos);
}
template<class T>
const T& vector<T>::operator[](size_t pos)const
{
	assert(pos < size());
	return *(_start + pos);
}
template<class T>
vector<T>& vector<T>::operator=(const vector<T>& v)
{
	for (auto& i : v)
	{
		push_back(i);
	}
	return *this;
}
template<class T>
vector<T>& vector<T>::operator=(std::initializer_list<T> li)
{
	vector<T> v(li);
	swap(v);
	return *this;
}
```
**注意**
- =操作符要支持连接=
- 检查越界情况
## 常用操作
### 容量操作
``` cpp
void vector<T>::reserve(const size_t n)
{
	if (n > capacity())
	{
		size_t oldn = size();
		T* temp = new T[n];
		if(_start!=nullptr)
		{
			size_t end = size();
			while (end > 0)
			{
				temp[end-1] = _start[end-1];
				end--;
			}
			delete[] _start;
		}
		_start = temp;
		_finish = _start + oldn;
		_end = _start + n;
	}
}
template<class T>
void vector<T>::resize(const size_t n, T val)
{
	if (n > size())
	{
		reserve(n);
		for (size_t i = size(); i < n; i++)
		{
			_start[i] = val;
			_finish++;
		}
	}
	else
	{
		_finish = _start+ n;
	}
}
```
**注意**
- 扩容后释放旧空间
- _end表示最后一个位置的下一个
### 插入
``` cpp
template<class T>
void vector<T>::push_back(const T& val)
{
	if (_finish == _end)
	{
        //第一次开4个空间, 以后是2倍扩容
		size_t newcapacity = capacity() == 0 ? 4 : 2 * capacity();
		reserve(newcapacity);
	}
	*_finish = val;
	++_finish;
}
//右值引用版尾插
template<class T>
void vector<T>::push_back(T&& val)
{
	if (_finish == _end)
	{
		size_t newcapacity = capacity() == 0 ? 4 : 2 * capacity();
		reserve(newcapacity);
	}
	*_finish = std::forward<T>(val);
	++_finish;
}
template<class T>
void vector<T>::pop_back()
{
	assert(size());
	--_finish;
}
template<class T>
void vector<T>::insert(iterator pos, T && val)
{
	assert(_start <= pos);
	assert(_finish >= pos);
	if (_finish == _end)
	{
		size_t n = pos - _start;
		size_t newcapacity = capacity() == 0 ? 4 : 2 * capacity();
		reserve(newcapacity);
		pos = _start + n;
	}
	_finish++;
	iterator end = _finish - 1;
	while (end != pos)
	{
		*end = *(end - 1);
		end--;
	}
	*pos = std::move(val);
}
template<class T>
void vector<T>::insert(iterator pos,const T& val)
{
	assert(_start <= pos);
	assert(_finish>= pos);
	if (_finish == _end)
	{
		size_t n = pos - _start;
		size_t newcapacity = capacity() == 0 ? 4 : 2 * capacity();
		reserve(newcapacity);
		pos = _start + n;
	}
	_finish++;
	iterator end = _finish-1;
	while (end != pos)
	{
		*end = *(end - 1);
		end--;
	}
	*pos = val;
}
```
**注意**
- 满了需要扩容, 我这里选择的第一次开辟4个空间, 接下面都是2倍扩容
- insert也要提前计算空间大小, 然后移动位置插入
- 右值引用的插入要完美转发
### 删除
``` cpp
iterator erase(iterator pos)
{
	assert(size());
	assert(_start <= pos);
	assert(_finish >= pos);
	iterator end = pos;
	int n = pos - _start;
	while (end < _finish)
	{
		*end = *(end + 1);
		end++;
	}
	--_finish;
	return _start + n;
}
```
**注意**
- 检查元素个数, 检查pos位置是否越界
