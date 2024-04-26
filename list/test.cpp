#include<iostream>
#include<list>
#include<queue>
#include<utility>
#include"list.h"
int main()
{
	M::list<int> li;
	li.push_back(1);
	li.push_back(2);
	li.push_back(4);
	li.emplace_back(5);
	//li.insert(li.begin(), 1);
	//li.insert(li.end(), 2);
	//li.insert(li.end(), 3);
	//li.insert(li.end(), 4);
	//auto it = li.begin();
	//M::list<int>::const_reverse_iterator rbegin = li.crbegin();
	//while (rbegin != li.crend())
	//{
	//	std::cout << *(rbegin.operator->()) << " ";
	//	++rbegin;
	//}
	//std::cout << li.size();
	//return 0;

}
