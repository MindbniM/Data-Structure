#pragma once
template<class T>
struct koft
{
	T operator()(const T& key)
	{
		return key;
	}
};
template<class K,class T,class koft=koft<T>,class Hash=Hashfun<T>>
class unordered_set
{
public:
	
private:
	hash_bucket<K, T, koft, Hash> hash;
};