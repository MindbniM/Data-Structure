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
	self operator++()
	{
		if (_n->_next != nullptr)
			_n = _n->_next;
		else
		{
			
		}
	}
	node* _n;
	hash* _h;
};
template<class K,class T,class koft,class Hash=Hashfun<T>>
class hash_bucket
{
	typedef hashnode<T> node;
public:
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
	bool insert(const T& data)
	{
		Hash H;
		if (find(data)) return false;
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
					size_t newhashi = n->_data % newsize;
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
		size_t hashi = H(data) % _v.size();
		node* next = _v[hashi];
		_v[hashi] = n;
		n->_next = next;
		_size++;
		return true;
	}
	node* find(const K& key)
	{
		Hash H;
		size_t hashi = H(key) % _v.size();
		node* n = _v[hashi];
		while (n)
		{
			if (k(n->_data) == key) return n;
			n = n->_next;
		}
		return nullptr;
	}
	bool erase(const K& key)
	{
		Hash H;
		koft k;
		if (find(key) == nullptr) return false;
		size_t hashi = H(key) % _v.size();
		node* n = _v[hashi];
		if (n->_data == key)
		{
			_v[hashi] = n->_next;
			delete n;
		}
		else
		{
			while (k(n->_next->_data) != key)
			{
				n = n->_next;
			}
			node* next = n->_next;
			n->_next = n->_next->_next;
			delete next;
		}
		return true;
	}
private:
	size_t _size = 0;
	std::vector<node*> _v;
};
