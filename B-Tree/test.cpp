#include"BTree.hpp"
#include<vector>
#include<iostream>
using namespace std;
int main()
{
	BTree<int> t;
	vector<int> v = { 53, 139, 75, 49, 145, 36, 101 };
	for (auto& i : v)
	{
		t.insert(i);
	}
	return 0;
}