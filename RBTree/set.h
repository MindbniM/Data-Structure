#pragma once
#include"RBTree.h"
template<class K>
class set
{
	struct kofv
	{
		const K operator()(const K& v)
		{
			return v;
		}
	};
public:
	typedef RBTree<K,const K, kofv> Tree;
	typedef typename Tree::iterator iterator;
	typedef typename Tree::const_iterator const_iterator;
	std::pair<iterator,bool> insert(const K& data)
	{
		return _root.insert(data);
	}
	iterator begin()
	{
		return _root.begin();
	}
	iterator end()
	{
		return _root.end();
	}

private:
	Tree _root;
};
