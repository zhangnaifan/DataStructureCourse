//作者：张乃凡
//学号：1143310119
//班级：11403103
#include <iostream>
#include <vector>
using namespace std;

struct edge {
	int vnum;
	edge* next;
	edge() { next = NULL; }
};

//用图节点表示农夫当前所在的岸及该岸当前停留的物品状态
struct vnode {
	bool shore;//shore为0表示本岸，1表示对岸
	//以下0表示没有，1表示有
	bool wolf;
	bool sheep;
	bool vegetable;
	edge* firstEdge;
	vnode() { firstEdge = NULL; }
};

vector<vnode> gra;

//初始化：建立所有可能存在的状态（点），以及它们之间可能的转换（边）
//返回初始状态下的图节点位置（点下标）
int init()
{
	int ret = 0;

	//建立点
	for (int p = 0; p<=1;++p)
		for (int i = 0; i<=1; ++i)
			for (int j = 0; j<=1; ++j)
				for (int k = 0; k<=1; ++k)
					//当且进当如果羊和农夫在一起
					//或者羊不在，狼和羊都和农夫在一起时可能发生
					if (j || i && k)
					{
						vnode tmp;
						tmp.shore = p;
						tmp.wolf = i;
						tmp.sheep = j;
						tmp.vegetable = k;

						//返回初始状态，即本岸，狼，羊，蔬菜都和农夫在一起时
						//的位置
						if (!p && i && j && k)
							ret = gra.size();

						gra.push_back(tmp);
					}

	//建立边
	int total = gra.size();
	for (int i = 0; i < total; ++i)
		for (int j = 0; j < total;++j)

			//当且仅当农夫所在的岸发生变化
			//且最多带走一样东西时，这种变化可能发生
			if ((gra[i].shore != gra[j].shore) && 
				((gra[i].wolf == gra[j].wolf) + (gra[i].sheep == gra[j].sheep) + (gra[i].vegetable == gra[j].vegetable) <=1))
			{
				edge* tmp = new edge;
				tmp->vnum = j;
				tmp->next = gra[i].firstEdge;
				gra[i].firstEdge = tmp;
			}
	return ret;
}

//标记已经出现过的状态
//出现过的就不能再出现了
bool visited[32];

//输入起点的位置tail和终点的位置arrow
//输出农夫的动作
bool showhow(int tail, int arrow)
{
	if (gra[tail].shore)
		cout << "农夫从对岸走到本岸";
	else
		cout << "农夫从本岸走到对岸";
	if (gra[tail].wolf == gra[arrow].wolf)
		cout << "，并带走狼";
	if (gra[tail].sheep == gra[arrow].sheep)
		cout << "，并带走羊";
	if (gra[tail].vegetable == gra[arrow].vegetable)
		cout << "，并带走蔬菜";
	cout << endl;
	return true;
}

//递归实现：深度优先遍历直到找到所求路径，并输出该过程
//输入出发节点的位置start
//如果start是所求路径中的点，则返回true；否则，返回false
bool traverse(int start)
{
	if (gra[start].shore && gra[start].wolf && gra[start].sheep && gra[start].vegetable)
		return true;
	for (edge* e = gra[start].firstEdge; e; e = e->next)//访问每一个未访问过的点，并标记已访问
		if (!visited[e->vnum] && (visited[e->vnum] = true))
			if (traverse(e->vnum))//如果传来好消息（在路径上）
				return showhow(start, e->vnum);//输出该过程，并逐级往上传递好消息
	return false;//如果不在路径上，返回false
}

int main()
{
	traverse(init());
	system("pause");
	return 0;
}