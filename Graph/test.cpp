#include<iostream>
#include<functional>
#include<memory>
#include<mutex>
#include<thread>
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
	shared_ptr<int> ptr(new int(1));
	int n = 1000;
	std::thread t1([=]()
		{
			for (int i = 0; i < n; i++)
			{
				shared_ptr<int> p = ptr;
				//std::cout << ptr.count() << std::endl;

			}
		}
	);
	std::thread t2([=]()
		{
			for (int i = 0; i < n; i++)
			{
				shared_ptr<int> p = ptr;
				//std::cout << ptr.count() << std::endl;

			}
		}
	);
	t1.join();
	t2.join();
	return 0;
}