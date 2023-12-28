#include"AVL.h"
AVLTree::AVLTree()
	:_root(nullptr)
{

}
AVLTree::~AVLTree()
{
	_root->TreeDestroy();
	_root = nullptr;
}
void AVLTree::Insert(TreeType val)
{
	_root = _root->InsertHeap(val);
}
void AVLTree::Remove(TreeType val)
{
	_root = _root->RemoveHelp(val);
}
TreeNode* AVLTree::Search(TreeType val)
{
	return _root->search(val);
}
void operator<< (std::ostream& out, const AVLTree& Tree)
{
	Tree._root->InOrder();
	out << std::endl;
}
