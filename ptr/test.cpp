#include<iostream>
#include<functional>
#include<memory>
#include"ptr.h"
template<class T>
struct D
{
	void operator()(T* ptr)
	{
		delete[] ptr;
	}
};
int main()
{
	shared_ptr<int> p(new int[5]{1},D<int>());

	return 0;
}