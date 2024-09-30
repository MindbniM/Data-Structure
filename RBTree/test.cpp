#include<iostream>
#include<vector>
#include<utility>
#include<functional>
#include"map.h"
#include"set.h"
//#include<stdlib.h>
//#include"RBTree.h"
//
//int main()
//{
//	RBTree<int,int> root;
//    std::vector<int> v{ 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
//    std::vector<int> vv;
//
//    /*const int n = 1000000;
//    srand(time(nullptr));
//    for (int i = 0; i < n; i++)
//    {
//        int n = rand();
//        root.insert(n+i);
//    }*/
//    for (int i = 0; i < v.size(); i++)
//    {
//        root.insert(v[i]);
//        //root.inorder();
//        //std::cout << std::endl;
//    }
//    RBTree<int, int>::iterator it = root.begin();
//    std::cout << *(it + 2) << std::endl;
//    while (it != root.end())
//    {
//        std::cout << *it << " ";
//        it++;
//    }
//    //std::cout<<root.isRBTree();
//
//	return 0;
//}
//int main()
//{
//	set<int> s;
//	std::vector<int> v{ 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
//	for (auto& i : v)
//	{
//		s.insert(i);
//	}
//	set<int>::iterator it = s.begin();
//	while (it != s.end())
//	{
//		std::cout << *it << " ";
//		++it;
//	}
//	return 0;
//}
int main()
{
	map<std::string, int> hash;
	std::vector<std::string> v{ "5","1","6","7","9"};
	for (auto& s : v)
	{
		hash[s]++;
	}
	//hash.clear();
	hash.emplace("0", 20);
	std::cout << hash.size() << std::endl;
	std::cout << hash["0"] << std::endl;
	return 0;
}