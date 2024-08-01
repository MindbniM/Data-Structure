#pragma once
#include<iostream>
template<class T,size_t N>
struct BTreeNode
{
	T _keys[N];
	BTreeNode* _child[N + 1];
	BTreeNode* _parent;
	int _n;
	BTreeNode()
	{
		for (int i = 0; i < N; i++)
		{
			_keys[i] = T();
			_child[i] = nullptr;
		}
		_child[N] = nullptr;
		_parent = nullptr;
		_n = 0;
	}
};
template<class K,size_t N=3>
class BTree
{
	using Node = BTreeNode<K, N>;
public:
	BTree():_root(nullptr)
	{}
	bool insert(const K& key)
	{
		if (_root == nullptr)
		{
			_root = new Node();
			_root->_keys[0] = key;
			_root->_n++;
			return true;
		}
		auto [node, n] = find_node(key);
		if (n >= 0) return false;

		K ikey = key;
		Node* inode = nullptr;
		while (node!=nullptr)
		{
			//新增节点
			n = find_in_node(node, ikey);
			for (int i = N - 1; i > n; i--)
			{
				node->_keys[i] = node->_keys[i - 1];
				node->_child[i + 1] = node->_child[i];
			}
			node->_keys[n] = ikey;
			node->_child[n + 1] = inode;
			node->_n++;
			if (inode != nullptr) inode->_parent = node;
			//要分裂
			if (node->_n == N)
			{
				Node* brother = new Node();
				int mid = N / 2;
				for (int i = mid + 1; i <= N; i++)
				{
					if (i < N)
					{
						brother->_keys[i - mid - 1] = node->_keys[i];
						node->_keys[i] = K();
						brother->_n++;
						node->_n--;
					}
					brother->_child[i - mid - 1] = node->_child[i];
					node->_child[i] = nullptr;
				}
				ikey = node->_keys[mid];
				node->_keys[mid] = K();
				node->_n--;
				inode = brother;
				//如果是根分裂就修改root,否则转换为向父节点插入一个key和node指针
				if (node->_parent == nullptr)
				{
					Node* newroot = new Node();
					newroot->_keys[0] = ikey;
					newroot->_child[0] = node;
					newroot->_child[1] = brother;
					newroot->_n = 1;
					node->_parent = newroot;
					brother->_parent = newroot;
					_root = newroot;
					return true;
				}
				node = node->_parent;
			}
			else return true;
		}
		return true;
	}

private:
	Node* _root;
	//找到返回节点指针和值下标,找不到返回父节点指针和-1
	std::pair<Node*, int> find_node(const K& key)
	{
		Node* p = _root;
		Node* parent = nullptr;
		while (p!=nullptr)
		{
			int left = 0, right = p->_n;
			while (left < right)
			{
				int mid = (left + right) / 2;
				if (p->_keys[mid] < key) left = mid + 1;
				else if (p->_keys[mid] > right)right = mid;
				else return std::make_pair(p, mid);
			}
			parent = p;
			p = p->_child[left];
		}
		return std::make_pair(parent, -1);

	}
	//在当前节点查找位置
	int find_in_node(Node*p,const K&key)
	{
		int left = 0, right = p->_n;
		while (left < right)
		{
			int mid = (left + right) / 2;
			if (p->_keys[mid] < key) left = mid + 1;
			else if (p->_keys[mid] > right)right = mid;
		}
		return left;
	}
};
