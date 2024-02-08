#include<iostream>
#include<stack>
#include"SearchTree.h"
int main()
{
	M::SearchTree<int> root;
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
	for (auto e : a)
	{
		root.insert(e);
	}
	root.in_order();
	M::SearchTree<int> r;
	r = root;
	r.in_order();
	//for (auto e : a)
	//{
	//	root.erase(e);
	//	std::cout << e << "                      ";
	//	root.in_order();
	//}
	//root.in_order();
	return 0;
}