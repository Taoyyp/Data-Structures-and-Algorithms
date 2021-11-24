#include <iostream>


using namespace std;
/*
栈		FILO	先进后出	栈顶标记
 入栈 出栈 获取栈顶元素 判断栈是否为NULL
队列		FIFO	先进先出	队头：fornt	队尾：tail	大小：size
 入队 出队 获取队头元素 判断对是否为NULL


数组栈
数组队列
链式栈
链式队列
	单向链表
	双向链表
	双向循环链表
*/


class Point {
	int data;
public:
	int getdata();
	void setdata(int data);
};

int Point::getdata() {
	return this->data;
}

void Point::setdata(int data) {
	this->data = data;
}

class Stack {
	Point* top;
	Point base[100];
	int length;
public:
	Stack();
	int _top();
	bool push(int data);
	bool pop();
	bool emp();
	int _length();
};

Stack::Stack() {
	top = base;
	length = 0;
}

int Stack::_top() {
	if (length == 0)
		return 0;
	return(top - 1)->getdata();
}

bool Stack::push(int data) {
	if (length == 100)
		return 0;
	top->setdata(data);
	top++; length++;
	return 1;
}

bool Stack::pop() {
	if (top == base)
		return 0;
	top--; length--;
	return 1;
}


bool Stack::emp() {
	if (top == base)
		return 1;
	else
		return 0;
}

int Stack::_length() {
	return length;
}

int main() {
	Stack s = Stack();
	s.push(1);
	cout << s._top() << endl;
	s.push(5);
	cout << s._top() << endl;
	s.push(345);
	cout << s._top() << endl;
	s.push(456);
	cout << s._top() << endl;
	for (int i = 0; i < 4; i++) {
		cout << s._top() << endl;
		s.pop();
	}
}