#include"AVL.h"
template<class TreeType>
AVLTree<TreeType>::AVLTree()
	:_root(nullptr)
{

}
template<class TreeType>
AVLTree<TreeType>::~AVLTree()
{
	_root->TreeDestroy();
	_root = nullptr;
}
template<class TreeType>
void AVLTree<TreeType>::Insert(TreeType val, int (*comp)(TreeType, TreeType))
{
	_root = _root->InsertHeap(val,comp);
}
template<class TreeType>
void AVLTree<TreeType>::Remove(TreeType val)
{
	_root = _root->RemoveHelp(val);
}
template<class TreeType>
TreeNode<TreeType>* AVLTree<TreeType>::Search(TreeType val)
{
	return _root->search(val);
}
template<class TreeType>
void operator<< (std::ostream& out, const AVLTree<TreeType>& Tree)
{
	Tree._root->InOrder();
	out << std::endl;
}
