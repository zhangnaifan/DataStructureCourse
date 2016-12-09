#include <iostream>
using namespace std;
const int maxl = 101;

//使用同一个数组同时实现多个栈
struct node {
	int dat;
	int next;
};
typedef node* LIST;

node L[maxl];
LIST head=L;


//函数 ini 接收 n 作为参数，生成 n 个栈
void ini(LIST l, int n)
{
	if (n > maxl - 1)
	{
		cerr << "无法存储如此多的栈，请在程序中修改 maxl 的值，已获得更多的空间\n";
		return;
	}
	l[0].next = n + 1;//l[0]指向当前未被利用的位置
	for (int i = 1; i <= n; ++i)
		l[i].next = 0;//l[i]表示第i个栈的头节点，其next初始化为0，表示空指针
	for (int i = n + 1; i < maxl-1; ++i)
		l[i].next = i + 1;//将未被利用空间前后相邻地串起来
	l[maxl - 1].next = 0;//最后一个可以用空间应指向空指针，此处为0
}

//函数 push 接收 k，x 作为参数，表示将 x 压入第 k 个栈
void push(LIST l, int k, int x)
{
	if (l[0].next == 0)
	{
		cerr << "栈满！\n";
		return;
	}
	int free = l[l[0].next].next;//free用来保存下一个可用空间的位置
	l[l[0].next].dat = x;//对新结点的数据域进行赋值
	l[l[0].next].next = l[k].next;//将新的结点与原来的栈顶链起来
	l[k].next = l[0].next;//将新的结点链入对应栈的头节点之后
	l[0].next = free;//将l[0].next指向新的可用空间
}

//函数 pop 接收 k 将 k 的栈顶元素弹出，并返回该值
int pop(LIST l, int k)
{
	if (l[k].next == 0)
	{
		cerr << "当前栈无元素，无法弹出\n";
		return -1;
	}
	int ret = l[l[k].next].dat;//保存当前栈顶的值，以便后续返回
	int free = l[k].next;//保存当前栈顶的位置，以便后续链入可用空间
	l[k].next = l[l[k].next].next;//将头结点与新的栈顶链起来
	l[free].next = l[0].next;//将新的可用空间与原先第一个可用空间链起来
	l[0].next = free;//将l[0].next指向新的可用空间
	return ret;
}

//函数 empty 用来返回某个栈是否为空
bool empty(LIST l, int k)
{
	return !l[k].next;
}

//输入存放三栈的数组名，输出空闲位置
void getfree(LIST head)
{
	int i = head->next;
	if (i == 0)
	{
		cout << "当前栈无可用空间！\n";
		return;
	}
	cout << "当前可用空间有：";
	while (i != 0)
	{
		cout << i << " ";
		i = head[i].next;
	}
	cout << endl;
}

//输入栈序号，输出该栈所有元素
void getdat(LIST head, int k)
{
	int p = head[k].next;
	if (p == 0)
	{
		cout << "该栈中无元素！\n";
		return;
	}
	cout << "第" << k << "个栈中有元素：";
	while (p != 0)
	{
		cout << head[p].dat << " ";
		p = head[p].next;
	}
	cout << endl;
}

//测试：弹出元素，并输出当前可用空间位置
bool testpop(LIST head)
{
	cout << "请输入k，表示要弹出第k个栈栈顶元素；若输入0，表示退出程序\t";
	int k; cin >> k;
	if (k == 0)
		return false;
	pop(head, k);
	for (int i = 1; i <= 3; ++i)
		getdat(head, i);
	getfree(head);
	for (int i = 0; i < 5;++i)
		cout << endl;
	return true;
}

int main()
{
	ini(head, 3);

	cout << "请输入k，表示要初始化k个数，这k个数将以30，70为分界线分别存入三个栈中\t";
	int k; cin >> k;
	for (int i = 1; i <= k; ++i)
	{
		int tmp; cin >> tmp;
		if (tmp < 30)
			push(head, 1, tmp);
		else if (tmp>70)
			push(head, 3, tmp);
		else
			push(head, 2, tmp);
	}
	getfree(head);

	for (int i = 1; i <= 3; ++i)
		getdat(head, i);

	while (testpop(head))
		;

	system("pause");
	return 0;
}