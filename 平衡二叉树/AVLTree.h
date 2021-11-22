#pragma once	//防止头文件重复引入
#include <iostream>
#include <iomanip>
using namespace std;
/*
	预处理 预编译 编译 链接
	#ifndef _AVLTREE_H_	//如果没有定义这个宏
	#define _AVLTREE_H_

	#endif
*/

//平衡二叉树节点类型
template<class T>
struct TreeNode
{
	T data;				//数据
	TreeNode* pLeft;	//左孩子
	TreeNode* pRight;	//右孩子
	int height;			//高度

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
	AVLTree() { pRoot = NULL; }	//无参构造 内联
	~AVLTree() {}				//析构

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
	TreeNode<T>* RR(TreeNode<T>* pRoot);	//右旋
	TreeNode<T>* LL(TreeNode<T>* pRoot);	//左旋
	TreeNode<T>* LR(TreeNode<T>* pRoot);	//左右旋
	TreeNode<T>* RL(TreeNode<T>* pRoot);	//右左旋

};



template<class T>
TreeNode<T>* AVLTree<T>::RR(TreeNode<T>* pRoot)	//右旋
{
	TreeNode<T>* child;
	child = pRoot->pLeft;
	pRoot->pLeft = child->pRight;
	child->pRight = pRoot;
	return child;
}

template<class T>
TreeNode<T>* AVLTree<T>::LL(TreeNode<T>* pRoot)	//左旋
{
	TreeNode<T>* child;
	child = pRoot->pRight;
	pRoot->pRight = child->pLeft;
	child->pLeft = pRoot;
	return child;
}

template<class T>
TreeNode<T>* AVLTree<T>::LR(TreeNode<T>* pRoot)	//左右旋
{
	TreeNode<T>* child;
	child = pRoot->pLeft;
	pRoot->pLeft = AVLTree<T>::LL(child);
	pRoot = AVLTree<T>::RR(pRoot);
	return pRoot;
}

template<class T>
TreeNode<T>* AVLTree<T>::RL(TreeNode<T>* pRoot)	//右左旋
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
	//作为平衡二叉树，先是有序二叉树
	//1以有序二叉树插入
	if (NULL == root)
	{
		root = new TreeNode<T>(data);
	}
	else if (data > root->data)
	{
		_insertNodeToTree(root->pRight, data);
		//2检查是否需要旋转，需要就旋转
		if (_getHeight(root->pRight) - _getHeight(root->pLeft) > 1)
		{
			//右边比左边高
			if (data > root->pRight->data)
			{
				std::cout << "右旋";
				root = LL(root);	//以root为轴右旋——返回值赋值给root——修改根节点
			}
			else
			{
				std::cout << "右左旋";
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
				//左边比右边高
				std::cout << "左旋";
				root = RR(root);
			}
			else
			{
				std::cout << "左右旋";
				root = LR(root);

			}

		}
	}
	

	//3设置高度
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
		if (direction == 0)    // tree是根节点
			cout << setw(2) << tree->data << " is root" << endl;
		else                // tree是分支节点
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