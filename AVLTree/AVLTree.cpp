#include<iostream>
#include "AVLTree.h"
using namespace std;

static int arr[] = { 3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9 };
int main()
{
	int i, len;
	AVLTreeNode<int>* tree = new AVLTreeNode<int>;
	AVLTree<int>* treemode = new AVLTree<int>();

	cout << "依次添加：";
	len = sizeof(arr) / sizeof(arr[0]);
	for (i = 0; i < len; ++i)
	{
		cout << arr[i] << " ";
		treemode->insert(tree, arr[i]);
	}
	cout << "\n前序遍历：";
	treemode->preorder(tree);
	cout << "\n中序遍历：";
	treemode->inorder(tree);
	cout << "\n后序遍历：";
	treemode->postorder(tree);

	cout << "\n高度: " << treemode->height(tree) << endl;
	cout << "最小值: " << treemode->miniNode(tree) << endl;
	cout << "最大值: " << treemode->maxNode(tree) << endl;
	cout << "树的详细信息: " << endl;
	treemode->print();

	i = 8;
	cout << "\n删除根节点：" << i;
	treemode->remove(tree, i);

	cout << "\n高度: " << treemode->height(tree) << endl;
	cout << "中序遍历：";
	treemode->inorder(tree);
	cout << "\n树的详细信息: " << endl;
	treemode->print();

	// 销毁二叉树
	//treemode->destroy(tree);
	return 0;
}