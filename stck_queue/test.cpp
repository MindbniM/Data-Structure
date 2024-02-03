#include<iostream>
#include<queue>
#include<vector>
#include<stack>
#include"stack.h"
#include"queue.h"
template<class T>
class less
{
public:
	bool operator()(const T& n1, const T& n2)
	{
		return n1 < n2;
	}
};
template<class T>
class less<T*>
{
public:
	bool operator()(T* n1,  T* n2)
	{
		return *n1 < *n2;
	}
};

template<class T>
class greater
{
public:
	bool operator()(const T& n1, const T& n2)
	{
		return n1 > n2;
	}
};
int main()
{
	M::priority_queue<int*,std::vector<int*>,less<int*>> st;
	st.push(new int(1));
	st.push(new int(5));
	st.push(new int(4));
	st.push(new int(6));
	while (!st.empty())
	{
		std::cout << *st.top() << " ";
		st.pop();
	}
	std::cout << std::endl;
	return 0;
}