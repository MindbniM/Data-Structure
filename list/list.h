#pragma once
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
	};

	template<class T>
	struct List_iterator
	{
		typedef ListNode<T> Node;
		typedef List_iterator<T> self;
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
		T& operator*() const
		{
			return _node->_val;
		}
		bool operator!=(const self& li) const
		{
			return _node != li._node;
		}
		bool operator==(const self& li) const
		{
			return _node == li._node;
		}
	};

	template<class T>
	struct const_List_iterator
	{
		typedef ListNode<T> Node;
		typedef const_List_iterator<T> self;
		Node* _node;
		const_List_iterator(Node* node)
			:_node(node)
		{
		}
		const_List_iterator(const self& s)
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
		const T& operator*() const
		{
			return _node->_val;
		}
		bool operator!=(const self& li) const
		{
			return _node != li._node;
		}
		bool operator==(const self& li) const
		{
			return _node == li._node;
		}
	};

	template<class T>
	class list
	{
		typedef ListNode<T> Node;
	public:
		typedef List_iterator<T> iterator;
		typedef const_List_iterator<T> const_iterator;

		list()
		{
			empty_init();
		}
		void empty_init()
		{
			_head = new ListNode<T>();
			_head->_next = _head;
			_head->_prev = _head;
		}
		list(const list<T>& li)
		{
			empty_init();
			for (auto& l : li)
			{
				push_back(l);
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
		list& operator=(list li)
		{
			swap(li);
			return *this;
		}
	private:
		Node* _head;
	};
}
