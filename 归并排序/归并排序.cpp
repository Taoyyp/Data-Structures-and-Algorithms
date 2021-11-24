#include <iostream>
#include <vector>
#include<cassert>
#include<string>
#include <fstream>

using namespace std;
////////////////二路归并////////////////
vector<int> merge(vector<int> a, vector<int> b) {
	vector<int> res;
	size_t ai = 0, bi = 0;
	while (ai < a.size() && bi < b.size()) {
		if (a[ai] <= b[bi])
			res.push_back(a[ai++]);
		else
			res.push_back(b[bi++]);
	}
	if (ai == a.size())
		res.insert(res.end(), b.begin() + bi, b.end());
	else if (bi == b.size())
		res.insert(res.end(), a.begin() + ai, a.end());
	return res;
}

vector<int> mergeSort(vector<int>& arr) {
	if (arr.size() < 2) return arr;
	const size_t mid = arr.size() / 2;
	vector<int> left(arr.begin(), arr.begin() + mid);
	vector<int> right(arr.begin() + mid, arr.end());
	return merge(mergeSort(left), mergeSort(right));
}


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


void main()
{
	vector<int> a;
	string file = "input.txt";
	cout << "输入数组已读取我完毕" << endl;
	a = readTxt(file);
	int len = a.size();
	//for (int i = 0; i < len; i++)
	//	cout << a[i] << endl;
	int lo = 0;
	int hi = len - 1;
	a = mergeSort(a);
	string locate = "output.txt";
	writeTxt(a, locate);
	cout << "归并排序已完成" << endl;

}

