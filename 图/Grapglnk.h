/*
ͼ�ṹ����Զ�Ĺ�ϵ
�㣺���� �����еĽڵ� ���еĽڵ�
�ߣ���֮��Ĺ���
����Ķȣ�degree�����Ӷ���ıߵ�������Ϊ�ö���Ķ�


�ڽӾ��󣺻�������
		��һ��һά�������洢���ж���
		��һ����ά�������洢���еı�

�ڽӱ���������
		��һ��һά�������һ���������洢���е۹���
		ÿ�����㶼��һ�������ͷ�ڵ㣬�������������ͨ���ߵ���Ķ���


����ͼ��û�з���			undigraph
����ͼ���з���				digraph
���ͼ�������з������û��	mixed graph

ŷ����·�����ͼG�е�һ��·������ÿ����ǡ��һ��
���ܶ��ٻ�·����ָ�������ǰ��ָ�����յ㣬;�о������������ڵ���ֻ����һ�Ρ�


��ͼ������ֵ
*/

#include "Graph.h"

template<class T, class E>
struct Edge		//�߽��Ķ���
{
	int dest;	//�ߵ���һ����λ��
	E  cost;	//Ȩֵ
	Edge<T, E>* link;//��һ������ָ��
	Edge() {}		//���캯��
	Edge(int num, E weight) :dest(num), cost(weight), link(NULL) {} //���캯��
	bool operator != (Edge<T, E>& R)const {	//�б߲��ȷ�
		return (dest != R.dest) ? true : false;
	}
};

template<class T, class E >
struct Vertex {	//����Ķ���
	T data;		//��������
	Edge<T, E>* adj;	//�������ͷָ��
};

template <class T, class E>
class Graphlnk : public Graph<T, E>
{
public:
	Graphlnk(int sz = DefaultVertices);
	~Graphlnk();
	T getValue(int i)
	{
		return (i >= 0 && i < numVertices) ? NodeTable[i].data : 0;
	}
	E getWeight(int v1, int v2);
	int getFirstNeighbor(int v);
	int getNextNeighbor(int v, int w);
	bool insertVertex(const T& vertex);
	bool insertEdge(int v1, int v2, E cost);
	bool removeVertex(int v);
	bool removeEdge(int v1, int v2);
	void inputGraph();
	void outputGraph();
	int getVertexPos(T vertex) {
		for (int i = 0; i < numVertices; i++)
		{
			if (NodeTable[i].data == vertex)
				return i;
		}
		return -1; //�Ҳ����ͷ���-1
	}

private:
	Vertex<T, E>* NodeTable; //�����

};

template <class T, class E>
Graphlnk<T, E>::Graphlnk(int sz)  //���캯��
{
	maxVertices = sz;
	numVertices = 0;
	numEdges = 0;
	NodeTable = new Vertex<T, E>[maxVertices];
	if (NodeTable == NULL) { cerr << "�洢�����" << endl; exit(1); }
	for (int i = 0; i < maxVertices; i++)
	{
		NodeTable[i].adj = NULL;
	}
}

template<class T, class E>
Graphlnk<T, E>::~Graphlnk() //��������
{
	for (int i = 0; i < numVertices; i++)
	{
		Edge<T, E>* p = NodeTable[i].adj;
		while (p != NULL)
		{
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}

	}
	delete[]NodeTable;
}

template <class T, class E>
E Graphlnk<T, E>::getWeight(int v1, int v2) //���رߣ�v1��v2����Ȩ�أ��߲������򷵻�0
{
	if (v1 != -1 && v2 != -1)
	{
		Edge<T, E>* p = NodeTable[v1].adj;
		while (p != NULL && p->dest != v2)
			p = p->link;
		if (p != NULL)
			return p->cost;
	}
	return 0;
}

