﻿#include <iostream>
#include <stack>
#include <vector>

using namespace std;

void Shuffling(int length, vector<vector<int>>& outputs);
void Internal_ShufflingRecursion(int length,
    int index,
    stack<int>& inStack,
    vector<int>& outList,
    vector<vector<int>>& outputs);


// 计算所有出栈序列（下标从0计算）
// params:
//      length:     入栈元素个数
//      outputs:    输出所有出栈序列结果（下标）
void Shuffling(int length, vector<vector<int>>& outputs)
{
    if (length <= 0)
    {
        return;
    }

    stack<int> inStack; // 入栈序列
    vector<int> outList; // 出栈序列

    Internal_ShufflingRecursion(length, 0, inStack, outList, outputs); // 递归求解
}

// 内部计算递归
// params:
//      length:     入栈元素个数
//      index:      当前元素下标
//      inStack:    当前入栈序列
//      outList:    当前出栈序列
//      outputs:    输出的所有出栈序列结果（下标）
void Internal_ShufflingRecursion(int length,
    int index,
    stack<int>& inStack,
    vector<int>& outList,
    vector<vector<int>>& outputs)
{
    // 如果全部元素都出栈
    if (outList.size() == length)
    {
        outputs.push_back(outList); // 将其加入到结果`outputs`中
        return;
    }

    // 如果当前元素下标小于总元素个数，开始入栈递归
    if (index < length)
    {
        inStack.push(index); // 入栈当前下标
        Internal_ShufflingRecursion(length, index + 1, inStack, outList, outputs);
        inStack.pop(); // 出栈栈顶元素
    }

    // 如果栈元素个数大于0，开始出栈递归
    if (inStack.size() > 0)
    {
        int top = inStack.top(); // 获取栈顶元素下标
        inStack.pop(); // 出栈栈顶元素
        outList.push_back(top); // 将出栈元素加入到出栈序列中

        // 此处递归，将判断元素出栈后，是否还需要入栈出栈操作（后面是否还有元素没有入过栈）
        Internal_ShufflingRecursion(length, index, inStack, outList, outputs);

        inStack.push(top); // 重新入栈原栈顶元素
        outList.pop_back(); // 将原栈顶元素移除
    }
}



int main()
{
    int length = -1;

    while (true)
    {
        cout << "栈的混洗，请输入栈长度：";
        while (!(cin >> length) || length < 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "输入不合法，请重新输入栈长度：";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vector<vector<int>> outputs; // 定义所有出栈结果
        Shuffling(length, outputs); // 计算出栈序列

        // 打印所有出栈顺序
        for (int i = 0; i < outputs.size(); i++)
        {
            cout << i << ": ";
            for (int j = 0; j < outputs[i].size(); j++)
            {
                // 出栈结果是下标从0开始，元素是从1开始
                // 如果原始数据不是1-n
                // 这里替换成`原入栈序列[outputs[i][j]]`
                cout << (outputs[i][j] + 1) << " ";
            }
            cout << endl;
        }
        cout << "一共有" << outputs.size() << "种出栈序列。" << endl;
        cout << endl;
    }

    system("pause");
    return 0;
}
