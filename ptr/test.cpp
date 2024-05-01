#include<iostream>
#include<memory>
#include"ptr.h"
int main()
{
	shared_ptr<int> ptr(new int(1));
	shared_ptr<int> p(new int(2));
	p = ptr;

	return 0;
}