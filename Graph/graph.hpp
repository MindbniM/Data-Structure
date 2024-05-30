#pragma once
#include<iostream>
#include<vector>
#include<map>
namespace matrix
{
	template<class V,class W,W invalid=0,bool Direction=false>
	class graph
	{
	public:
		graph(std::initializer_list<V> list) :_v(list)
		{
			size_t size = list.size();
			size_t n = 0;
			for (auto& i : list)
			{
				_map[i] = n;
				n++;
			}
			_vv.resize(size);
			for (auto& v : _vv) v.resize(size, invalid);
		}
		bool inset_edge(const V& v1, const V& v2,const W& w)
		{
			size_t n1 = get_v_index(v1), n2 = get_v_index(v2);
			if (n1 == -1 || n2 == -1) return false;
			_vv[n1][n2] = w;
			if (Direction == false)
			{
				_vv[n2][n1] = w;
			}
			return true;
		}
		void print()
		{
			std::cout << "     ";
			for (int i = 0; i < _vv.size(); i++)
			{
				std::cout << i << "    ";
			}
			std::cout << std::endl;
			for (int i = 0; i < _vv.size(); i++)
			{
				std::cout << i << "    ";
				for (int j = 0; j < _vv[i].size(); j++)
				{
					std::cout << _vv[i][j] << "    ";
				}
				std::cout << std::endl;
			}
		}
	private:
		size_t get_v_index(const V& v)
		{
			auto it = _map.find(v);
			if (it == _map.end())
			{
				return -1;
			}
			return it->second;
		}
		std::vector<V> _v;
		std::map<V, int> _map;
		std::vector<std::vector<W>> _vv;
	};
}
