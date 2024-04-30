#pragma once
#include"RBTree.h"
template<class K,class V>
class map
{
	struct kofv
	{
		const K operator()(const std::pair<K, V>& v)
		{
			return v.first;
		}
	};
public:
	typedef RBTree<K, std::pair<const K, V>, kofv> Tree;
	typedef typename Tree::iterator iterator;
	typedef typename Tree::const_iterator const_iterator;
	std::pair<iterator, bool> insert( const std::pair<const K,V>& data)
	{
		return _root.insert(data);
	}
	V& operator[](K& data)
	{
		std::pair<iterator, bool> p = insert(make_pair(data,V()));
		return p.first->second;
	}
	iterator begin()
	{
		return _root.begin();
	}
	iterator end()
	{
		return _root.end();
	}
	bool count(const K& data)
	{
		return _root.count(data);
	}
private:
	
	Tree _root;
};