template<class T, class E>
int Graphlnk<T, E>::getFirstNeighbor(int v) //���v�ĵ�һ���ڽӶ��㣬�Ҳ����򷵻�-1
{
	if (v != -1)
	{
		Edge<T, E>* p = NodeTable[v].adj;
		if (p != NULL)
			return p->dest;
	}
	return -1;
}
template<class T, class E>
int Graphlnk<T, E>::getNextNeighbor(int v, int w) //���v���ڽӶ���w����һ���ڽӶ���
{
	if (v != -1)
	{
		Edge<T, E>* p = NodeTable[v].adj;
		while (p != NULL && p->dest != w)		//Ѱ���ڽӶ���w
			p = p->link;
		if (p != NULL && p->link != NULL)	//�ҵ�w�Ҵ�����һ���ڽӶ�����
			return p->link->dest;
	}
	return -1;
}


template<class T, class E>
bool Graphlnk<T, E>::insertVertex(const T& vertex)	//�����
{
	if (numVertices == maxVertices)	return false;	//ͼ����������ʧ��
	NodeTable[numVertices].data = vertex;
	numVertices++;
	return true;
}

template<class T, class E>
bool Graphlnk<T, E>::removeVertex(int v)			//ɾ����
{
	if (numVertices == 1 || v < 0 || v >= numVertices)		return false;
	Edge<T, E>* p, * s, * t;
	int  k;
	while (NodeTable[v].adj != NULL)		//ɾ���ö��㣬�Լ���֮�ڽӵĶ����еļ�¼
	{
		p = NodeTable[v].adj;
		k = p->dest;
		s = NodeTable[k].adj;	//���ҶԳƴ�ŵı߽ڵ�
		t = NULL;
		while (s != NULL && s->dest != v) //�ڶԳƵ���ڽӱ�������v��ɾ����
		{
			t = s;
			s = s->link;
		}
		if (s != NULL)
		{
			if (t == NULL) //��һ���ڽӶ������v
				NodeTable[k].adj = s->link;
			else
				t->link = s->link;
			delete s;
		}
		NodeTable[v].adj = p->link;
		delete p;
		numEdges--;
	}
	numVertices--;
	NodeTable[v].data = NodeTable[numVertices].data;
	p = NodeTable[v].adj = NodeTable[numVertices].adj;
	while (p != NULL)
	{
		s = NodeTable[p->dest].adj;
		while (s != NULL)
		{
			if (s->dest == numVertices)
			{
				s->dest = v;
				break;
			}
			else
				s = s->link;
		}
		p = p->link;
	}
	return true;
}

template<class T, class E>
bool Graphlnk<T, E>::insertEdge(int v1, int v2, E weight)	//����һ����,�����Ѵ��ڣ����������������false
{
	if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
	{
		Edge<T, E>* q, * p = NodeTable[v1].adj;
		//�ȼ��ñ��Ƿ��Ѿ�����
		while (p != NULL && p->dest != v2)
			p = p->link;
		if (p != NULL)//�ҵ��ñ�
		{
			cout << "�ñ��Ѿ����ڣ�����ʧ�ܣ�" << endl;
			return false;
		}
		p = new Edge<T, E>;
		q = new Edge<T, E>;
		p->dest = v2;
		p->cost = weight;
		p->link = NodeTable[v1].adj;
		NodeTable[v1].adj = p;	//���뵽�ڽӱ��ͷ
		q->dest = v1;
		q->cost = weight;
		q->link = NodeTable[v2].adj;
		NodeTable[v2].adj = q;
		numEdges++;
		return true;
	}
	return false;
}

template<class T, class E>
bool Graphlnk<T, E>::removeEdge(int v1, int v2)
{
	if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices)
	{
		Edge<T, E>* p = NodeTable[v1].adj, * q = NULL, * s = p;
		while (p != NULL && p->dest != v2) //���Ҹñ�
		{
			q = p;
			p = p->link;
		}
		if (p != NULL) //�ҵ��ñ�
		{
			if (p == s)//��һ���ڵ���ҵ�
				NodeTable[v1].adj = p->link;
			else
				q->link = p->link;
			delete p;
		}
		else return false; //�Ҳ�����
		p = NodeTable[v2].adj; q = NULL; s = p;
		while (p != NULL && p->dest != v1)
		{
			q = p;
			p = p->link;
		}
		if (p == s)
			NodeTable[v2].adj = p->link;
		else
			q->link = p->link;
		delete p;
		return true;
	}
	return false;
}

template<class T, class E>
void Graphlnk<T, E>::inputGraph()
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
void Graphlnk<T, E>::outputGraph()
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
