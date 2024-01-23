#include"str.h"
int main()
{
	M::string s1("12345");
	M::string s2 = s1.substr(0,2);
	cout << s2<<endl;
	return 0;
}