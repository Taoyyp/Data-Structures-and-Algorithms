#pragma once
#include<iostream>
using namespace std;


#define INF 100000 //��ʾ������
const int DefaultVertices = 30;

template<class T, class E>
class Graph
{
public:
	static const E maxWeight = INF;
	Graph(int size = DefaultVertices) {};
	~Graph() {};
	bool GraphEmpty()const //���Ϊ��
	{
		if (numEdges == 0)return true;
		else return false;
	}
	bool GraphFull()const //���Ϊ��
	{
		if (numVertices == maxVertices || numEdges == maxVertices * (maxVertices - 1) / 2)
			return true;
		else
			return false;
	}
	int NumberOfVertices() { return numVertices; }	//���ص�ǰ������
	int NumberOfEdges() { return numEdges; }		//���ص�ǰ����
	virtual T getValue(int i) = 0;					//ȡ����i��ֵ��i��������0
	virtual E getWeight(int v1, int v2) = 0;			//ȡ�ߣ�v1��v2����Ȩֵ
	virtual int getFirstNeighbor(int v) = 0;		//ȡ����v�ĵ�һ���ڽӶ���
	virtual int getNextNeighbor(int v, int w) = 0;	//ȡ�ڽӶ���w����һ���ڽӶ���
	virtual bool insertVertex(const T& vertex) = 0;	//����һ������vertex
	virtual bool insertEdge(int v1, int v2, E cost) = 0;//����ߣ�v1,v2��,Ȩֵcost
	virtual bool removeVertex(int v) = 0;			//ɾ������v��������֮�����ı�
	virtual bool removeEdge(int v1, int v2) = 0;		//ɾ���ߣ�v1,v2��
	virtual int getVertexPos(T vertex) = 0;

protected:
	int maxVertices;
	int numEdges;
	int numVertices;

};