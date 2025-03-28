#include "SkipList.hpp"
int main()
{
	Skiplist<int> list;
	list.add(1);
	list.add(8);
	list.add(3);
	list.add(2);
	return 0;
}