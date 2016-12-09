#include <iostream>
#include <string>
#include <fstream>
using namespace std;
typedef struct node{
	string sort;
	string brand;
	double price;
	int amount=0;
	node* next=nullptr;
}*list;
//��ʼ������
list makenull()
{
	list ret = new node;
	return ret;
}
//ִ�а��۸�������
void insrt(list head, node nd)
{
	if (head->next == nullptr)
	{
		head->next = new node;
		*(head->next) = nd;
		return;
	}
	list p = head;
	while (p->next != nullptr && p->next->price < nd.price)
		p = p->next;
	if (p->next == nullptr || p->next->price > nd.price + 1e-3)
	{
		list tmp = p->next;
		p->next = new node;
		*(p->next) = nd;
		p->next->next = tmp;
	}
	else
	{
		p->next->price += nd.amount;
	}
}
//ִ��ɾ��/���ٲ���
void del(list head, node nd)
{
	if (head == nullptr || head->next == nullptr)
		return;
	list p = head;
	while (p->next != nullptr && p->next->price < nd.price)
		p = p->next;
	if (p->next == nullptr || p->next->price > nd.price + 1e-3)
	{
		cout << "�Ҳ�������Ʒ��\n";
		return;
	}
	if (p->next->amount < nd.amount)
	{
		cout << "û���㹻��棡\n";
		return;
	}
	if (p->next->amount == nd.amount)
	{
		list tmp = p->next;
		p->next = p->next->next;
		delete tmp;
		return;
	}
	p->next->amount -= nd.amount;
}
//�����й����ƣ�Ʒ�ƣ��۸����Ϣ
void updat(list head, node ond, node nnd)
{
	if (head == nullptr || head->next == nullptr)
		return;
	list p = head;
	while (p->next != nullptr && (p->next->sort != ond.sort || p->next->brand != ond.brand))
		p = p->next;
	if (p->next == nullptr)
	{
		cout << "δ�ҵ�ԭ��Ʒ��\n";
		return;
	}
	if (ond.price - nnd.price <1e-3 && ond.price - nnd.price >-1e-3)
	{
		p->next->brand = nnd.brand;
		p->next->sort = nnd.sort;
		p->next->amount = nnd.amount;
		return;
	}
	list tmp = p->next;
	p->next = p->next->next;
	delete tmp;
	insrt(head, nnd);
}
//����
void indat(list head)
{
	cout << "���������������Ʒ�����ƣ�Ʒ�ƣ��۸������\n";
	node nd;
	cin >> nd.sort >> nd.brand >> nd.price >> nd.amount;
	insrt(head, nd);
}
//���
void deldat(list head)
{
	if (head == nullptr || head->next == nullptr)
	{
		cout << "���������ڣ�\n";
		return;
	}
	cout << "����������Ҫ�����Ʒ�����ƣ�Ʒ�ƣ��۸������\n";
	node nd;
	cin >> nd.sort >> nd.brand >> nd.price >> nd.amount;
	del(head, nd);
}
//�����û�����
void refresh(list head)
{
	if (head == nullptr || head->next == nullptr)
	{
		cout << "���������ڣ�\n";
		return;
	}
	cout << "����������ԭ��Ʒ�����ƣ�Ʒ��\n";
	node ond;
	cin >> ond.sort >> ond.brand;
	cout << "������������º���Ʒ�����ƣ�Ʒ�ƣ��۸������\n";
	node nnd;
	cin >> nnd.sort >> nnd.brand >> nnd.price >> nnd.amount;
	updat(head, ond,nnd);
}
//ȫ����ʾ�û�����
void showall(list head)
{
	if (head == nullptr || head->next == nullptr)
	{
		cout << "���������ڣ�\n";
		return;
	}
	for (list p = head->next; p != nullptr; p = p->next)
		cout << "���ƣ�" << p->sort
			<< "  Ʒ�ƣ�" << p->brand
			<< "  �۸�" << p->price
			<< "  ������" << p->amount << endl;
}
//��ʾ��Ʒ�û�����
void showitem(list head)
{
	if (head == nullptr || head->next == nullptr)
	{
		cout << "���������ڣ�\n";
		return;
	}
	cout << "����������Ҫ��ѯ����Ʒ������Ʒ��\n";
	string sort, brand; cin >> sort >> brand;
	for (list p = head->next; p != nullptr;p=p->next)
		if (p->sort == sort && p->brand == brand)
		{
			cout << "���ƣ�" << sort
				<< "  Ʒ�ƣ�" << brand
				<< "  �۸�" << p->price
				<< "  ������" << p->amount << endl;
			return;
		}
	cout << "����Ʒ�����ڣ�\n";
}
//�˵�
bool menu(list head)
{
	cout << "1.����  2.���  3.��ѯȫ��  4.��ѯ��Ʒ  5.������Ϣ  6.Ӫҵ����\n";
	int choice; cin >> choice;
	switch (choice)
	{
	case 1:
		indat(head); break;
	case 2:
		deldat(head); break;
	case 3:
		showall(head); break;
	case 4:
		showitem(head); break;
	case 5:
		refresh(head); break;
	case 6:
		return false;
	}
	return true;
}
//װ���ļ�
void tofile(list head, string addr)
{
	if (head == nullptr || head->next == nullptr)
		return;
	ofstream file(addr, ios::out);
	for (list p = head->next; p != nullptr; p = p->next)
		file << p->sort << " " << p->brand << " "
		<< p->price << " " << p->amount << endl;
	file.close();
}
//��ʼ������
void tolist(list head, string addr)
{
	node nd;
	fstream file(addr,ios::in | ios::app);
	while (file >> nd.sort >> nd.brand >> nd.price >> nd.amount)
		insrt(head, nd);
	file.close();
}
int main()
{
	cout << "��ӭʹ��������ϵͳ��\n"
		<< "�����������ļ���ַ��";
	string addr; cin >> addr;
	list head = makenull();
	tolist(head, addr);
	while (menu(head))
		;
	tofile(head, addr);
	system("pause");
	return 0;
}