#pragma once
namespace M
{
	template<class k>
	struct SearchTreeNode
	{
		typedef SearchTreeNode<k> Node;
		Node* _left = nullptr;
		Node* _right = nullptr;
		k _key;
		SearchTreeNode() = default;
		SearchTreeNode(const k& key) :_key(key), _left(nullptr), _right(nullptr)
		{}
	};
	template<class k>
	class SearchTree
	{
	public:
		typedef SearchTreeNode<k> Node;
		SearchTree() = default;
		SearchTree(const SearchTree<k>& root)
		{
			_root=_SearchTree(root._root);
		}
		bool insert(const k& key);
		bool erase(const k& key);
		void in_order();
		bool find(const k& key);
		bool empty()
		{
			return _root == nullptr;
		}
		SearchTree<k>& operator=(SearchTree<k> root)
		{
			swap(root);
			return *this;
		}
		~SearchTree()
		{
			Destroy(_root);
			_root = nullptr;
		}
	private:
		void swap(SearchTree<k>& root)
		{
			std::swap(_root, root._root);
		}
		Node* _SearchTree(Node* root)
		{
			if (root == nullptr)
				return nullptr;
			Node*r = new Node(root->_key);
			r->_left = _SearchTree(root->_left);
			r->_right = _SearchTree(root->_right);
			return r;
		}
		void Destroy(Node* root)
		{
			if (root == nullptr)
				return;
			Destroy(root->_left);
			Destroy(root->_right);
			delete root;
		}
		Node* _root=nullptr;
	};
	template<class k>
	void SearchTree<k>::in_order()
	{
		if (_root == nullptr)
			return;
		std::stack<Node*> st;
		st.push(_root);
		Node* r = _root->_left;
		while (r != nullptr)
		{
			st.push(r);
			r = r->_left;
		}
		while (!st.empty())
		{
			Node* n = st.top();
			std::cout << n->_key << " ";
			st.pop();
			if (n->_right != nullptr)
			{
				st.push(n->_right);
				Node* node = n->_right->_left;
				while (node != nullptr)
				{
					st.push(node);
					node = node->_left;
				}
			}
		}
		std::cout << std::endl;
	}
	template<class k>
	bool SearchTree<k>::insert(const k& key)
	{
		if (_root == nullptr)
		{
			_root = new SearchTreeNode<k>(key);
			return true;
		}
		Node* prante = nullptr;
		Node* root = _root;
		while (root != nullptr)
		{
			if (root->_key < key)
			{
				prante = root;
				root = root->_right;
			}
			else if (root->_key > key)
			{
				prante = root;
				root = root->_left;
			}
			else
			{
				return false;
			}
		}
		if (prante->_key < key)
			prante->_right = new SearchTreeNode<k>(key);
		else
			prante->_left = new SearchTreeNode<k>(key);
		return true;
	}
	template<class k>
	bool SearchTree<k>::erase(const k& key)
	{
		if (_root == nullptr)
			return false;
		Node* prante = _root;
		Node* root = _root;
		while (root != nullptr)
		{
			if (root->_key < key)
			{
				prante = root;
				root = root->_right;
			}
			else if (root->_key > key)
			{
				prante = root;
				root = root->_left;
			}
			else
			{
				if (root == prante)
				{
					if (root->_right == nullptr)
					{
						_root = root->_left;
						delete root;
					}
					else if (root->_left == nullptr)
					{
						_root = root->_right;
						delete root;
					}
					else
					{
						Node* rightminp = root;
						Node* rightmin = root->_right;
						while (rightmin->_left != nullptr)
						{
							rightminp = rightmin;
							rightmin = rightmin->_left;
						}
						root->_key = rightmin->_key;
						if (root == rightminp)
							rightminp->_right = rightmin->_right;
						else
							rightminp->_left = rightmin->_right;
						delete rightmin;
					}
				}
				else if(root == prante->_left )
				{
					if (root->_right == nullptr)
					{
						prante->_left = root->_left;
						delete root;
					}
					else if (root->_left == nullptr)
					{
						prante->_left = root->_right;
						delete root;
					}
					else
					{
						Node* rightminp = root;
						Node* rightmin = root->_right;
						while (rightmin->_left != nullptr)
						{
							rightminp = rightmin;
							rightmin = rightmin->_left;
						}
						root->_key = rightmin->_key;
						if (root == rightminp)
							rightminp->_right = rightmin->_right;
						else
							rightminp->_left = rightmin->_right;
						delete rightmin;
					}
				}
				else if (root == prante->_right)
				{
					if (root->_right == nullptr)
					{
						prante->_right = root->_left;
						delete root;

					}
					else if (root->_left == nullptr)
					{
						prante->_right = root->_right;
						delete root;

					}
					else
					{
						Node* rightminp = root;
						Node* rightmin = root->_right;
						while (rightmin->_left != nullptr)
						{
							rightminp = rightmin;
							rightmin = rightmin->_left;
						}
						root->_key = rightmin->_key;
						if(root==rightminp)
							rightminp->_right = rightmin->_right;
						else
							rightminp->_left = rightmin->_right;
						delete rightmin;
					}
				}
				return true;
			}
		}
		return false;
	}

	template<class k>
	bool SearchTree<k>::find(const k& key)
	{
		if (_root == nullptr)
		{
			return false;
		}
		Node* root = _root;
		while (root != nullptr)
		{
			if (root->_key < key)
			{
				root = root->_right;
			}
			else if (root->_key > key)
			{
				root = root->_left;
			}
			else
			{
				return true;
			}
		}
		return false;
	}
}
