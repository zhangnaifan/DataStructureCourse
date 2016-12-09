#include <iostream>
using namespace std;
const int maxl = 101;

//ʹ��ͬһ������ͬʱʵ�ֶ��ջ
struct node {
	int dat;
	int next;
};
typedef node* LIST;

node L[maxl];
LIST head=L;


//���� ini ���� n ��Ϊ���������� n ��ջ
void ini(LIST l, int n)
{
	if (n > maxl - 1)
	{
		cerr << "�޷��洢��˶��ջ�����ڳ������޸� maxl ��ֵ���ѻ�ø���Ŀռ�\n";
		return;
	}
	l[0].next = n + 1;//l[0]ָ��ǰδ�����õ�λ��
	for (int i = 1; i <= n; ++i)
		l[i].next = 0;//l[i]��ʾ��i��ջ��ͷ�ڵ㣬��next��ʼ��Ϊ0����ʾ��ָ��
	for (int i = n + 1; i < maxl-1; ++i)
		l[i].next = i + 1;//��δ�����ÿռ�ǰ�����ڵش�����
	l[maxl - 1].next = 0;//���һ�������ÿռ�Ӧָ���ָ�룬�˴�Ϊ0
}

//���� push ���� k��x ��Ϊ��������ʾ�� x ѹ��� k ��ջ
void push(LIST l, int k, int x)
{
	if (l[0].next == 0)
	{
		cerr << "ջ����\n";
		return;
	}
	int free = l[l[0].next].next;//free����������һ�����ÿռ��λ��
	l[l[0].next].dat = x;//���½�����������и�ֵ
	l[l[0].next].next = l[k].next;//���µĽ����ԭ����ջ��������
	l[k].next = l[0].next;//���µĽ�������Ӧջ��ͷ�ڵ�֮��
	l[0].next = free;//��l[0].nextָ���µĿ��ÿռ�
}

//���� pop ���� k �� k ��ջ��Ԫ�ص����������ظ�ֵ
int pop(LIST l, int k)
{
	if (l[k].next == 0)
	{
		cerr << "��ǰջ��Ԫ�أ��޷�����\n";
		return -1;
	}
	int ret = l[l[k].next].dat;//���浱ǰջ����ֵ���Ա��������
	int free = l[k].next;//���浱ǰջ����λ�ã��Ա����������ÿռ�
	l[k].next = l[l[k].next].next;//��ͷ������µ�ջ��������
	l[free].next = l[0].next;//���µĿ��ÿռ���ԭ�ȵ�һ�����ÿռ�������
	l[0].next = free;//��l[0].nextָ���µĿ��ÿռ�
	return ret;
}

//���� empty ��������ĳ��ջ�Ƿ�Ϊ��
bool empty(LIST l, int k)
{
	return !l[k].next;
}

//��������ջ�����������������λ��
void getfree(LIST head)
{
	int i = head->next;
	if (i == 0)
	{
		cout << "��ǰջ�޿��ÿռ䣡\n";
		return;
	}
	cout << "��ǰ���ÿռ��У�";
	while (i != 0)
	{
		cout << i << " ";
		i = head[i].next;
	}
	cout << endl;
}

//����ջ��ţ������ջ����Ԫ��
void getdat(LIST head, int k)
{
	int p = head[k].next;
	if (p == 0)
	{
		cout << "��ջ����Ԫ�أ�\n";
		return;
	}
	cout << "��" << k << "��ջ����Ԫ�أ�";
	while (p != 0)
	{
		cout << head[p].dat << " ";
		p = head[p].next;
	}
	cout << endl;
}

//���ԣ�����Ԫ�أ��������ǰ���ÿռ�λ��
bool testpop(LIST head)
{
	cout << "������k����ʾҪ������k��ջջ��Ԫ�أ�������0����ʾ�˳�����\t";
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

	cout << "������k����ʾҪ��ʼ��k��������k��������30��70Ϊ�ֽ��߷ֱ��������ջ��\t";
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