#include<iostream>
#include<vector>
#include<fstream>
#include<cassert>
#include<string>

using namespace std;
int partion(vector<int>& aux, int low, int high);
///////////////////有序数组///////////////////

///////////////////二分查找/////////////////
int binarySearch(vector<int>& v, int target)//循环实现
{
	int low = 0;
	int high = v.size() - 1;
	int mid = (low + high) / 2;
	while (low <= high)
	{

		if (v[mid] == target)
		{
			return mid;
		}
		else if (target < v[mid])
		{
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
		mid = (low + high) / 2;
	}
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
	string file = "input.txt";
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
	cout << "答案：" << binarySearch(a, target) + 1;
}