#pragma once
#include<iomanip>
#include<iostream>
using namespace std;
//树的节点
template<class T>
class AVLTreeNode
{
public:
	AVLTreeNode(T value, AVLTreeNode* l, AVLTreeNode* r) :
		key(value), Left(l), Right(r) {}
	T key;	//键值
	int height;	//高度
	AVLTreeNode* Left;
	AVLTreeNode* Right;
	AVLTreeNode();
};

template<class T>
AVLTreeNode<T>::AVLTreeNode()
{
	key = 0;
	Left = Right = NULL;
	height = 0;
}
//树的类
template<class T>
class AVLTree
{
private:
	AVLTreeNode<T>* root;
public:
	//外部接口
	AVLTree();
	~AVLTree();

	//获取树的高度
	int height(AVLTreeNode<T>* tree);
	//比较两个值的大小
	int max(int a, int b);

	//前序遍历
	void preorder(AVLTreeNode<T>* tree);
	//中序遍历
	void inorder(AVLTreeNode<T>* tree);
	//后序遍历
	void postorder(AVLTreeNode<T>* tree);

	//查找AVL树中的值的节点
	AVLTreeNode<T>* search(AVLTreeNode<T>* tree, T key);
	//最大值最小值
	T miniNode(AVLTreeNode<T>* tree);
	T maxNode(AVLTreeNode<T>* tree);

	//插入节点
	AVLTreeNode<T>* insert(AVLTreeNode<T>*& tree, T key);
	//删除节点
	AVLTreeNode<T>* remove(AVLTreeNode<T>*& tree, T reNode);

	//销毁树
	void destroy(AVLTreeNode<T>*& tree);
	//打印树
	void print();


	//LL：左左对应的情况（左单旋）
	AVLTreeNode<T>* LL_Rotation(AVLTreeNode<T>* key1);
	//RR：右右对应的情况（右单旋）
	AVLTreeNode<T>* RR_Rotation(AVLTreeNode<T>* key2);
	//LR：左右			（左双旋）
	AVLTreeNode<T>* LR_Rotation(AVLTreeNode<T>* key3);
	//RL：右左			（右双旋）
	AVLTreeNode<T>* RL_Rotation(AVLTreeNode<T>* key4);

private:
	void _print(AVLTreeNode<T>* tree, T key, int direction);
};

template<class T>
AVLTree<T>::~AVLTree()
{
	destroy(root);
}
template<class T>
int AVLTree<T>::max(int a, int b)
{
	return a > b ? a : b;
}


template<class T>
int AVLTree<T>::height(AVLTreeNode<T>* tree)
{
	if (tree != NULL)
		return tree->height;
	return 0;
}


//前序遍历
template<class T>
void AVLTree<T>::preorder(AVLTreeNode<T>* tree)
{
	if (tree != NULL)
	{
		cout << tree->key << " ";
		preorder(tree->Left);
		preorder(tree->Right);
	}
}
//中序
template<class T>
void AVLTree<T>::inorder(AVLTreeNode<T>* tree)
{
	if (tree != NULL)
	{
		inorder(tree->Left);
		cout << tree->key << " ";
		inorder(tree->Right);
	}
}
//后序
template<class T>
void AVLTree<T>::postorder(AVLTreeNode<T>* tree)
{
	if (tree != NULL)
	{
		postorder(tree->Left);
		postorder(tree->Right);
		cout << tree->key << " ";
	}
}


//查找
template<class T>
AVLTreeNode<T>* AVLTree<T>::search(AVLTreeNode<T>* tree, T key)
{
	if (tree == NULL || tree->key == key)
		return tree;
	if (key < tree->key)
		return search(tree->Left, key);
	else
		return search(tree->Right, key);
}
//最小值最大值
template<class T>
T AVLTree<T>::miniNode(AVLTreeNode<T>* tree)
{
	if (tree == NULL)
		return NULL;
	while (tree->Left != NULL)
		tree = tree->Left;
	return tree->key;
}
template<class T>
T AVLTree<T>::maxNode(AVLTreeNode<T>* tree)
{
	if (tree == NULL)
		return NULL;
	while (tree->Right != NULL)
		tree = tree->Right;
	return tree->key;
}

//销毁
template<class T>
void AVLTree<T>::destroy(AVLTreeNode<T>*& mainNode)
{
	if (mainNode == NULL)
		return;
	if (mainNode->Left != NULL)
		destroy(mainNode->Left);
	if (mainNode->Right != NULL)
		destroy(mainNode->Right);
	delete mainNode;
}
//打印
template<class T>
void AVLTree<T>::_print(AVLTreeNode<T>* tree, T key, int direction)
{
	if (tree != NULL)
	{
		
		if (direction == 0)
			cout << setw(2) << tree->key << "is root" << endl;
		else
			cout << setw(2) << tree->key << "is" << setw(2) << key << "'s" << setw(12) << (direction == 1 ? "right child" : "left child") << endl;
		_print(tree->Left, tree->key, -1);
		_print(tree->Right, tree->key, 1);
	}
}

