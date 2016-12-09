//�������ʧ�ܣ�����VS2015�±���
#include <iostream>
#include <stack>
#include <queue>
#include <deque>
using namespace std;
const int maxl = 100;//�����ɵ����ڵ���
int pre[maxl], mid[maxl];//����pre��mid�ֱ�洢ǰ�����к��и����еĽڵ���

//����ڵ㣬����������n�����Һ���ָ�����
typedef struct node {
	int n;
	node* lchild=nullptr;
	node* rchild=nullptr;
}*btree;

//==========�ݹ齨����=============
//Ҫ������ָ���������ĸ��ڵ��ָ�� root���Լ�ǰ�����У��и����е���ʼ��ĩβ�����±� 
void build(btree &root, int pleft, int pright, int mleft, int mright)
{
	root->n = pre[pleft];//���ڵ��Ȼ��ǰ�����е���Ԫ��

	//i ָʾ���������еĸ��ڵ㣬j ָʾǰ�������е�ǰroot��ҵ�������
	int i = mleft, j = pleft;
	for (; mid[i] != pre[pleft]; ++i, ++j)
		;

	//�������������
	if (i > mleft)
	{
		root->lchild = new node;
		build(root->lchild, pleft + 1, j, mleft, i - 1);
	}

	//�������������
	if (i < mright)
	{
		root->rchild = new node;
		build(root->rchild, j+1, pright, i + 1, mright);
	}
}

//=========�ǵݹ齨����=============
//Ҫ������ڵ�����ǰ�����к��и�����
//����ָ�����������ָ��
struct pairr {
	btree p;
	int mid;
};
btree build(int n, int pre[], int mid[])
{
	//����root���飬�������нڵ��ָ������и������е�λ��
	pairr root[maxl];
	for (int i = 0; i < n; ++i)
	{
		root[mid[i]].mid = i;
	}

	btree ret, parent;//ret���ش��������ĸ���parent������ʱ����������ĸ��ڵ�ָ��
	stack<pairr> s;//s���������������ָ������и������е�λ����Ϣ

	//��������ɨ��ǰ������
	for (int i = 0; i < n; ++i)
	{
		//�½��ڵ�
		root[pre[i]].p = new node;
		root[pre[i]].p->n = pre[i];

		//���ջ�գ����½ڵ���ջ
		//�ڱ������У����½ڵ�ֻ�����������ĸ��ڵ�
		if (s.empty())
		{
			s.push(root[pre[i]]);
			ret = root[pre[i]].p;
			continue;
		}

		//���ջ�����и������е�λ�ñ��½ڵ㿿�ң���ջ�����½ڵ�ĸ��ף��½ڵ���ջ����������
		if (s.top().mid > root[pre[i]].mid)
		{
			s.top().p->lchild = root[pre[i]].p;
			s.push(root[pre[i]]);
			continue;
		}

		//���ջ�����и������е�λ�ñ��½ڵ㿿�����������½ڵ�ĸ���
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

//ǰ��ݹ����������
void preorder(btree root)
{
	if (root != nullptr)
	{
		cout << root->n << " ";
		preorder(root->lchild);
		preorder(root->rchild);
	}
}

//����ݹ����������
void midorder(btree root)
{
	if (root != nullptr)
	{
		midorder(root->lchild);
		cout << root->n << " ";
		midorder(root->rchild);
	}
}

//����ݹ����������
void postorder(btree root)
{
	if (root != nullptr)
	{
		postorder(root->lchild);
		postorder(root->rchild);
		cout << root->n << " ";
	}
}

//�ǵݹ�ǰ�����������
void non_recursive_pre(btree root)
{
	stack<btree> s;
	while (root != nullptr || !s.empty())//���ڵ㲻Ϊ�ջ��߻������ֵ�δ����ʱ
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

//�ǵݹ��������������
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

//�ǵݹ�������������
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

//��α���
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

//��root��dtree��·��
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

//�������������
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

//��ȡǰ�����и�����
int get()
{
	int n;
	do
	{
		cout << "������ڵ�����";
		cin >> n;
	} while (n > maxl);
	cout << "������ǰ�����У����֣���";
	for (int i = 0; i < n; ++i)
		cin >> pre[i];
	cout << "�������������У����֣���";
	for (int i = 0; i < n; ++i)
		cin >> mid[i];
	return n;
}

int main()
{
	int n = get();
	btree root = new node;
	build(root, 0, n - 1, 0, n - 1);
	cout << "�ǵݹ���������";
	non_recursive_post(root);
	cout << endl;
	cout << "��α�����";
	hierarchical(root);
	cout << endl;
	int t1, t2;
	cout << "��������Ҫ��ѯ�Ľڵ㣺";
	cin >> t1 >> t2;
	cout << "��������ǣ�";
	cout << findanc(root, t1, t2)->n << endl;
	system("pause");
	return 0;
}