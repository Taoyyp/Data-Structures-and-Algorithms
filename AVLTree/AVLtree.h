#pragma once
#include<iomanip>
#include<iostream>
using namespace std;
//���Ľڵ�
template<class T>
class AVLTreeNode
{
public:
	AVLTreeNode(T value, AVLTreeNode* l, AVLTreeNode* r) :
		key(value), Left(l), Right(r) {}
	T key;	//��ֵ
	int height;	//�߶�
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
//������
template<class T>
class AVLTree
{
private:
	AVLTreeNode<T>* root;
public:
	//�ⲿ�ӿ�
	AVLTree();
	~AVLTree();

	//��ȡ���ĸ߶�
	int height(AVLTreeNode<T>* tree);
	//�Ƚ�����ֵ�Ĵ�С
	int max(int a, int b);

	//ǰ�����
	void preorder(AVLTreeNode<T>* tree);
	//�������
	void inorder(AVLTreeNode<T>* tree);
	//�������
	void postorder(AVLTreeNode<T>* tree);

	//����AVL���е�ֵ�Ľڵ�
	AVLTreeNode<T>* search(AVLTreeNode<T>* tree, T key);
	//���ֵ��Сֵ
	T miniNode(AVLTreeNode<T>* tree);
	T maxNode(AVLTreeNode<T>* tree);

	//����ڵ�
	AVLTreeNode<T>* insert(AVLTreeNode<T>*& tree, T key);
	//ɾ���ڵ�
	AVLTreeNode<T>* remove(AVLTreeNode<T>*& tree, T reNode);

	//������
	void destroy(AVLTreeNode<T>*& tree);
	//��ӡ��
	void print();


	//LL�������Ӧ�������������
	AVLTreeNode<T>* LL_Rotation(AVLTreeNode<T>* key1);
	//RR�����Ҷ�Ӧ��������ҵ�����
	AVLTreeNode<T>* RR_Rotation(AVLTreeNode<T>* key2);
	//LR������			����˫����
	AVLTreeNode<T>* LR_Rotation(AVLTreeNode<T>* key3);
	//RL������			����˫����
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


//ǰ�����
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
//����
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
//����
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


//����
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
//��Сֵ���ֵ
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

//����
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
//��ӡ
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


//����
template<class T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>*& tree, T key)
{
	if (tree == NULL)
	{
		//�½����
		tree = new AVLTreeNode<T>(key, NULL, NULL);
		if (tree == NULL)
		{
			cout << "������ʧ�ܣ�" << endl;
			return NULL;
		}
	}
	else if (key < tree->key)
	{
		tree->Left = insert(tree->Left, key);
		// ���������AVL��ʧȥƽ�⣬�������Ӧ�ĵ���
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
		// ���������AVL��ʧȥƽ�⣬�������Ӧ�ĵ���
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
		//��Ϊ�ջ�û��Ҫɾ���Ľڵ�
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
		else// tree�Ƕ�ӦҪɾ���Ľ��
		{// tree�����Һ��Ӷ��ǿ�
			if ((tree->Left != NULL) && (tree->Right != NULL))
			{
				if (height(tree->Left) > height(tree->Right))
				{
					// ���tree�����������������ߣ�
					// ��(01)�ҳ�tree���������е����ڵ�
					//   (02)�������ڵ��ֵ��ֵ��tree��
					//   (03)ɾ�������ڵ㡣
					// ����������"tree�������������ڵ�"��"tree"������
					// �������ַ�ʽ�ĺô��ǣ�ɾ��"tree�������������ڵ�"֮��AVL����Ȼ��ƽ��ġ�
					T max = maxNode(tree->Left);
					tree->key = max;
					tree->Left = remove(tree->Left, max);
				}
				else
				{
					// ���tree��������������������(��������ȣ�������������������1)
					// ��(01)�ҳ�tree���������е���С�ڵ�
					//   (02)������С�ڵ��ֵ��ֵ��tree��
					//   (03)ɾ������С�ڵ㡣
					// ����������"tree������������С�ڵ�"��"tree"������
					// �������ַ�ʽ�ĺô��ǣ�ɾ��"tree������������С�ڵ�"֮��AVL����Ȼ��ƽ��ġ�
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


//��ת
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