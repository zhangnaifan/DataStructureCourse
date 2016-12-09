//如果编译失败，请在VS2015下编译
#include <iostream>
#include <stack>
#include <queue>
#include <deque>
using namespace std;
const int maxl = 100;//可容纳的最大节点数
int pre[maxl], mid[maxl];//数组pre，mid分别存储前根序列和中根序列的节点编号

//定义节点，由整型数据n和左右孩子指针组成
typedef struct node {
	int n;
	node* lchild=nullptr;
	node* rchild=nullptr;
}*btree;

//==========递归建立树=============
//要求输入指向整棵树的根节点的指针 root，以及前根序列，中根序列的起始和末尾数组下标 
void build(btree &root, int pleft, int pright, int mleft, int mright)
{
	root->n = pre[pleft];//根节点必然是前根序列的首元素

	//i 指示中序序列中的根节点，j 指示前序序列中当前root最靠右的左子孙
	int i = mleft, j = pleft;
	for (; mid[i] != pre[pleft]; ++i, ++j)
		;

	//如果存在左子树
	if (i > mleft)
	{
		root->lchild = new node;
		build(root->lchild, pleft + 1, j, mleft, i - 1);
	}

	//如果存在右子树
	if (i < mright)
	{
		root->rchild = new node;
		build(root->rchild, j+1, pright, i + 1, mright);
	}
}

//=========非递归建立树=============
//要求输入节点数，前根序列和中根序列
//返回指向这棵树根的指针
struct pairr {
	btree p;
	int mid;
};
btree build(int n, int pre[], int mid[])
{
	//定义root数组，包含所有节点的指针和在中根序列中的位置
	pairr root[maxl];
	for (int i = 0; i < n; ++i)
	{
		root[mid[i]].mid = i;
	}

	btree ret, parent;//ret返回创建的树的根，parent用来临时存放右子树的父节点指针
	stack<pairr> s;//s用来存放右子树的指针和在中根序列中的位置信息

	//从左往右扫描前序序列
	for (int i = 0; i < n; ++i)
	{
		//新建节点
		root[pre[i]].p = new node;
		root[pre[i]].p->n = pre[i];

		//如果栈空，则新节点入栈
		//在本程序中，该新节点只能是整棵树的根节点
		if (s.empty())
		{
			s.push(root[pre[i]]);
			ret = root[pre[i]].p;
			continue;
		}

		//如果栈顶在中根序列中的位置比新节点靠右，则栈顶是新节点的父亲，新节点是栈顶的左子树
		if (s.top().mid > root[pre[i]].mid)
		{
			s.top().p->lchild = root[pre[i]].p;
			s.push(root[pre[i]]);
			continue;
		}

		//如果栈顶在中根序列中的位置比新节点靠左，则往回找新节点的父亲
		while (!s.empty() && s.top().mid < root[pre[i]].mid)
		{
			parent = s.top().p;
			s.pop();
		}
		parent->rchild = root[pre[i]].p;
		s.push(root[pre[i]]);
	}
	return ret;
}

//前序递归遍历二叉树
void preorder(btree root)
{
	if (root != nullptr)
	{
		cout << root->n << " ";
		preorder(root->lchild);
		preorder(root->rchild);
	}
}

//中序递归遍历二叉树
void midorder(btree root)
{
	if (root != nullptr)
	{
		midorder(root->lchild);
		cout << root->n << " ";
		midorder(root->rchild);
	}
}

//后序递归遍历二叉树
void postorder(btree root)
{
	if (root != nullptr)
	{
		postorder(root->lchild);
		postorder(root->rchild);
		cout << root->n << " ";
	}
}

//非递归前序遍历二叉树
void non_recursive_pre(btree root)
{
	stack<btree> s;
	while (root != nullptr || !s.empty())//当节点不为空或者还有有兄弟未访问时
	{
		while (root != nullptr)
		{
			cout << root->n << " ";
			s.push(root->rchild);
			root = root->lchild;
		}
		root = s.top();
		s.pop();
	}
}

//非递归中序遍历二叉树
void non_recursive_mid(btree root)
{
	stack<btree> s;
	while (root != nullptr || !s.empty())
	{
		while (root != nullptr)
		{
			s.push(root);
			root = root->lchild;
		}
		root = s.top();
		cout << root->n << " ";
		s.pop();
		root = root->rchild;
	}
}

//非递归后序遍历二叉树
void non_recursive_post(btree root)
{
	stack<btree> s;
	stack<bool> n;
	while (root != nullptr || !s.empty())
	{
		while (root != nullptr)
		{
			s.push(root);
			n.push(0);
			root = root->lchild;
		}
		while (!n.empty() && n.top())
		{
			cout << s.top()->n << " ";
			n.pop();
			s.pop();
		}
		if (!s.empty())
		{
			n.top()=1;
			root = s.top()->rchild;
		}
	}
}

//层次遍历
void hierarchical(btree root)
{
	queue<btree> q;
	q.push(root);
	while (!q.empty())
	{
		if (q.front()->lchild != nullptr)
			q.push(q.front()->lchild);
		if (q.front()->rchild != nullptr)
			q.push(q.front()->rchild);
		cout << q.front()->n << " ";
		q.pop();
	}
}

//求root到dtree的路径
bool findpath(btree root, int dtree, deque<btree> &q)
{
	if (root == nullptr)
		return 0;
	q.push_back(root);
	if (root->n == dtree || findpath(root->lchild, dtree, q) || findpath(root->rchild, dtree, q))
		return 1;
	if (!q.empty())
		q.pop_back();
	return 0;
}

//求最近公共祖先
btree findanc(btree root, int t1, int t2)
{
	deque<btree> q1, q2;
	findpath(root, t1, q1);
	findpath(root, t2, q2);
	btree ret=nullptr;
	while (!q1.empty() && !q2.empty() && q1.front() == q2.front())
	{
		ret = q1.front();
		q1.pop_front();
		q2.pop_front();
	}
	return ret;
}

//获取前根，中根序列
int get()
{
	int n;
	do
	{
		cout << "请输入节点数：";
		cin >> n;
	} while (n > maxl);
	cout << "请输入前序序列（数字）：";
	for (int i = 0; i < n; ++i)
		cin >> pre[i];
	cout << "请输入中序序列（数字）：";
	for (int i = 0; i < n; ++i)
		cin >> mid[i];
	return n;
}

int main()
{
	int n = get();
	btree root = new node;
	build(root, 0, n - 1, 0, n - 1);
	cout << "非递归后序遍历：";
	non_recursive_post(root);
	cout << endl;
	cout << "层次遍历：";
	hierarchical(root);
	cout << endl;
	int t1, t2;
	cout << "请输入所要查询的节点：";
	cin >> t1 >> t2;
	cout << "最近祖先是：";
	cout << findanc(root, t1, t2)->n << endl;
	system("pause");
	return 0;
}