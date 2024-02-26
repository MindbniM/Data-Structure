#include<iostream>
#include<string>
#include<vector>
#include<assert.h>
#include<algorithm>
#include<list>
#include"vector.h"
int main()
{
	M::vector<char> v;
	v.push_back('a');
	v.push_back('b');
	v.push_back('c');
	v.push_back('d');
	M::vector<char>::reverse_iterator rit = v.rbegin();
	while (rit != v.rend())
	{
		std::cout << *rit << " ";
		++rit;
	}
	return 0;
}