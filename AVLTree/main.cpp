#include"AVL.h"
int main()
{
	AVLTree* T = new AVLTree();
	T->Insert(5);
	T->Insert(6);
	T->Insert(2);
	T->Insert(5);
	T->Insert(4);
	T->Insert(9);
	T->Insert(12);
	T->Insert(30);
	std::cout << *T;
	delete(T);
	return 0;
}