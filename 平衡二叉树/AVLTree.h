#pragma once	//��ֹͷ�ļ��ظ�����
#include <iostream>
#include <iomanip>
using namespace std;
/*
	Ԥ���� Ԥ���� ���� ����
	#ifndef _AVLTREE_H_	//���û�ж��������
	#define _AVLTREE_H_

	#endif
*/

//ƽ��������ڵ�����
template<class T>
struct TreeNode
{
	T data;				//����
	TreeNode* pLeft;	//����
	TreeNode* pRight;	//�Һ���
	int height;			//�߶�

	TreeNode(const T& data)
	{
		this->data = data;
		pLeft = pRight = NULL;
		height = 0;
	}
};



template<class T>
class AVLTree
{
	TreeNode<T>* pRoot;
public:
	AVLTree() { pRoot = NULL; }	//�޲ι��� ����
	~AVLTree() {}				//����

	void insert(const T& data);
	void preOrder();
	void postOrder();
	void print();
private:
	void _insertNodeToTree(TreeNode<T>*& root, const T& data);
	int _getHeight(TreeNode<T>* pRoot);
	void preOrder(TreeNode<T>* tree) const;
	void postOrder(TreeNode<T>* tree) const;
	void print(TreeNode<T>* tree, T key, int direction);
	TreeNode<T>* RR(TreeNode<T>* pRoot);	//����
	TreeNode<T>* LL(TreeNode<T>* pRoot);	//����
	TreeNode<T>* LR(TreeNode<T>* pRoot);	//������
	TreeNode<T>* RL(TreeNode<T>* pRoot);	//������

};



template<class T>
TreeNode<T>* AVLTree<T>::RR(TreeNode<T>* pRoot)	//����
{
	TreeNode<T>* child;
	child = pRoot->pLeft;
	pRoot->pLeft = child->pRight;
	child->pRight = pRoot;
	return child;
}

template<class T>
TreeNode<T>* AVLTree<T>::LL(TreeNode<T>* pRoot)	//����
{
	TreeNode<T>* child;
	child = pRoot->pRight;
	pRoot->pRight = child->pLeft;
	child->pLeft = pRoot;
	return child;
}

template<class T>
TreeNode<T>* AVLTree<T>::LR(TreeNode<T>* pRoot)	//������
{
	TreeNode<T>* child;
	child = pRoot->pLeft;
	pRoot->pLeft = AVLTree<T>::LL(child);
	pRoot = AVLTree<T>::RR(pRoot);
	return pRoot;
}

template<class T>
TreeNode<T>* AVLTree<T>::RL(TreeNode<T>* pRoot)	//������
{
	TreeNode<T>* child;
	child = pRoot->pRight;
	pRoot->pRight = AVLTree<T>::RR(child);
	pRoot = AVLTree<T>::LL(pRoot);
	return pRoot;
}

template<class T>
void AVLTree<T>::insert(const T& data)
{
	_insertNodeToTree(pRoot, data);
}
template<class T>
int AVLTree<T>::_getHeight(TreeNode<T>* pRoot)
{
	if (pRoot)
		return pRoot->height;
	else return 0;
}

template<class T>
void AVLTree<T>::_insertNodeToTree(TreeNode<T>*& root, const T& data)
{
	//��Ϊƽ����������������������
	//1���������������
	if (NULL == root)
	{
		root = new TreeNode<T>(data);
	}
	else if (data > root->data)
	{
		_insertNodeToTree(root->pRight, data);
		//2����Ƿ���Ҫ��ת����Ҫ����ת
		if (_getHeight(root->pRight) - _getHeight(root->pLeft) > 1)
		{
			//�ұ߱���߸�
			if (data > root->pRight->data)
			{
				std::cout << "����";
				root = LL(root);	//��rootΪ��������������ֵ��ֵ��root�����޸ĸ��ڵ�
			}
			else
			{
				std::cout << "������";
				root = RL(root);

			}

		}
	}
	else
	{
		_insertNodeToTree(root->pLeft, data);
		if (_getHeight(root->pLeft) - _getHeight(root->pRight) > 1)
		{
			if (data < root->pLeft->data)
			{
				//��߱��ұ߸�
				std::cout << "����";
				root = RR(root);
			}
			else
			{
				std::cout << "������";
				root = LR(root);

			}

		}
	}
	

	//3���ø߶�
	int lh = _getHeight(root->pLeft);
	int rh = _getHeight(root->pRight);

	root->height = 1 + ((lh > rh) ? lh : rh);
}

template <class T>
void AVLTree<T>::preOrder(TreeNode<T>* pRoot) const
{
	if (pRoot != NULL)
	{
		std::cout << pRoot->data << " ";
		preOrder(pRoot->pLeft);
		preOrder(pRoot->pRight);
	}
}
template <class T>
void AVLTree<T>::preOrder()
{
	preOrder(pRoot);
}

template <class T>
void AVLTree<T>::postOrder(TreeNode<T>* pRoot) const
{
	if (pRoot != NULL)
	{
		preOrder(pRoot->pLeft);
		preOrder(pRoot->pRight);
		std::cout << pRoot->data << " ";
	}
}
template <class T>
void AVLTree<T>::postOrder()
{
	postOrder(pRoot);
}


template <class T>
void AVLTree<T>::print(TreeNode<T>* tree, T data, int direction)
{
	if (tree != NULL)
	{
		if (direction == 0)    // tree�Ǹ��ڵ�
			cout << setw(2) << tree->data << " is root" << endl;
		else                // tree�Ƿ�֧�ڵ�
			cout << setw(2) << tree->data << " is " << setw(2) << data << "'s " << setw(12) << (direction == 1 ? "right child" : "left child") << endl;

		print(tree->pLeft, tree->data, -1);
		print(tree->pRight, tree->data, 1);
	}
}

template <class T>
void AVLTree<T>::print()
{
	if (pRoot != NULL)
		print(pRoot, pRoot->data, 0);
}