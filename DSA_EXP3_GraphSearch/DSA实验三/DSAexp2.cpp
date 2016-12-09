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
	int inDegree=0;//���
	edgeNode* firstEdge=nullptr;
	vector<int> tail;//�������ͼ��ָ�򱾶���Ķ�����
};

struct mGraph{
	vector<vertexNode> vertex;
	int v=0;
	int e=0;
};

void getVE(mGraph &gra)
{
	vector<vertexNode> &vertex = gra.vertex;
	cout << "������ͼ�Ķ�������";
	cin >> gra.v;
	vertex.resize(gra.v);
	for (int i = 0; i < gra.v; ++i)
	{
		vertexNode &node = vertex[i];
		cout << "��������Ϊ" << i << "�Ķ����������Ϣ��";
		cin >> node.info;
		cout << "������ö���ı�����";
		cin >> node.e;
		gra.e += node.e;
		for (int j = 0; j < node.e; ++j)
		{
			edgeNode *tmp = new edgeNode;
			tmp->next = node.firstEdge;
			cout << "�������"<<j+1<<"�����ڵĶ����ţ�";
			cin >> tmp->vertexNo;
			++vertex[tmp->vertexNo].inDegree;
			//ͷ�巨
			vertex[tmp->vertexNo].tail.push_back(i);
			cout << "������ߵ�Ȩֵ��";
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
		cout << "DSP���к�Ϊ" << ++visitedCount << "�Ķ���"
			<< start << "��������" << vertex[start].info << endl;
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
			cout << "DSP���к�Ϊ" << ++visitedCount << "�Ķ���"
				<< i->vertexNo << "��������" << vertex[i->vertexNo].info << endl;
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
	cout << "��������Ϊ��";
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
	cout << "����������Ϊ��";
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
	cout << "��" << start << "�Žڵ����Ϣ�ǣ�" << vertex[start].info << endl;
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
			cout << "BFS���Ϊ" << ++visitedCount << "�ĵ�"
				<< q.front() << "�Ŷ����������" << vertex[q.front()].info << endl;
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
	cout << "��ͼ����ͨ��ͼ��ĿΪ" << DSF(gra) << endl<<endl;
	DSF_re(gra);
	cout << endl;
	BSF(gra);
	cout << endl;
	//topo(gra);
	system("pause");
	return 0;
}