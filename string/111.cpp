#include"str.h"
int main()
{
	M::string s1("hello");
	/*M::string::const_iterator it = s2.begin();
	while (it != s2.end())
	{
		cout << *it << " ";
		++it;reverse
	}*/
	//s1.reserve(10);
	s1.resize(20);
	char* str = s1.c_str();
	cout << s1.capacity() << endl;
	cout << s1.size() << endl;

	return 0;
}