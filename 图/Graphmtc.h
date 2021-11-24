#include "Graph.h"
#include<iostream>
using namespace std;

template<class T, class E>
class Graphmtx : Graph<T, E>
{

public:
	Graphmtx(int sz = DefaultVertices);							//����
	~Graphmtx()													//����
	{
		delete[]VerticesList;
		delete[]Edge;
	}
	T getValue(int i)											//ȡ����i��ֵ����i��������NULL
	{
		if (i >= 0 && i < numVertices) return VerticesList[i];
		else return NULL;
	}
	E getWeight(int v1, int v2)									//ȡ�ߣ�v1,v2����Ȩֵ����������0
	{
		if (v1 != -1 && v2 != -1)
			return Edge[v1][v2];
		else
			return 0;
	}
	int getFirstNeighbor(int v);
	int getNextNeighbor(int v, int w);
	bool insertVertex(const T& vertex);
	bool insertEdge(int v1, int v2, E cost);
	bool removeVertex(int v);
	bool removeEdge(int v1, int v2);
	void inputGraph();
	void outputGraph();
	int getVertexPos(T vertex)									//����������ͼ�е�λ��
	{
		for (int i = 0; i < numVertices; i++)
			if (VerticesList[i] == vertex)return i;
		return -1;												//�Ҳ�������-1
	}
private:
	T* VerticesList;											//�����
	E** Edge;													//�ڽӾ���

};

template<class T, class E>
Graphmtx<T, E>::Graphmtx(int sz)	//���캯��
{
	maxVertices = sz;
	numVertices = 0;
	numEdges = 0;
	int i, j;
	VerticesList = new T[maxVertices];
	Edge = new E * [maxVertices];
	for (i = 0; i < maxVertices; i++)
		Edge[i] = new E[maxVertices];
	for (i = 0; i < maxVertices; i++)
		for (j = 0; j < maxVertices; j++)
			Edge[i][j] = (i == j) ? 0 : maxWeight;
}

template<class T, class E>
int Graphmtx<T, E>::getFirstNeighbor(int v)//����v�ĵ�һ���ڽӶ����λ��
{
	if (v != -1)
	{
		for (int col = 0; col < maxVertices; col++)
			if (Edge[v][col] > 0 && Edge[v][col] < maxWeight)
				return col;
	}
	return -1;
}

template<class T, class E>
int Graphmtx<T, E>::getNextNeighbor(int v, int w)//����v���ڽӶ���w����һ���ڽӶ���
{
	if (v != -1 && w != -1)
	{
		for (int col = w + 1; col < maxVertices; col++)
		{
			if (Edge[v][col] > 0 && Edge[v][col] < maxWeight)
				return col;
		}
	}
	return -1;
}

template<class T, class E>
bool Graphmtx<T, E>::insertVertex(const T& vertex) //����һ������
{
	if (numVertices == maxVertices)return false; //���������������false
	VerticesList[numVertices++] = vertex;
	return true;
}

template<class T, class E>
bool Graphmtx<T, E>::insertEdge(int v1, int v2, E cost)//����һ����
{
	if (v1 > -1 && v1<numVertices && v2>-1 && v2 < numVertices) //�������
	{
		if (Edge[v1][v2] == maxWeight)
		{
			Edge[v1][v2] = Edge[v2][v1] = cost;
			numEdges++;
			return true;
		}
		else
		{
			cout << "�ñ��Ѵ��ڣ����ʧ��" << endl;
			return false;
		}
	}
	else return false;
}

template<class T, class E>
bool Graphmtx<T, E>::removeVertex(int v)				//ɾ��һ������
{
	if (v<0 || v>numVertices)	return false;			//v����ͼ��
	if (numVertices == 1)	return false;				//ֻʣһ�����㣬��ɾ��
	int i, j;
	VerticesList[v] = VerticesList[numVertices - 1];	//�������ɾ��
	for (i = 0; i < numVertices; i++)						//��������
		if (Edge[i][v] > 0 && Edge[i][v] < maxWeight)
			numEdges--;
	for (i = 0; i < numVertices; i++)
		Edge[i][v] = Edge[i][numVertices - 1];
	numVertices--;									//����������
	for (j = 0; j < numVertices; j--)
		Edge[v][j] = Edge[numVertices][j];
	return true;
}

template<class T, class E>
bool Graphmtx<T, E>::removeEdge(int v1, int v2)		//ɾ����
{
	if (v1 > -1 && v1<numVertices && v2>-1 && v2 < numVertices && Edge[v1][v2]>0 && Edge[v1][v2] < maxWeight)
	{
		Edge[v1][v2] = Edge[v1][v2] = maxWeight;
		numEdges--;
		return true;
	}
	else return false;
};

template<class T, class E>
void Graphmtx<T, E>::inputGraph()
{
	//ͨ��������������in����n�Ķ����e������ߵ���Ϣ�����ڽӾ����ʾ��ͼG���ڽӾ����ʼ�������ڹ��캯�����
	int i, j, k, m, n;
	T e1, e2;
	E weight;
	cout << "�����붥�����ͱ���(�ո����):" << endl;
	cin >> n >> m;	//�������n�ı���m
	cout << "���������붥��:" << endl;
	for (i = 0; i < n; i++)//���붥�㣬���������
	{
		cin >> e1;
		this->insertVertex(e1);
		//G.insertVertex(e1);
	}
	cout << "����������ߣ����� v1 v2 weight ��" << endl;
	i = 0;
	while (i < m)
	{
		cin >> e1 >> e2 >> weight;
		j = this->getVertexPos(e1);//�鶥���
		k = this->getVertexPos(e2);
		if (j == -1 || k == -1)
		{
			cout << "�����˵���Ϣ�����������룡" << endl;
		}
		else
		{
			if (this->insertEdge(j, k, weight))
				i++;
		}
	}

}
template<class T, class E>
void Graphmtx<T, E>::outputGraph()
{
	//���ͼ�����ж���ͱ���Ϣ
	int i, j, n, m;
	T e1, e2;
	E weight;
	n = this->NumberOfVertices();	 //����
	m = this->NumberOfEdges();		//����
	cout << "�������ı���Ϊ��";
	cout << n << "," << m << endl;		//��������ͱ���
	cout << "��������Ϊ��" << endl;
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			weight = this->getWeight(i, j);
			if (weight > 0 && weight < maxWeight)
			{
				e1 = this->getValue(i);
				e2 = this->getValue(j);
				cout << "(" << e1 << "," << e2 << "," << weight << ")" << endl;
			}
		}
	}
}
