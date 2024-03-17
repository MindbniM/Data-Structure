#ifndef HASH_CLISED
#define HASH_CLISED
namespace MindbniM
{
	enum sign
	{
		EMPTY,
		DELETEd,
		FULL,
	};
	template<class T>
	struct hashnode
	{
		T _data;
		sign _s;
		hashnode()
			:_data(T())
			, _s(EMPTY)
		{
		}
		hashnode(const T& data)
			:_data(data)
			, _s(FULL)
		{
		}
	};
	template<class T>
	struct koft
	{
		T operator()(const hashnode<T>& k)
		{
			return k._data;
		}
	};
	template<class T>
	struct Hashfun
	{
		int operator()(const T& k)
		{
			return (int)k;
		}
	};
	template<>
	struct Hashfun<std::string>
	{
		size_t operator()(const std::string& k)
		{
			size_t num = 0;
			for (auto& c : k)
			{
				num += c;
				num *= 31;
			}
			return num;
		}
	};
	template<class K, class T, class koft, class Hashfun = Hashfun<T>>
	class Hash
	{
		typedef hashnode<T> node;
	public:
		Hash(size_t size = 10)
		{
			_v.resize(size);
			_size = 0;
		}
		bool insert(const T& data)
		{
			if (find(data)) return false;
			double bf = _size * 1.0 / _v.size();
			if (bf > 0.7)
			{
				Hash<K, T, koft, Hashfun> newhash(_v.size() * 2);
				for (int i = 0; i < _v.size(); i++)
				{
					newhash.insert(_v[i]._data);
				}
				swap(newhash);
			}
			Hashfun hash;
			size_t hashi = hash(data) % _v.size();
			while (_v[hashi]._s == FULL)
			{
				hashi++;
				hashi = hashi % _v.size();
			}
			_v[hashi] = node(data);
			_size++;
			return true;
		}
		bool erase(const K& key)
		{
			koft k;
			size_t hashi = key % _v.size();

			while (k(_v[hashi]) != key && _v[hashi]._s != EMPTY)
			{
				hashi++;
				hashi = hashi % _v.size();
			}
			if (_v[hashi]._s == EMPTY) return false;
			_v[hashi]._s = DELETEd;

		}
		bool find(const K& key)
		{
			koft k;
			Hashfun hash;
			size_t hashi = hash(key) % _v.size();
			while (k(_v[hashi]) != key && _v[hashi]._s != EMPTY)
			{
				hashi++;
				hashi = hashi % _v.size();
			}
			if (_v[hashi]._s == FULL) return true;
			return false;
		}
		void swap(Hash<K, T, koft, Hashfun>& hash)
		{
			_v.swap(hash._v);
			_size = hash._size;
		}
	private:
		std::vector<node> _v;
		size_t _size;
	};
}
#endif
