#ifndef AVL.H
#define AVL.H 0
#include<iostream>
#include<math.h>
template<class TreeType>
class TreeNode
{
public:
	TreeNode(TreeType x);
	int Height();
	~TreeNode();
	int TreeHeight();
	int balanceFactor();//获取平衡因子
	TreeNode<TreeType>* RightRotate();
	TreeNode<TreeType>* LefttRotate();
	TreeNode<TreeType>* rotate();
	void TreeDestroy();
	TreeNode<TreeType>* search(TreeType val);
	TreeNode<TreeType>* InsertHeap(TreeType val, int (*comp)(TreeType, TreeType));
	TreeNode<TreeType>* RemoveHelp(TreeType val);
	void InOrder();

private:
	TreeType _val;
	int _height;
	TreeNode<TreeType>* _left;
	TreeNode<TreeType>* _right;
};
template<class TreeType>
class AVLTree
{
public:
	AVLTree();
	~AVLTree();
	void Insert(TreeType val, int (*comp)(TreeType, TreeType));
	void Remove(TreeType val);
	TreeNode<TreeType>* Search(TreeType val);
	friend void operator<< (std::ostream& out, const AVLTree<TreeType>& Tree);

//private:
	TreeNode<TreeType>* _root;
};
template<class TreeType>
void operator<< (std::ostream& out, const AVLTree<TreeType>& Tree);

#include"AVL.cpp"
#include"TreeNode.cpp"
#endif