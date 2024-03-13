#pragma once
enum color
{
	Red,
	Black,
};
template<class T>
struct RBTreeNode
{
	typedef RBTreeNode<T> Node;
	Node* _prante;
	Node* _left;
	Node* _right;
	color _c;
	T _data;
	RBTreeNode(const T& data)
		:_prante(nullptr)
		, _left(nullptr)
		,_right(nullptr)
		,_c(Red)
		, _data(data)
	{
	}
};
template<class T>
struct RBTreeiterator
{
	typedef RBTreeNode<T> Node;

	typedef RBTreeiterator<T> self;
	RBTreeiterator( Node* root)
		:_root(root)
	{
	}
	RBTreeiterator(const self& rb)
	{
		_root = rb._root;
	}
	self& operator++()
	{
		if (_root->_right != nullptr)
		{
			_root = _root->_right;
			while (_root->_left != nullptr)
				_root = _root->_left;
		}
		else
		{
			while (_root->_prante != nullptr && _root != _root->_prante->_left)
				_root = _root->_prante;
			_root = _root->_prante;
		}
		return *this;
	}
	self operator++(int)
	{
		self temp(*this);
		if (_root->_right != nullptr)
		{
			_root = _root->_right;
			while (_root->_left != nullptr)
				_root = _root->_left;
		}
		else
		{
			while (_root->_prante != nullptr && _root != _root->_prante->_left)
				_root = _root->_prante;
			_root = _root->_prante;
		}
		return temp;
	}
	bool operator!=(const self& rb)
	{
		return _root != rb._root;
	}
	bool operator==(const self& rb)
	{
		return _root == rb._root;
	}
	self operator+(int num)
	{
		self temp(*this);
		while (num)
		{
			++temp;
			num--;
		}
		return temp;
	}
	T& operator*()
	{
		return _root->_data;
	}
	T* operator->()
	{
		return &_root->_data;
	}
	Node* _root=nullptr;
};
template<class K,class V,class kofv>
class RBTree
{
	typedef RBTreeNode<V> Node;
public:
	typedef RBTreeiterator<V> iterator;
	typedef RBTreeiterator<V> const_iterator;
	iterator begin()
	{
		Node* root = _root;
		while (root->_left != nullptr)
			root = root->_left;
		return root;
	}
	iterator end()
	{
		return nullptr;
	}
	const_iterator begin()const
	{
		Node* root = _root;
		while (root->_left != nullptr)
			root = root->_left;
		return root;
	}
	const_iterator end()const
	{
		return nullptr;
	}
	std::pair<iterator,bool> insert(const V& value)
	{
		kofv key;
		if (_root == nullptr)
		{
			_root = new Node(value);
			_root->_c = Black;
			return std::pair<iterator,bool>(_root,true);
		}
		Node* prante = _root->_prante;
		Node* cur = _root;
		while (cur != nullptr)
		{
			if (key(cur->_data) < key(value))
			{
				prante = cur;
				cur = cur->_right;
			}
			else if (key(value) < key(cur->_data))
			{
				prante = cur;
				cur = cur->_left;
			}
			else
			{
				return std::pair<iterator, bool>(cur, false);
			}
		}
		Node* node = new Node(value);
		Node* p = node;
		if (key(prante->_data) < key(value))
		{
			prante->_right = node;
			node->_prante = prante;
		}
		else
		{
			prante->_left = node;
			node->_prante = prante;
		}
		while (prante!=nullptr&&prante->_c == Red)
		{
			Node* gp = prante->_prante;
			Node* u = gp->_left;
			if (prante == gp->_left)
			{
				u = gp->_right;
			}
			if (u!=nullptr&&u->_c == Red)
			{
				prante->_c = Black;
				u->_c = Black;
				gp->_c = Red;
				node = gp;
				prante = node->_prante;
			}
			else
			{
				if (node == prante->_left)
				{
					if (prante == gp->_left)
					{
						rotateR(gp);
						gp->_c = Red;
						prante->_c = Black;
						node = prante;
						prante = prante->_prante;
					}
					else
					{
						rotateR(prante);
						rotateL(gp);
						
						gp->_c = Red;
						node->_c = Black;
						prante = node->_prante;
					}

				}
				else if (node == prante->_right)
				{
					if (prante == gp->_right)
					{
						rotateL(gp);
						gp->_c = Red;
						prante->_c = Black;
						node = prante;
						prante = prante->_prante;
					}
					else
					{
						rotateL(prante);
						rotateR(gp);
						gp->_c = Red;
						node->_c = Black;
						prante = node->_prante;
					}
				}
				break;
			}
		}
		_root->_c = Black;
		return std::pair<iterator, bool>(p, true);
	}
	/*bool isRBTree()
	{
		int blacksize = 0;
		Node* root = _root;
		while (root != nullptr)
		{
			if (root->_c == Black) blacksize++;
			root = root->_left;
		}
		return _isRBTree(_root, 0, blacksize);
	}*/
	~RBTree()
	{
		_destroy(_root);
	}
private:
	/*bool _isRBTree(Node* root, int num, int blacksize)
	{
		if (root == nullptr)
		{
			std::cout << num << " ";
			if (num == blacksize)
				return true;
			else
			{
				std::cout << "blacksize" << std::endl;
				return false;
			}
		}
		if (root->_c == Black) num++;
		else
		{
			Node* prante = root->_prante;
			if (prante != nullptr && prante->_c == Red)
			{
				std::cout << "redsize" << std::endl;
				return false;
			}
		}
		return _isRBTree(root->_left, num, blacksize)&&_isRBTree(root->_right,num,blacksize);
	}*/
	void rotateR(Node* cur)
	{
		Node* prante = cur->_prante;
		Node* clreft = cur->_left;
		Node* clcr = clreft->_right;
		cur->_left = clcr;
		if (clcr != nullptr)
		{
			clcr->_prante = cur;
		}
		clreft->_right = cur;
		cur->_prante = clreft;
		clreft->_prante = prante;
		if (cur == _root)
		{
			_root = clreft;
		}
		else
		{
			if (cur == prante->_left)
				prante->_left = clreft;
			else
				prante->_right = clreft;
		}

	}
	void rotateL(Node* cur)
	{
		Node* prante = cur->_prante;
		Node* cright = cur->_right;
		Node* crcl = cright->_left;
		cur->_right = crcl;
		if (crcl != nullptr)
		{
			crcl->_prante = cur;
		}
		cright->_prante = prante;
		cright->_left = cur;
		cur->_prante = cright;
		if (cur == _root)
		{
			_root = cright;
		}
		else
		{
			if (cur == prante->_left)
				prante->_left = cright;
			else
				prante->_right = cright;
		}
		
	}
	void _destroy(Node* root)
	{
		if (root == nullptr)
			return;
		_destroy(root->_left);
		_destroy(root->_right);
		delete root;
	}
	Node* _root=nullptr;
};
