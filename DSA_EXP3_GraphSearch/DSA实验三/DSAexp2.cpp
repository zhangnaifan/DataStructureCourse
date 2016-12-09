#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

struct edgeNode {
	int vertexNo;
	int weight;
	edgeNode* next = nullptr;
};

struct vertexNode {
	int info;
	int e=0;
	int inDegree=0;//入度
	edgeNode* firstEdge=nullptr;
	vector<int> tail;//存放有向图中指向本顶点的顶点编号
};

struct mGraph{
	vector<vertexNode> vertex;
	int v=0;
	int e=0;
};

void getVE(mGraph &gra)
{
	vector<vertexNode> &vertex = gra.vertex;
	cout << "请输入图的顶点数：";
	cin >> gra.v;
	vertex.resize(gra.v);
	for (int i = 0; i < gra.v; ++i)
	{
		vertexNode &node = vertex[i];
		cout << "请输入编号为" << i << "的顶点的整型信息：";
		cin >> node.info;
		cout << "请输入该顶点的边数：";
		cin >> node.e;
		gra.e += node.e;
		for (int j = 0; j < node.e; ++j)
		{
			edgeNode *tmp = new edgeNode;
			tmp->next = node.firstEdge;
			cout << "请输入第"<<j+1<<"个相邻的顶点编号：";
			cin >> tmp->vertexNo;
			++vertex[tmp->vertexNo].inDegree;
			//头插法
			vertex[tmp->vertexNo].tail.push_back(i);
			cout << "请输入边的权值：";
			cin >> tmp->weight;
			node.firstEdge = tmp;
		}
	}
}

int DSF(mGraph gra)
{
	vector<vertexNode> &vertex = gra.vertex;
	vector<bool> visited(gra.v,0);
	int visitedCount = 0;
	stack<int> s;
	int connectedNum = 0;
	while (visitedCount < gra.v)
	{
		++connectedNum;
		int start = 0;
		while (start<gra.v && visited[start])
			++start;
		visited[start]=1;
		s.push(start);
		cout << "DSP序列号为" << ++visitedCount << "的顶点"
			<< start << "的内容是" << vertex[start].info << endl;
		while (!s.empty())
		{
			edgeNode *i = vertex[s.top()].firstEdge;
			while (i!=nullptr && visited[i->vertexNo])
				i = i->next;
			if (!i)
			{
				s.pop();
				continue;
			}
			cout << "DSP序列号为" << ++visitedCount << "的顶点"
				<< i->vertexNo << "的内容是" << vertex[i->vertexNo].info << endl;
			visited[i->vertexNo] = 1;
			s.push(i->vertexNo);
		}
	}
	return connectedNum;
}

void topo(mGraph gra)
{
	vector<vertexNode> &vertex = gra.vertex;
	vector<int> indeg;
	for (int i = 0; i < gra.v; ++i)
		indeg.push_back(vertex[i].inDegree);
	int count = 0;
	vector<bool> visited(gra.v, 0);
	cout << "拓扑排序为：";
	while (count < gra.v)
	{
		int i = 0;
		while (i<gra.v &&  (visited[i] || indeg[i]))
			++i;
		visited[i] = 1;
		for (edgeNode* p = vertex[i].firstEdge; p; p = p->next)
			--indeg[p->vertexNo];
		++count;
		cout << i << " ";
	}
	cout << endl;
	cout << "逆拓扑排序为：";
	count = 0;
	vector<int> outdeg;
	visited.assign(gra.v, 0);
	for (int i = 0; i < gra.v; ++i)
		outdeg.push_back(vertex[i].e);
	while (count < gra.v)
	{
		int i = 0;
		while (i < gra.v && (visited[i] || outdeg[i]))
			++i;
		visited[i] = 1;
		for (unsigned int j = 0; j < vertex[i].tail.size(); ++j)
			--outdeg[vertex[i].tail[j]];
		++count;
		cout << i << " ";
	}
	cout << endl;
}


vector<bool> visited;
int DSF_red(mGraph, int);
void DSF_re(mGraph gra)
{
	visited.resize(gra.v);
	visited.assign(gra.v, 0);
	int visitedCount = 0;
	while (visitedCount < gra.v)
	{
		int start = 0;
		while (visited[start])
			++start;
		visitedCount += DSF_red(gra, start);
	}
}

int DSF_red(mGraph gra, int start)
{
	vector<vertexNode> &vertex = gra.vertex;
	edgeNode *i = vertex[start].firstEdge;
	visited[start] = 1;
	cout << "第" << start << "号节点的信息是：" << vertex[start].info << endl;
	int ret = 1;
	while (i)
	{
		if (!visited[i->vertexNo])
			ret += DSF_red(gra, i->vertexNo);
		i = i->next;
	}
	return ret;
}

void BSF(mGraph gra)
{
	vector<vertexNode> &vertex = gra.vertex;
	vector<bool> visited(gra.v, 0);
	vector<bool> inqueue(gra.v, 0);
	int visitedCount = 0;
	while (visitedCount < gra.v)
	{
		int start = 0;
		while (visited[start])
			++start;
		queue<int> q;
		q.push(start);
		inqueue[start] = 1;
		while (!q.empty())
		{
			cout << "BFS序号为" << ++visitedCount << "的第"
				<< q.front() << "号顶点的内容是" << vertex[q.front()].info << endl;
			visited[q.front()] = 1;
			edgeNode *i = vertex[q.front()].firstEdge;
			q.pop();
			while (i)
			{
				if (!visited[i->vertexNo] && !inqueue[i->vertexNo])
				{
					q.push(i->vertexNo);
					inqueue[i->vertexNo] = 1;
				}
				i = i->next;
			}
		}
	}
}

int main()
{
	mGraph gra;
	getVE(gra);
	cout << "该图的连通子图数目为" << DSF(gra) << endl<<endl;
	DSF_re(gra);
	cout << endl;
	BSF(gra);
	cout << endl;
	//topo(gra);
	system("pause");
	return 0;
}