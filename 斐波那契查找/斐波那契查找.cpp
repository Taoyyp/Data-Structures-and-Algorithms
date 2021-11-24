#include <iostream>
#include<vector>
#include<fstream>
#include<cassert>
#include<string>
using namespace std;

int fib(int n) {

	vector<int> res(n);
	int a = 0;
	int b = 1;
	while (0 < n--)
	{
		a = a + b;
		b = a - b;
	}
	return a;
};
int fibonacciSearch(vector<int>data, int maxSize, int targetValue) {
	// 1：构建斐波那契数列
	vector<int>fiboArray(maxSize, 0);
	int oriLength = data.size();
	for (int i = 0; i < maxSize - 1; i++) {
		fiboArray[i + 1] = fib(i);
		// printf("%d ", fiboArray[i]);
	}

	// 2：计算数据长度对应斐波那契数列元素
	int index = 0;
	while (fiboArray[index] < data.size())
	{
		index++;
	}
	// printf("%d %d \n", index, fiboArray[index]);

	// 3：对数据进行填充
	for (int i = data.size(); i < fiboArray[index]; i++) {
		data.push_back(data[data.size() - 1]);
		// printf("%d ", data[i]);
	}

	// 4：对区间不断分割
	int left = 0;
	int right = data[data.size() - 1];
	while (left <= right && index >= 0)
	{
		// 计算中间位置
		int mid = left + fiboArray[index - 1] - 1;

		// 对三种情况分别处理
		// 目标值搜索成功
		if (data[mid] == targetValue) {
			// 如果mid比原始数据长度大，则说明mid位置为填充的元素
			if (mid >= oriLength) { return oriLength - 1; }
			else { return mid; }
		}
		// 目标值在中间值左边，更新右边界
		else if (data[mid] > targetValue) {
			right = mid - 1;
			index = index - 1;
		}
		// 目标值在中间值右边，更新左边界
		else {
			left = mid + 1;
			index = index - 2;
		}
	}
	// 搜索失败
	return -1;
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
		outfile << num[i] << ", ";
	}

}
//////////////排序结果输出///////////////////
/////////////////快排//////////////////////
int partion(vector<int>& aux, int low, int high) {
	int mid = aux[low]; ///切分
	while (low < high) {
		while (low < high && aux[high] >= mid)
			high--;
		aux[low] = aux[high];
		while (low < high && aux[low] <= mid)
			low++;
		aux[high] = aux[low];
	}
	aux[low] = mid;
	return low;
};
void quicksort(vector<int>& aux, int low, int high) {
	if (low < high) {
		int mid = partion(aux, low, high);
		quicksort(aux, low, mid - 1);
		quicksort(aux, mid + 1, high);
	}
};
////////////////////快排/////////////////


void main()
{
	int inter;
	vector<int> a;
	int target;
	string file = "input_fib.txt";
	cout << "输入数组已读取我完毕" << endl;
	a = readTxt(file);
	int len = a.size();
	//for (int i = 0; i < len; i++)
	//	cout << a[i] << endl;
	quicksort(a, 0, len - 1);
	string locate = "output.txt";
	writeTxt(a, locate);
	cout << "需要查找数字:";
	cin >> target;
	cout << "答案：" << fibonacciSearch(a, len, target) + 1;
}