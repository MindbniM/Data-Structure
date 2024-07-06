#pragma once
#include<vector>
class udf
{
public:
	udf(int n):_n(n),_v(n,-1)
	{}
	bool Union(int u1, int u2)
	{
		int n1 = find_head(u1), n2 = find_head(u2);
		if (n1 != n2)
		{
			_v[n1] += _v[n2];
			_v[n2] = n1;
			return true;
		}
		return false;
	}
	bool is_Union(int u1, int u2)
	{
		int n1 = find_head(u1), n2 = find_head(u2);
		return n1 == n2;
	}

private:
	int find_head(int n)
	{
		if (n >= _n) return -1;
		while (_v[n] >= 0)
		{
			n = _v[n];
		}
		return n;
	}
	int _n;
	std::vector<int> _v;
};
