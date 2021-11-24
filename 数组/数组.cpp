/*
	int array[arraysize];	//在stack上定义长度为arraysize的整型数组
	int *array = new int [arraysize];	在heap上定义长度为arraysize的整型数组使用完后需要释放内存
	delete[] array;


	旧的编译器不能再stack上定义一个长度不确定的数组，即只能定义固定长度的
	新的编译器没有限制，但是数组不确定，不能初始化数组。

	stack主要是指由操作系统自动管理的内存空间。局部变量存储在此
	stack总是后进先出（LIFO）

	heap是用来存储动态分配变量的空间。需要自己管理，否则会产生内存泄露（memory leak）

	二维数组
	在stack上：int array[M][N]
	传递给子函数 M可以省略，N必须存在，以便编译器确定移动内存的间距

	在heap上：in c++11: auto array = new int[m][n]		 int (*array)[n] = new int[m][n]; delete []array; 
	int **array = new int*[M];	//(int**)malloc(M* sizeof(int*));
	for(int i = 0; i < M; i++)
		array[i] = new int [N]	//(int*)malloc(N* sizeof(int));
	传递给子函数：
	void func(int **arr, int M, int N){}
	使用完后需要释放内存
	for(int i = 0; i < M; i++)
		delete[] array[i];
	delete[] array;

	Vector:
	成员函数：size() push_back(i) pop_back()
	####
	Hash table:基于key的查找
	map容器和unordered_map容器
	

	String：
	在C语言中，字符串指的是一个以'\0'结尾的char数组，关于字符串的函数通常需要传入一个字符型指针
	在C++中，String是一个类，并且可以通过调用类函数实现判断字符串长度，字串等等操作
*/
#include <iostream>

using namespace std;