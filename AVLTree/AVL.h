#pragma once
#include<iostream>
#include<math.h>
typedef int TreeType;
class TreeNode
{
public:
	TreeNode(TreeType x);
	int Height();
	~TreeNode();
	int TreeHeight();
	int balanceFactor();//获取平衡因子
	TreeNode* RightRotate();
	TreeNode* LefttRotate();
	TreeNode* rotate();
	void TreeDestroy();
	TreeNode* search(TreeType val);
	TreeNode* InsertHeap(TreeType val);
	TreeNode* RemoveHelp(TreeType val);
	void InOrder();

private:
	TreeType _val;
	int _height;
	TreeNode* _left;
	TreeNode* _right;
};
class AVLTree
{
public:
	AVLTree();
	~AVLTree();
	void Insert(TreeType val);
	void Remove(TreeType val);
	TreeNode*Search(TreeType val);
	friend void operator<< (std::ostream& out, const AVLTree& Tree);

private:
	TreeNode* _root;
};
void operator<< (std::ostream& out, const AVLTree& Tree);
