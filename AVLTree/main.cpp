#include"AVL.h"

void nume()
{
	std::cout << "**********************************************" << std::endl;
	std::cout << "**1.插入***********************2.查找*********" << std::endl;
	std::cout << "**3.删除***********************4.遍历*********" << std::endl;
	std::cout << "**5.修改***********************0.销毁并退出***" << std::endl;
	std::cout << "**********************************************" << std::endl;

	std::cout << "输入选项>>:";
}
int comp(int a, int b)
{
	return a - b;
}
//void test1()
//{
//	int n = 1;
//	AVLTree<int>* T = new AVLTree<int>();
//	while (n)
//	{
//		nume();
//		std::cin >> n;
//		switch (n)
//		{
//		case 0:
//		{
//			delete  T;
//			break;
//		}
//		case 1:
//		{
//			std::cout << "输入要插入的数据个数" << std::endl;
//			int cou;
//			std::cin >> cou;
//			std::cout << "输入要插入的数据" << std::endl;
//			for (int i = 0; i < cou; i++)
//			{
//				int val;
//				std::cin >> val;
//				T->Insert(val, comp);
//			}
//			break;
//		}
//		case 2:
//		{
//			std::cout << "输入要查找的数据" << std::endl;
//			int val;
//			std::cin >> val;
//			TreeNode<int>* root = T->Search(val);
//			if (root != nullptr)
//			{
//				std::cout << "找到了" << std::endl;
//				break;
//			}
//			std::cout << "没找到" << std::endl;
//			break;
//		}
//		case 3:
//		{
//			std::cout << "输入要删除的数据" << std::endl;
//			int val;
//			std::cin >> val;
//			TreeNode<int>* root = T->Search(val);
//			if (root != nullptr)
//			{
//				std::cout << "找到了" << std::endl;
//				T->Remove(val);
//				std::cout << "已删除" << std::endl;
//				break;
//			}
//			std::cout << "没找到" << std::endl;
//			break;
//		}
//		case 4:
//		{
//			std::cout << *T;
//			break;
//		}
//		case 5:
//		{
//			std::cout << "输入要修改的数据" << std::endl;
//			int val;
//			std::cin >> val;
//			std::cout << "输入修改后的数据" << std::endl;
//			int _val;
//			std::cin >> _val;
//			TreeNode<int>* root = T->Search(val);
//			if (root != nullptr)
//			{
//				std::cout << "找到了" << std::endl;
//				T->Insert(_val, comp);
//				T->Remove(val);
//				std::cout << "已修改" << std::endl;
//				break;
//			}
//			std::cout << "没找到" << std::endl;
//			break;
//		}
//		default:
//		{
//			std::cout << "输入错误,重新输入" << std::endl;
//			break;
//		}
//		}
//	}
//}

int main()
{
	AVLTree<int>* a=new AVLTree<int>();
	a->Insert(1, comp);
	a->Insert(2, comp);
	a->Insert(6, comp);
	a->Insert(5, comp);
	a->_root->InOrder();
	delete a;
	return 0;
}