#include<iostream>
#include<utility>
#include<vector>
#include<stack>
#include<assert.h>
using namespace std; 
#include"AVL.h"
int main()
{
    const int N = 5;
    AVLTree<int, int> node;
    srand(time(nullptr));
    vector<int> v{ 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
    for (int i = 0;i < v.size(); i++)
    {
        node.insert(make_pair(v[i],1));
        if (!node.isAVLTree())
        {
            int a = 1;
        }

    }
    /*for (int i = 0; i < N; i++)
    {
        int n = rand()%100;
        node.insert(make_pair(n,1));
        cout << i<<"->"<<n<<endl;
    }*/
    /*node.insert(make_pair(6, 1));
    node.insert(make_pair(2, 1));
    node.insert(make_pair(3, 1));
    node.insert(make_pair(0, 1));
    node.inorder();
    cout << endl;*/
    return 0;
}
