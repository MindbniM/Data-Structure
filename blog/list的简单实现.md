[toc]


---
# 前言
&nbsp;&nbsp;&nbsp;&nbsp;STL中的list是一个双向链表容器，适用于需要频繁插入和删除操作的场景, 这次我们来简单实现一下list
# list接口介绍
## 构造函数
&nbsp;&nbsp;&nbsp;&nbsp;list也提供了许多种类的构造函数, 和之前的vector, string都有类型的构造
``` cpp
list();//默认构造
explicit list (const allocator_type& alloc);//指定内存分配器构造
explicit list (size_type n, const allocator_type& alloc = allocator_type());//相当于插入n个元素, 每个元素是这个类型的默认构造
list (size_type n, const value_type& val,const allocator_type& alloc = allocator_type());//同上, 只不过指定插入元素
template <class InputIterator>
list (InputIterator first, InputIterator last,const allocator_type& alloc = allocator_type());//经典迭代器构造
list (const list& x);//拷贝构造
list (const list& x, const allocator_type& alloc);
list (list&& x);//右值引用构造
list (list&& x, const allocator_type& alloc);
list (initializer_list<value_type> il,const allocator_type& alloc = allocator_type());//经典列表初始化
```
## 迭代器
&nbsp;&nbsp;&nbsp;&nbsp;list也提供迭代器来访问元素
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
&nbsp;&nbsp;&nbsp;&nbsp;很多容器都封装迭代器, 它们的实现可能都不相同, 但经过封装, 使用起来非常类似, 这次就不在过多说明使用
## 常用容量操作
``` cpp
size_type size() const noexcept;//获取当前元素个数
void resize (size_type n, value_type val = value_type());//调整容器的大小，使其包含 n 个元素
bool empty() const noexcept;//判断是否为空
```
**注意**
- 在resize中如果 n 小于当前的 size()，则 vector 将被缩小，多余的元素将被移除
## 元素访问
&nbsp;&nbsp;&nbsp;&nbsp;list只提供了访问头部和尾部的接口, 和vector不同, 没有提供[]等一系列接口
``` cpp
reference front();
const_reference front() const;
reference back();
const_reference back() const;
```
## 插入删除
&nbsp;&nbsp;&nbsp;&nbsp;list提供了许多插入的接口
### 头插尾插
``` cpp
void push_front (const value_type& val);//头插
void push_front (value_type&& val);//右值头插
template <class... Args>
void emplace_front (Args&&... args);//头插, 直接拿模板参数构造对象
template <class... Args>
void emplace_back (Args&&... args);//模板参数尾插
void push_back (const value_type& val);//尾插
void push_back (value_type&& val);//右值尾插
```
### 任意位置插入
``` cpp
iterator insert (const_iterator position, const value_type& val);//一个迭代器位置插入一个值
iterator insert (const_iterator position, size_type n, const value_type& val);//迭代器位置插入n个值
template <class InputIterator>
iterator insert (const_iterator position, InputIterator first, InputIterator last);//范围插入
iterator insert (const_iterator position, value_type&& val);//右值插入
iterator insert (const_iterator position, initializer_list<value_type> il);//列表插入
```
### 删除
``` cpp
iterator erase (const_iterator position);//删除一个迭代器位置的值
iterator erase (const_iterator first, const_iterator last);//删除一个范围的值
void remove (const value_type& val);//删除容器中所有等于val的值
```
**注意**
- list也有迭代器失效的问题, erase操作会返回一个有效的迭代器
## 其他常用操作
``` cpp
void unique();//去重
template <class BinaryPredicate>
void unique (BinaryPredicate binary_pred);//自定义去重
```
**注意**
- unique只会比较相邻的两个值, 来判断是否需要去重

