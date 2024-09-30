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
		template<class ...Args>
		const K operator()(const K k,Args&&... args)
		{
			return k;
		}
	};
public:
	map()
	{}
	typedef RBTree<K, std::pair<const K, V>, kofv> Tree;
	typedef typename Tree::iterator iterator;
	typedef std::pair<const K, V> value_type;
	typedef typename Tree::const_iterator const_iterator;
	map(std::initializer_list<value_type> li)
	{
		for (auto& i : li)
		{
			insert(i);
		}
	}
	map(map<K, V>&& mp)
	{
		_root.swap(mp._root);
	}
	std::pair<iterator, bool> insert( const std::pair<const K,V>& data)
	{
		return _root.insert(data);
	}
	template<class ...Args>
	std::pair<iterator, bool> emplace(Args&&... args)
	{
		return _root.emplace(std::forward<Args>(args)...);
	}
	V& operator[](const K& data)
	{
		std::pair<iterator, bool> p = insert(std::make_pair(data,V()));
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
	size_t size()
	{
		return _root.size();
	}
	bool empty()
	{
		return _root.empty();
	}
	void clear()
	{
		_root.clear();
	}
private:
	Tree _root;
};
