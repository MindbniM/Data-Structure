#pragma once
template<class T>
struct hashnode
{
	T _data;
	hashnode<T>* _next=nullptr;
	hashnode(const T& data)
		:_data(data)
	{}
};
template<class T>
struct Hashfun
{
	size_t operator()(const T& data)
	{
		return (size_t)data;
	}
};
template<>
struct Hashfun<std::string>
{
	size_t operator()(const std::string& data)
	{
		size_t num = 0;
		for (auto& c : data)
		{
			num += c;
			num *= 31;
		}
		return num;
	}
};
template<class K, class T, class koft, class Hash>
class hash_bucket;
template<class K, class T, class koft, class Hash>
struct hash_iterator
{
	typedef hashnode<T> node;
	typedef hash_bucket<K, T, koft, Hash> hash;
	typedef hash_iterator<K, T, koft, Hash> self;
	hash_iterator(node* n, hash* h)
		:_n(n)
		,_h(h)
	{
	}
	hash_iterator(const self& it)
		:_n(it._n)
		, _h(it._h)
	{
	}
	self& operator++()
	{
		if (_n->_next != nullptr)
			_n = _n->_next;
		else
		{
			koft k;
			Hash H;
			int hashi = H(k(_n->_data)) % _h->_v.size();
			hashi++;
			while (hashi < _h->_v.size())
			{
				if (_h->_v[hashi] != nullptr)
				{
					_n = _h->_v[hashi];
					break;
				}
				hashi++;
			}
			if (hashi == _h->_v.size())
				_n = nullptr;
		}
		return *this;
	}
	T& operator*()
	{
		return _n->_data;
	}
	bool operator!=(const self& it)
	{
		return _n != it._n;
	}
	bool operator==(const self& it)
	{
		return (_n == it._n) && (_h == it._h);
	}
	node* _n;
	hash* _h;
};
template<class K,class T,class koft,class Hash=Hashfun<T>>
class hash_bucket
{
	template<class K, class T, class koft, class Hash>
	friend struct hash_iterator;
	typedef hashnode<T> node;
public:
	typedef hash_iterator<K, T, koft, Hash> iterator;
	iterator begin()
	{
		int hashi = 0;
		while (hashi<_v.size()&&_v[hashi] == nullptr)
		{
			hashi++;
		}
		if (hashi == _v.size()) return iterator(nullptr, this);
		return iterator(_v[hashi], this);
	}
	iterator end()
	{
		return iterator(nullptr, this);
	}
	hash_bucket(size_t size = 10)
	{
		_v.resize(size, nullptr);
	}
	~hash_bucket()
	{
		for (int i = 0; i < _v.size(); i++)
		{
			node* n = _v[i];
			while (n)
			{
				node* next = n->_next;
				delete n;
				n = next;
			}
			_v[i] = nullptr;
		}
	}
	std::pair<iterator,bool> insert(const T& data)
	{
		Hash H;
		koft k;
		iterator it = find(k(data));
		if (it != end()) return std::make_pair(it,false);
		double bf = _size * 1.0 / _v.size();
		if (bf == 1)
		{
			size_t newsize = _v.size() * 2;
			std::vector<node*> v(newsize,nullptr);
			for (int i = 0; i < _v.size(); i++)
			{
				node* n = _v[i];
				while (n)
				{
					node* p = n->_next;
					size_t newhashi = H(k(n->_data)) % newsize;
					node* next = v[newhashi];
					v[newhashi] = n;
					n->_next = next;
					n = p;
				}
				_v[i] = nullptr;
			}
			_v.swap(v);
		}
		node* n = new hashnode<T>(data);
		size_t hashi = H(k(data)) % _v.size();
		node* next = _v[hashi];
		_v[hashi] = n;
		n->_next = next;
		_size++;
		return std::make_pair(iterator(n,this),true);
	}
	iterator find(const K& key)
	{
		Hash H;
		koft k;
		size_t hashi = H(key) % _v.size();
		node* n = _v[hashi];
		while (n)
		{
			if (k(n->_data) == key) return iterator(n,this);
			n = n->_next;
		}
		return iterator(nullptr,this);
	}
	iterator erase(const K& key)
	{
		Hash H;
		koft ko;
		node* next=nullptr;
		if (find(key) == end()) return end();
		size_t hashi = H(key) % _v.size();
		node* n = _v[hashi];
		if (ko(n->_data) == key)
		{
			_v[hashi] = n->_next;
			delete n;
			next = _v[hashi];
			if (next == nullptr)
			{
				while (hashi < _v.size() && _v[hashi] == nullptr) hashi++;
			}
			if (hashi == _v.size())next = nullptr;
			else next = _v[hashi];
		}
		else
		{
			while (ko(n->_next->_data) != key)
			{
				n = n->_next;
			}
			next = n->_next;
			n->_next = n->_next->_next;
			delete next;
		}
		return iterator(next,this);
	}
private:
	size_t _size = 0;
	std::vector<node*> _v;
};