``` cpp
void merge (list& x);//合并俩list
void sort();//排序
template <class Compare>
void sort (Compare comp);//自定义排序
void reverse() noexcept;//反转list
```
# list简单实现
&nbsp;&nbsp;&nbsp;&nbsp;我们已经熟悉了list的基本操作, list本质是一个带头双循环链表, 现在我们来简单实现一下
[完整代码](https://github.com/MindbniM/Data-Structure/tree/main/list)
## 框架
&nbsp;&nbsp;&nbsp;&nbsp;这里只介绍常用重点功能实现, 具体可以看我的仓库
**首先是ListNode的封装**
``` cpp
	template<class T>
	struct ListNode
	{
		ListNode<T>* _prev;
		ListNode<T>* _next;
		T _val;
		ListNode(const T& val=T());//默认构造
		ListNode(T&& val);//右值构造
		template<class ...Args>
		ListNode(Args&& ...args);//模板参数构造
	};
```
ListNode这个就不用在细说了
**在list这里, 普通的指针已经不能满足需求, 所以需要自己封装一个**
``` cpp
	template<class T,class CIT,class PTR>
	struct List_iterator
	{
		typedef ListNode<T> Node;
		typedef List_iterator<T,CIT,PTR> self;
		Node* _node;
		List_iterator(Node* node);
		List_iterator(const self& s);
		self& operator++();
		self& operator--();
		CIT operator*() const;
		bool operator!=( const self& li) const;
		bool operator==(const self& li) const;
		PTR operator->() const;
	};
```
- 迭代器的功能就是实现元素的顺序访问, 
``` cpp
self& operator++()
{
	_node = _node->_next;//重载++
	return *this;
}
self& operator--()
{
	_node = _node->_prev;//重载--
	return *this;
}
CIT operator*() const
{
	return _node->_val;//返回一个元素的引用
}
bool operator!=( const self& li) const
{
	return _node != li._node;
}
bool operator==(const self& li) const
{
	return _node == li._node;
}
PTR operator->() const
{
	return &_node->_val;
}
```
list是链表结构, 元素的储存不是线性的, 在内存中是分散的, 指针++并不能达到下一个数据, 反而会越界
``` cpp
template<class T>
class list
{
	typedef ListNode<T> Node;
public:
	typedef List_iterator<T,T&,T*> iterator;
	typedef List_iterator<T,const T&,const T*> const_iterator;
    //构造和析构
	list();
	list(const list<T>& li);
	list(list<T>&& li);
	list(std::initializer_list<T> li);
	~list();
    //插入删除操作
	void push_back(const T& val);
	void push_front(const T& val);
	void pop_back();
	void pop_front();
	template<class ... Args>
    iterator emplace(iterator it, Args&&... args)
    template<class ...Args>
    void emplace_back(Args&&...args)
    template<class ...Args>
    void emplace_front(Args&&...args)
	iterator insert(iterator it,const T& val);
	iterator insert(iterator it,T&& val);
	iterator erase(iterator it);
    //迭代器
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
	void clear();
	void swap(list& li);
	void resize(size_t n, const T& val = T());
	bool empty();
	int size();
    //操作符重载
	list& operator=(const list& li);
	list& operator=(list&& li);
private:
	Node* _head;
	void empty_init();//初始化
};
```
## 构造析构
``` cpp
void empty_init()
{
	_head = new ListNode<T>();
	_head->_next = _head;
	_head->_prev = _head;
}
void clear()
{
	iterator b = begin();
	while (b != end())
	{
		b=erase(b);
	}
}
list()
{
	empty_init();
}
list(const list<T>& li)
{
	empty_init();
	for (auto& l : li)
	{
		push_back(l);
	}
}
list(list<T>&& li)
{
	swap(li);
}
list(std::initializer_list<T> li)
{
	empty_init();
	for (auto& i : li)
	{
		push_back(i);
	}
}
~list()
{
	clear();
	delete _head;
	_head = nullptr;
}
```
初始化和之前的vector基本一个套路
**注意**
- list为带头双向链表, 要先初始化头节点和指针指向
- 析构删除所有节点, 不要忘记头节点
## 插入
### emplace插入
``` cpp
template<class ... Args>
iterator emplace(iterator it, Args&&... args)
{
	Node* prev = it._node->_prev;
	Node* node = it._node;
	Node* newnode = new Node(std::forward<Args>(args)...);
	prev->_next = newnode;
	newnode->_prev = prev;
	newnode->_next = node;
	node->_prev = newnode;
	return newnode;
}
template<class ...Args>
void emplace_back(Args&&...args)
{
	emplace(end(), std::forward<Args>(args)...);
}
template<class ...Args>
void emplace_front(Args&&...args)
{
	emplace(begin(), std::forward<Args>(args)...);
}
```
**注意**
- 右值被右值引用后的属性会变成左值, 使用万能引用要跟上完美转发
- Node也要支持模板参数构造
### insert插入
``` cpp
iterator insert(iterator it,const T& val)
{
	Node* prev = it._node->_prev;
	Node* node = it._node;
	Node* newnode = new Node(val);
	prev->_next = newnode;
	newnode->_prev = prev;
	newnode->_next = node;
	node->_prev = newnode;
	return newnode;
}
iterator insert(iterator it,T&& val)
{
	Node* prev = it._node->_prev;
	Node* node = it._node;
	Node* newnode = new Node(std::forward<T>(val));
	prev->_next = newnode;
	newnode->_prev = prev;
	newnode->_next = node;
	node->_prev = newnode;
	return newnode;
}
```
## 删除
``` cpp
iterator erase(iterator it)
{
	Node* node = it._node;
	Node* next = node->_next;
	node->_prev->_next = next;
	next->_prev = node->_prev;
	delete node;
	node = nullptr;
	return next;
}
```
**注意**
- 释放内存, 返回下一个有效的迭代器
## 迭代器
``` cpp
iterator begin()
{
	return _head->_next;
}
iterator end()
{
	return _head;
}
```
**注意**
- 这里将头节点的下一个为第一个元素, 头节点为最后一个位置的下一个, 满足[begin,end)
## 操作符重载
``` cpp
list& operator=(const list& li)
{
	empty_init();
	for (auto&i : li)
	{
		push_back(i);
	}
}
list& operator=(list&& li)
{
	swap(li);
	return *this;
}
```





