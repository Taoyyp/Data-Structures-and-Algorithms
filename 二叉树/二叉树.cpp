#include <iostream>

using namespace std;

typedef struct treeNode
{
	char data;
	struct treeNode* LChild;
	struct treeNode* RChild;
}TREE,*LPTREE;
//LP指针
LPTREE createNode(char data)
{
	LPTREE newNode = (LPTREE)malloc(sizeof(TREE));
	newNode->data = data;
	newNode->LChild = NULL;
	newNode->RChild = NULL;
	return newNode;
}
//没有规律的树
void insertNode(LPTREE parentNode, LPTREE LChild, LPTREE RChild)
{
	parentNode->LChild = LChild;
	parentNode->RChild = RChild;
}

//打印当前节点的元素
void printCurNodeData(LPTREE curData)
{
	cout << curData->data;
}
//递归法
//前序：根左右
void preOrder(LPTREE root)
{
	if (root != NULL)
	{
		printCurNodeData(root);
		preOrder(root->LChild);
		preOrder(root->RChild);
	}
}
void preOrderByStack(LPTREE root)
{
	if (root == NULL)
		return;
	LPTREE stack[10];//存储每次打印节点的位置
	int stackTop = -1;//栈顶标记
	LPTREE pMove = root;
	while (stackTop != -1 || pMove)
	{
		//根左右
		while (pMove)
		{
			//把路径入栈+打印走过的节点
			cout << pMove->data;
			stack[++stackTop] = pMove;
			pMove = pMove->LChild;
		}
		//无路可走的处理
		if (stackTop != -1)
		{
			pMove = stack[stackTop];//获取栈顶元素
			stackTop--;
			pMove = pMove->RChild;
		}
	}
}
//中序：左根右
void midOrder(LPTREE root)
{
	if (root != NULL)
	{
		midOrder(root->LChild); 
		printCurNodeData(root);
		midOrder(root->RChild);
	}
}
void midOrderByStack(LPTREE root)
{
	if (root == NULL)
		return;
	//栈准备动作
	LPTREE stack[10];
	int stackTop = -1;
	//定义移动指针
	LPTREE pMove = root;
	while (stackTop != -1 || pMove)
	{
		//走到最左边，把走过的结点入栈
		while (pMove)
		{
			stack[++stackTop] = pMove;
			pMove = pMove->LChild;
		}
		//出栈
		if (stackTop != -1)
		{
			pMove = stack[stackTop--];
			cout << pMove->data;
			pMove = pMove->RChild;
		}
	}
}
//后续：左右根
void postOrder(LPTREE root)
{
	if (root != NULL)
	{
		postOrder(root->LChild);
		postOrder(root->RChild);
		printCurNodeData(root);
	}
}
void postOrderByStack(LPTREE root)
{
	if (root == NULL)
		return;
	LPTREE stack[10];
	int stackTop = -1;
	LPTREE pMove = root;
	LPTREE pPostVisit = NULL;

	//左右根
	while (pMove)
	{
		stack[++stackTop] = pMove;
		pMove = pMove->LChild;
	}
	while (stackTop != -1)
	{
		pMove = stack[stackTop--];
		//当前节点左右是否被访问
		if (pMove->RChild == NULL || pMove->RChild == pPostVisit)
		{
			//左右根
			//如果被访问就可以打印当前节点数据
			cout << pMove->data;
			pPostVisit = pMove;	//改变标记的位置
		}
		else
		{
			//右边没有被访问
			stack[++stackTop] = pMove;
			pMove = pMove->RChild;
			while (pMove)
			{
				stack[++stackTop] = pMove;
				pMove = pMove->LChild;
			}
		}
	}
}

int main()
{
	LPTREE A = createNode('A');
	LPTREE B = createNode('B');
	LPTREE C = createNode('C');
	LPTREE D = createNode('D');
	LPTREE E = createNode('E');
	LPTREE F = createNode('F');
	LPTREE G = createNode('G'); 
	insertNode(A, B, C);
	insertNode(B, D, NULL);
	insertNode(D, NULL, G);
	insertNode(C, E, F);
	preOrder(A);
	cout << endl;
	preOrderByStack(A);
	cout << endl;
	midOrder(A);
	cout << endl;
	midOrderByStack(A);
	cout << endl;
	postOrder(A);
	cout << endl;
	postOrderByStack(A);
}