#pragma once
template<class K,class T,class Hash=Hashfun<T>>
class unordered_map
{
	struct koft
	{
		T operator()(const std::pair<K, T>& p)
		{
			return p.first;
		}
	};
public:
	typedef typename hash_bucket<K, std::pair<K, T>, koft, Hash>::iterator iterator;
	iterator begin()
	{
		return hash.begin();
	}
	iterator end()
	{
		return hash.end();
	}
	std::pair<iterator, bool> insert(const std::pair<K, T>& data)
	{
		return hash.insert(data);
	}
	T& operator[](const K& key)
	{
		std::pair<iterator, bool> data = insert(std::make_pair(key, T()));
		return (*(data.first)).second;
	}
	iterator erase(const K& key)
	{
		return hash.erase(key);
	}
	size_t size()
	{
		return hash.size();
	}
private:
	hash_bucket<K, std::pair<K, T>, koft, Hash> hash;
};
