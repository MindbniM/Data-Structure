#include"str.h"
int main()
{
	const M::string s1("hello");
	M::string s3(" word");
	M::string s2;
	s2+= s3;
	s2.insert(0, s1);
	cout << s2.c_str() << endl;;
	cout << s2.find("o") << endl;

	return 0;
}