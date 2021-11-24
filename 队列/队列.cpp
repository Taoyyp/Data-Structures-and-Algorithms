#include <iostream>

using namespace std;


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

class Queue {
	int head;
	int tail;
	int length;
	Point q[100];
public:
	Queue();
	bool push(int data);
	bool pop();
	int front();
	int back();
	bool emp();
	int size();
};

Queue::Queue() {
	head = 0;
	tail = 0;
	length = 0;
}

//bool push(int data) {
//	if (length == 100)
//		return 0;
//	q[tail].setdata(data);
//	tail = (tail + 1) % 100;
//}