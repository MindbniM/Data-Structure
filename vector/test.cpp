#include<iostream>
#include<string>
#include<vector>
#include<assert.h>
#include<algorithm>
#include<utility>
#include"vector.h"
M::vector<int>  fun()
{
	M::vector<int> vv({1,2,3,4,5});

	return vv;
}
int main()
{
	M::vector<int> v;
	v = fun();
	for (auto i : v) std::cout << i << " ";

	return 0;
}