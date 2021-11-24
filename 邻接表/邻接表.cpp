#include<iostream>
/*
图的表示方法
DG（有向图）或者DN（有向网）：邻接矩阵、邻接表（逆邻接表--为求入度）、十字链表
UDG（无向图）或者UDN（无向网）：邻接矩阵、邻接表、邻接多重表
*/
using namespace std;
int N, M, etop;
struct EDGE
{
	//边
	int u, v, len;
	EDGE* next;
	
}epool[100001];
struct NODE
{
	//点
	EDGE* first;//点指向边
}nodes[10001];

void addedge(int u, int v, int len)
{
	epool[etop].u = u;
	epool[etop].v = v;
	epool[etop].len = len;
	epool[etop].next = nodes[u].first;
	nodes[u].first = &epool[etop];
	etop++;
}


int main()
{
	int i;
	cin >> N >> M;
	for (i = 1; i <= M; i++)
	{
		cin >> u >> v >> len;
		addedge(u, v, len);	
		//无向图再加
		//addedge(v,u,len);
	}

	//遍历id好点的出边
	EDGE* e = nodes[id].first;
	while (e != NULL)
	{
		//e->v等于（*e).v
		//e->u

		e = e->next;
	}
}