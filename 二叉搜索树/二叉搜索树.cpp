#include <iostream>
#include "BSTree.h"
using namespace std;
/*
    二叉搜索树单调性：中序遍历序列必然单调非降
    充要条件

*/

static int arr[] = {1,2,3,4};
#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )


int main()
{
    int i, ilen;
    BSTree<int>* tree = new BSTree<int>();

    cout << "== 依次添加: ";
    ilen = TBL_SIZE(arr);
    for (i = 0; i < ilen; i++)
    {
        cout << arr[i] << " ";
        tree->insert(arr[i]);
    }

    cout << "\n== 前序遍历: ";
    tree->preOrder();

    cout << "\n== 中序遍历: ";
    tree->inOrder();

    cout << "\n== 后序遍历: ";
    tree->postOrder();
    cout << endl;

    cout << "== 最小值: " << tree->minimum() << endl;
    cout << "== 最大值: " << tree->maximum() << endl;
    cout << "== 树的详细信息: " << endl;
    tree->print();

    cout << "\n== 删除根节点: " << arr[3];
    tree->remove(arr[3]);

    cout << "\n== 中序遍历: ";
    tree->inOrder();
    cout << endl;

    // 销毁二叉树
    tree->destroy();

    return 0;
}