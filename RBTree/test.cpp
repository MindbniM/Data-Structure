#include<iostream>
#include<vector>
#include<stdlib.h>
#include"RBTree.h"

int main()
{
	RBTree<int,int> root;
    std::vector<int> v{ 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
    std::vector<int> vv;

    /*const int n = 1000000;
    srand(time(nullptr));
    for (int i = 0; i < n; i++)
    {
        int n = rand();
        root.insert(n+i);
    }*/
    for (int i = 0; i < v.size(); i++)
    {
        root.insert(v[i]);
        //root.inorder();
        //std::cout << std::endl;
    }
    RBTree<int, int>::iterator it = root.begin();
    std::cout << *(it + 2) << std::endl;
    while (it != root.end())
    {
        std::cout << *it << " ";
        it++;
    }
    //std::cout<<root.isRBTree();

	return 0;
}