#include<iostream>
#include<list>
#include"list.h"
int main()
{
	M::list<int> li;
	li.insert(li.begin(), 1);
	li.insert(li.end(), 2);
	li.insert(li.end(), 3);
	li.insert(li.end(), 4);
	M::list<int>::iterator begin = li.begin();
	while (begin != li.end())
	{
		std::cout << *begin << " ";
		++begin;
	}
	std::cout << std::endl;
	M::list<int> l;
	l.resize(10, 10);
	begin = l.begin();
	while (begin != l.end())
	{
		std::cout << *begin << " ";
		++begin;
	}
	return 0;
}