#include<iostream>
#include<string>
#include<vector>
#include<assert.h>
#include<algorithm>
#include<list>
#include"vector.h"
int main()
{
	std::list<char> lc;
	lc.push_back('a');
	lc.push_back('b');
	lc.push_back('c');
	lc.push_back('d');
	M::vector<char> v(lc.begin(), lc.end());
	for (auto& e : v)
	{
		std::cout << e << " ";
	}
	return 0;
}