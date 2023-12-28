#include"AVL.h"
TreeNode::TreeNode(TreeType x)
	:_val(x)
	,_left(nullptr)
	,_right(nullptr)
	,_height(0)
{
}
TreeNode::~TreeNode()
{
	_left = nullptr;
	_right = nullptr;
}
int TreeNode::Height()
{
	if (this == nullptr)
		return 0;
	return _height;
}
int TreeNode::TreeHeight()
{
	if (this == nullptr)
		return 0;
	return fmax(_left->TreeHeight(),_right->TreeHeight())+1;
}
int TreeNode::balanceFactor()
{
	if (this == nullptr)
		return 0;
	return _left->Height() - _right->Height();
}
TreeNode* TreeNode::RightRotate()
{
	TreeNode* child = _left;
	TreeNode* cchild = child->_right;
	child->_right = this;
	_left = cchild;
	_height = TreeHeight();
	child->_height = child->TreeHeight();
	return child;
}
TreeNode* TreeNode::LefttRotate()
{
	TreeNode* child = _right;
	TreeNode* cchild = child->_left;
	child->_left = this;
	_right = cchild;
	_height = TreeHeight();
	child->_height = child->TreeHeight();
	return child;
}
TreeNode* TreeNode::rotate()
{
	int n = balanceFactor();
	if (n > 1)
	{
		if (_left->balanceFactor() < 0)
		{
			_left = _left->LefttRotate();
		}
		return RightRotate();
	}
	if (n < -1)
	{
		if (_right->balanceFactor() > 0)
		{
			_right = _right->RightRotate();
		}
		return LefttRotate();
	}
	return this;
}
void TreeNode::TreeDestroy()
{
	if (this == nullptr)
		return;
	_left->TreeDestroy();
	_right->TreeDestroy();
	delete(this);
}
TreeNode* TreeNode::InsertHeap(TreeType val)
{
	if (this == nullptr)
		return new TreeNode(val);
	if (val < _val)
		_left = _left->InsertHeap(val);
	else if (val > _val)
		_right = _right->InsertHeap(val);
	else
		return this;
	_height = TreeHeight();
	TreeNode* node=rotate();
	return node;
}
TreeNode* TreeNode::RemoveHelp(TreeType val)
{
	if (this == nullptr)
		return nullptr;
	TreeNode* root = this;
	if (_val > val)
	{
		_left = _left->RemoveHelp(val);
	}
	else if (_val < val)
	{
		_right = _right->RemoveHelp(val);
	}
	else
	{
		if (!_left || !_right)
		{
			delete(this);
			return nullptr;
		}
		else if (_left && _right)
		{
			TreeNode* temp = _right;
			while (temp->_left != nullptr)
			{
				temp = temp->_left;
			}
			TreeType n = temp->_val;
			_right = _right->RemoveHelp(n);
			_val = n;
		}
		else
		{
			TreeNode* node = _left == nullptr ? _right : _left;
			delete(this);
			root = node;
		}
	}
	root->TreeHeight();
	root = root->rotate();
	return root;
}
TreeNode* TreeNode::search(TreeType num) 
{
	TreeNode* cur = this;
	while (cur != nullptr) {
		if (cur->_val < num)
			cur = cur->_right;
		else if (cur->_val > num)
			cur = cur->_left;
		else
			break;
	}
	return cur;
}
void TreeNode::InOrder()
{
	if (this == NULL)
		return;
	_left->InOrder();
	std::cout << _val << " ";
	_right->InOrder();
}