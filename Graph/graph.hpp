#pragma once
#include"run_error.hpp"
#include"UnionFindSet.hpp"
#include<vector>
#include<queue>
#include<map>
namespace matrix
{
	template<class W>
	struct edge
	{
		int _begin;
		int _end;
		W _w;
		edge(int begin,int end,W w):_begin(begin),_end(end),_w(w)
		{}
		bool operator>(const edge<W>& e) const
		{
			return _w > e._w;
		}
		bool operator<(const edge<W>& e) const
		{
			return _w < e._w;
		}
	};
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
				_hash[n++] = i;
			}
			_vv.resize(size);
			for (auto& v : _vv) v.resize(size, invalid);
		}
		bool insert_edge(const V& v1, const V& v2,const W& w)
		{
			size_t n1 = get_v_index(v1), n2 = get_v_index(v2);
			if (n1 == -1 || n2 == -1)
			{
				throw run_exception("节点不存在\n");
			}
			_vv[n1][n2] = w;
			if (!Direction)
			{
				_vv[n2][n1] = w;
			}
			return true;
		}
		W kruskal()
		{
			int n = _vv.size();
			std::vector<std::vector<W>> vv(n,std::vector<W>(n,invalid));
			std::priority_queue<edge<W>, std::vector<edge<W>>, std::greater<edge<W>>> q;
			udf U(n);
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					if (_vv[i][j] != invalid)
					{
						if (!Direction)
						{
							if(i<j) q.push(edge<W>(i, j, _vv[i][j]));
						}
						else
						{
							q.push(edge<W>(i, j, _vv[i][j]));
						}
					}
				}
			}
			W num=W();
			int len = 0;
			while (!q.empty())
			{
				edge<W> e = q.top();
				if (!U.is_Union(e._begin, e._end))
				{
					U.Union(e._begin, e._end);
					std::cout << _hash[e._begin] << "->" << _hash[e._end] << std::endl;
					vv[e._begin][e._end] = e._w;
					if (!Direction)
					{
						vv[e._end][e._begin] = e._w;
					}
					len++;
				}
				q.pop();
			}
			if (len == n - 1)
			{
				print(vv);
				return num;
			}
			throw run_exception("图不是联通的\n");

		}
		W prim()
		{

		}
	private:
		void print(std::vector<std::vector<W>>& vv)
		{
			std::cout << "     ";
			for (int i = 0; i < vv.size(); i++)
			{
				printf("%-4d", i);
			}
			std::cout << std::endl;
			for (int i = 0; i < vv.size(); i++)
			{
				std::cout << i << "    ";
				for (int j = 0; j < vv[i].size(); j++)
				{
					printf("%-4d", vv[i][j]);
				}
				std::cout << std::endl;
			}
		}
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
		std::map<int,V> _hash;
		std::map<V,int> _map;
		std::vector<std::vector<W>> _vv;
	};
}
