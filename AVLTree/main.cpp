#include"AVL.h"

void nume()
{
	std::cout << "**********************************************" << std::endl;
	std::cout << "**1.����***********************2.����*********" << std::endl;
	std::cout << "**3.ɾ��***********************4.����*********" << std::endl;
	std::cout << "**5.�޸�***********************0.���ٲ��˳�***" << std::endl;
	std::cout << "**********************************************" << std::endl;

	std::cout << "����ѡ��>>:";
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
//			std::cout << "����Ҫ��������ݸ���" << std::endl;
//			int cou;
//			std::cin >> cou;
//			std::cout << "����Ҫ���������" << std::endl;
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
//			std::cout << "����Ҫ���ҵ�����" << std::endl;
//			int val;
//			std::cin >> val;
//			TreeNode<int>* root = T->Search(val);
//			if (root != nullptr)
//			{
//				std::cout << "�ҵ���" << std::endl;
//				break;
//			}
//			std::cout << "û�ҵ�" << std::endl;
//			break;
//		}
//		case 3:
//		{
//			std::cout << "����Ҫɾ��������" << std::endl;
//			int val;
//			std::cin >> val;
//			TreeNode<int>* root = T->Search(val);
//			if (root != nullptr)
//			{
//				std::cout << "�ҵ���" << std::endl;
//				T->Remove(val);
//				std::cout << "��ɾ��" << std::endl;
//				break;
//			}
//			std::cout << "û�ҵ�" << std::endl;
//			break;
//		}
//		case 4:
//		{
//			std::cout << *T;
//			break;
//		}
//		case 5:
//		{
//			std::cout << "����Ҫ�޸ĵ�����" << std::endl;
//			int val;
//			std::cin >> val;
//			std::cout << "�����޸ĺ������" << std::endl;
//			int _val;
//			std::cin >> _val;
//			TreeNode<int>* root = T->Search(val);
//			if (root != nullptr)
//			{
//				std::cout << "�ҵ���" << std::endl;
//				T->Insert(_val, comp);
//				T->Remove(val);
//				std::cout << "���޸�" << std::endl;
//				break;
//			}
//			std::cout << "û�ҵ�" << std::endl;
//			break;
//		}
//		default:
//		{
//			std::cout << "�������,��������" << std::endl;
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