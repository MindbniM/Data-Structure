#include<iostream>
#include<utility>
#include<stack>
using namespace std; 
#include"AVL.h"
int main()
{
    AVLTree<int,int> node;
    node.insert(pair<int,int>(5,10));
    node.insert(pair<int,int>(6,30));
    node.insert(pair<int,int>(7,20));
    node.order();
    return 0;
}
