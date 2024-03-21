#pragma once
template<class K,class Hash=Hashfun<K>>
class unordered_set
{
	struct koft
	{
		K operator()(const K& key)
		{
			return key;
		}
	};
public:
	typedef typename hash_bucket<K, K, koft, Hash>::iterator iterator;
	iterator begin()
	{
		return hash.begin();
	}
	iterator end()
	{
		return hash.end();
	}
	std::pair<iterator, bool> insert(const K& data)
	{
		return hash.insert(data);
	}
	iterator erase(const K& key)
	{
		return hash.erase(key);
	}
private:
	hash_bucket<K, K, koft, Hash> hash;
};