#include <iostream>
#include <vector>
#include<cassert>
#include<string>
#include <fstream>
using namespace std;


void seletionsort(vector<int>& num)
{
	int len = num.size();

	for (int i = 0; i < len - 1; i++)
	{
		int min = i;
		int temp = num[i];
		for (int j = i + 1; j < len; j++)
		{
			if (num[j] < temp)
			{
				temp = num[j];
				min = j;
			}
		}
		if (temp < num[i])
		{
			num[min] = num[i];
			num[i] = temp;
		}
	}
};





////////////////文件读取////////////////
vector<int> readTxt(string file)
{
	ifstream infile;
	infile.open(file.data());   //将文件流对象与文件连接起来 
	assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 
	int data;
	vector<int> num;
	while (!infile.eof()) {
		infile >> data;
		num.push_back(data);
	}
	num.pop_back();
	infile.close();             //关闭文件输入流 
	return num;
};
//////////////////文件读取////////////////
/////////////////排序结果输出/////////////
void writeTxt(vector<int> num, string location)
{
	ofstream outfile(location);
	int len = num.size();
	for (int i = 0; i < len; i++) {
		outfile << num[i] << endl;
	}

}
//////////////排序结果输出///////////////////


void main()
{
	int inter;
	vector<int> a;
	int target;
	string file = "input.txt";
	cout << "输入数组已读取我完毕" << endl;
	a = readTxt(file);
	int len = a.size();
	//for (int i = 0; i < len; i++)
	//	cout << a[i] << endl;
	seletionsort(a);
	string locate = "output.txt";
	writeTxt(a, locate);
	cout << "选择排序已完成" << endl;

}