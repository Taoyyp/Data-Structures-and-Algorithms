#include <iostream>
#include<vector>
#include<fstream>
#include<cassert>
#include<string>
using namespace std;

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
		outfile << num[i] << ", ";
	}

}
//////////////排序结果输出///////////////////

int SeqSearch(vector<int> num, int len, int target)
{
	for (int i = 0; i < len; i++)
		if (num[i] == target)
			return i + 1;
}


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
	cout << "需要查找数字:";
	cin >> target;
	cout << "答案：" << SeqSearch(a, len, target) + 1;
}