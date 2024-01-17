#include"111.h"
int main()
{
	M::string s1;
	s1.push_back('a');
	s1.push_back('a');
	s1.push_back('a');
	s1.push_back('a');
	s1.push_back('a');
	s1.push_back('a');
	cout << s1.capacity() << endl;
	cout << s1.size() << endl;
	cout << s1.c_str() << endl;
	s1 += 'c';
	cout << s1.c_str() << endl;
	return 0;
}