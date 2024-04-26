#pragma once
#include"Reverse_iterator.h"
namespace M
{
	template<class T>
	struct ListNode
	{
		ListNode<T>* _prev;
		ListNode<T>* _next;
		T _val;
		ListNode(const T& val=T())
			:_prev(nullptr)
			,_next(nullptr)
			,_val(val)
		{
		}
		ListNode(T&& val)
			:_prev(nullptr)
			,_next(nullptr)
			,_val(std::forward<T>(val))
		{
		}
	};

	template<class T,class CIT,class PTR>
	struct List_iterator
	{
		typedef ListNode<T> Node;
		typedef List_iterator<T,CIT,PTR> self;
		Node* _node;
		List_iterator(Node* node)
			:_node(node)
		{
		}
		List_iterator(const self& s)
		{
			_node = s._node;
		}
		self& operator++()
		{
			_node = _node->_next;
			return *this;
		}
		self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}
		CIT operator*() const
		{
			return _node->_val;
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
	};

	template<class T>
	class list
	{
		typedef ListNode<T> Node;
	public:
		typedef List_iterator<T,T&,T*> iterator;
		typedef List_iterator<T,const T&,const T*> const_iterator;
		typedef Reverse_iterator<iterator, T&, T*> reverse_iterator;
		typedef Reverse_iterator<const_iterator,const T&, const T*> const_reverse_iterator;

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
		void push_back(const T& val)
		{
			insert(end(), val);
		}
		void push_front(const T& val)
		{
			insert(begin(), val);
		}
		void pop_back()
		{
			erase(--end());
		}
		void pop_front()
		{
			erase(begin());
		}
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
			emplace(end(), args...);
		}
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
		iterator begin()
		{
			return _head->_next;
		}
		iterator end()
		{
			return _head;
		}
		const_iterator begin() const
		{
			return _head->_next;
		}
		const_iterator end() const
		{
			return _head;
		}
		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}
		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}
		const_reverse_iterator crbegin() const
		{
			return const_reverse_iterator(end());
		}
		const_reverse_iterator crend() const
		{
			return const_reverse_iterator(begin());
		}
		void clear()
		{
			iterator b = begin();
			while (b != end())
			{
				b=erase(b);
			}
		}
		void swap(list& li)
		{
			std::swap(_head, li._head);
		}
		void resize(size_t n, const T& val = T())
		{
			while (n--)
			{
				push_back(val);
			}
		}
		bool empty()
		{
			return _head->_next == _head;
		}
		int size()
		{
			iterator it = begin();
			int n = 0;
			while (it != end())
			{
				++it;
				n++;
			}
			return n;
		}
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
	private:
		Node* _head;



		void empty_init()
		{
			_head = new ListNode<T>();
			_head->_next = _head;
			_head->_prev = _head;
		}
	};
}
