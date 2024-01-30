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
	M::priority_queue<int,std::vector<int>,less<int>> st;
	st.push(1);
	st.push(5);
	st.push(3);
	st.push(6);
	while (!st.empty())
	{
		std::cout << st.top() << " ";
		st.pop();
	}
	std::cout << std::endl;
	std::cout << less<int>()(1, 2) << std::endl;
	return 0;
}