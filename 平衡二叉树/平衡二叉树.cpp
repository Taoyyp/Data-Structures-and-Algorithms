#include<iostream>
#include "AVLTree.h"

using namespace std;

//平衡二叉树是一颗有序的二叉树
//左右子树高度差不超过1

int main()
{
	AVLTree<int> tree;
	tree.insert(9);
	tree.insert(8);
	tree.insert(7);
	//tree.insert(2);
	//tree.insert(6);
	tree.preOrder();
	cout << endl;
	//tree.postOrder()
	//cout << endl;
	tree.print();

}