#include<iostream>
#include<stack>
#include<queue>

using namespace std;
int N, M, etop;
struct EDGE
{
	int u, v;
	EDGE* next;
}epool[100001];
struct NODE
{
	EDGE* first;
}nodes[10001];

void addedge(int u, int v)
{
	epool[etop].u = u;
	epool[etop].v = v;
	epool[etop].next = nodes[u].first;
	nodes[u].first = &epool[etop];
	etop++;
}
//递归DFS
bool visited[10001];
void DFS(int id)
{
	visited[id] = true;
	cout << id << ' ';
	EDGE* e = nodes[id].first;
	while (e != NULL)
	{
		if (!visited[e->v])
			DFS(e->v);
		e = e->next;
	}
}

//一般搜索
bool discovered[10001];
stack<int> F;	//DFS
//queue<int> F;	//BFS
void search()
{
	F.push(1);
	discovered[1] = true;
	while (!F.empty())
	{
		int id = F.top();
		//int id=F.front();
		F.pop();
		cout << id << ' ';
		EDGE* e = nodes[id].first;
		while (e != NULL)
		{
			if (!discovered[e->v])
			{
				F.push(e->v);
				discovered[e->v] = true;
			}
			e = e->next;
		}
	}
}

int main()
{
	int i, u, v;
	cin >> N >> M;
	for (i = 1; i <= M; i++)
	{
		cin >> u >> v;
		addedge(u, v);
		addedge(v, u);
	}

	DFS(1);
	cout << endl;
	search();
	cout << endl;
}