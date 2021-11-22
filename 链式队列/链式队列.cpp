#include <iostream>

using namespace std;

struct Node
{
	int data;
	struct Node* next;
};

struct  Node* createNode(int data)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
};

struct Queue
{
	struct Node* frontNode;
	struct Node* tailNode;
	int size;
};

//创建队列
struct Queue* createQueue()
{
	struct Queue* myQueue = (struct Queue*)malloc(sizeof(struct Queue));
	myQueue->frontNode = myQueue->tailNode = NULL;
	myQueue->size = 0;
	return myQueue;
}

void push(struct Queue* myQueue, int data)
{
	struct Node* newNode = createNode(data);
	if (myQueue->size == 0)
	{
		myQueue->frontNode = myQueue->tailNode = newNode;
	}
	else
	{
		myQueue->tailNode->next = newNode;
		myQueue->tailNode = newNode;
	}
	myQueue->size++;
}

void pop(struct Queue* myQueue)
{
	if (myQueue->size == 0)
	{
		cout << "队为空" << endl;
		system("pause");
		return;
	}
	else
	{
		struct Node* nextNode = myQueue->frontNode->next;
		free(myQueue->frontNode);
		myQueue->frontNode = nextNode;
		myQueue->size--;
	}
}

int front(struct Queue* myQueue)
{
	if (myQueue->size == 0)
	{
		cout << "队空" << endl;
		system("pause");
		return myQueue->size;
	}
	return myQueue->frontNode->data;
}

int empty(struct Queue* myQueue)
{
	if (myQueue->size == 0)
	{
		return 0;
	}
	else {
		return 1;
	}
}
int main()
{
	struct Queue* myQueue = createQueue();
	push(myQueue, 1);
	push(myQueue, 2);
	push(myQueue, 3);
	while (empty(myQueue))
	{
		cout << front(myQueue)<<endl;
		pop(myQueue);
	}
	system("pause");
	return 0;
}