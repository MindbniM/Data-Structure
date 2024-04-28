#include<iostream>
#include<string>
#include<vector>
#include<assert.h>
#include<algorithm>
#include<utility>
#include"vector.h"
int main()
{
	M::vector<int> v;
	v.emplace_back(1);
	std::cout << v[0];
	return 0;
}