template<class T>
void AVLTree<T>::print()
{
	
	if (root != NULL)
		_print(root, root->key, 0);
}


//插入
template<class T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>*& tree, T key)
{
	if (tree == NULL)
	{
		//新建结点
		tree = new AVLTreeNode<T>(key, NULL, NULL);
		if (tree == NULL)
		{
			cout << "创建树失败！" << endl;
			return NULL;
		}
	}
	else if (key < tree->key)
	{
		tree->Left = insert(tree->Left, key);
		// 插入结点后，若AVL树失去平衡，则进行相应的调节
		if (height(tree->Left) - height(tree->Right) == 2)
		{
			if (key < tree->Left->key)
				tree = LL_Rotation(tree);
			else
				tree = LR_Rotation(tree);
		}
	}
	else
	{
		tree->Right = insert(tree->Right, key);
		// 插入结点后，若AVL树失去平衡，则进行相应的调节
		if (height(tree->Right) - height(tree->Left) == 2)
		{
			if (key > tree->Right->key)
				tree = RR_Rotation(tree);
			else
				tree = RL_Rotation(tree);
		}
	}

	tree->height = max(height(tree->Left), height(tree->Right)) + 1;
	return tree;
}


template<class T>
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>*& tree, T key)
{
	AVLTreeNode<T>* reNode;
	if ((reNode = search(root, key)) != NULL)
	{
		//跟为空或没有要删除的节点
		if (tree == NULL || reNode == NULL)
			return NULL;
		if (reNode->key < tree->key)
		{
			tree->Left = remove(tree->Left, reNode->key);
			if (height(tree->Right) - height(tree->Left) == 2)
			{
				AVLTreeNode<T>* tempNode = tree->Right;
				if (height(tempNode->Left) > height(tempNode->Right))
					tree = RL_Rotation(tree);
				else
					tree = RR_Rotation(tree);
			}
		}
		else if (reNode->key > tree->key)
		{
			tree->Right = remove(tree->Right, reNode->key);
			if (height(tree->Left) - height(tree->Right) == 2)
			{
				AVLTreeNode<T>* tempNode = tree->Left;
				if (height(tempNode->Left) < height(tempNode->Right))
					tree = LR_Rotation(tree);
				else
					tree = LL_Rotation(tree);
			}
		}
		else// tree是对应要删除的结点
		{// tree的左右孩子都非空
			if ((tree->Left != NULL) && (tree->Right != NULL))
			{
				if (height(tree->Left) > height(tree->Right))
				{
					// 如果tree的左子树比右子树高；
					// 则(01)找出tree的左子树中的最大节点
					//   (02)将该最大节点的值赋值给tree。
					//   (03)删除该最大节点。
					// 这类似于用"tree的左子树中最大节点"做"tree"的替身；
					// 采用这种方式的好处是：删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的。
					T max = maxNode(tree->Left);
					tree->key = max;
					tree->Left = remove(tree->Left, max);
				}
				else
				{
					// 如果tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
					// 则(01)找出tree的右子树中的最小节点
					//   (02)将该最小节点的值赋值给tree。
					//   (03)删除该最小节点。
					// 这类似于用"tree的右子树中最小节点"做"tree"的替身；
					// 采用这种方式的好处是：删除"tree的右子树中最小节点"之后，AVL树仍然是平衡的。
					T min = miniNode(tree->Right);
					tree->key = min;
					tree->Right = remove(tree->Right, min);
				}
			}
			else
			{
				AVLTreeNode<T>* tmp = tree;
				tree = (tree->Left != NULL) ? tree->Left : tree->Right;
				delete tmp;
			}
		}
		return tree;
	}
}


//旋转
template<class T>
AVLTreeNode<T>* AVLTree<T>::LL_Rotation(AVLTreeNode<T>* key1)
{
	AVLTreeNode<T>* key_child;
	key_child = key1->Left;
	key1->Left = key_child->Right;
	key1->Right = key_child;

	key_child->height = max(height(key_child->Left), height(key_child->Right)) + 1;
	key1->height = max(height(key1->Left), key_child->height) + 1;

	return key1;
}
template<class T>
AVLTreeNode<T>* AVLTree<T>::RR_Rotation(AVLTreeNode<T>* key2)
{
	AVLTreeNode<T>* key_child;
	key_child = key2->Right;
	key2->Right = key_child->Left;
	key2->Left = key_child;

	key2->height = max(height(key2->Left), height(key2->Right)) + 1;
	key_child->height = max(height(key2->Right), key_child->height) + 1;

	return key2;
}
template<class T>
AVLTreeNode<T>* AVLTree<T>::LR_Rotation(AVLTreeNode<T>* key3)
{
	key3->Left = RR_Rotation(key3->Left);

	return LL_Rotation(key3);
}
template<class T>
AVLTreeNode<T>* AVLTree<T>::RL_Rotation(AVLTreeNode<T>* key4)
{
	key4->Right = LL_Rotation(key4->Right);

	return RR_Rotation(key4);
}