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
//初始化链表
list makenull()
{
	list ret = new node;
	return ret;
}
//执行按价格插入操作
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
//执行删除/减少操作
void del(list head, node nd)
{
	if (head == nullptr || head->next == nullptr)
		return;
	list p = head;
	while (p->next != nullptr && p->next->price < nd.price)
		p = p->next;
	if (p->next == nullptr || p->next->price > nd.price + 1e-3)
	{
		cout << "找不到该商品！\n";
		return;
	}
	if (p->next->amount < nd.amount)
	{
		cout << "没有足够库存！\n";
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
//更新有关名称，品牌，价格的信息
void updat(list head, node ond, node nnd)
{
	if (head == nullptr || head->next == nullptr)
		return;
	list p = head;
	while (p->next != nullptr && (p->next->sort != ond.sort || p->next->brand != ond.brand))
		p = p->next;
	if (p->next == nullptr)
	{
		cout << "未找到原商品！\n";
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
//进货
void indat(list head)
{
	cout << "请依次输入进货商品的名称，品牌，价格和数量\n";
	node nd;
	cin >> nd.sort >> nd.brand >> nd.price >> nd.amount;
	insrt(head, nd);
}
//提货
void deldat(list head)
{
	if (head == nullptr || head->next == nullptr)
	{
		cout << "该链表不存在！\n";
		return;
	}
	cout << "请依次输入要提货商品的名称，品牌，价格和数量\n";
	node nd;
	cin >> nd.sort >> nd.brand >> nd.price >> nd.amount;
	del(head, nd);
}
//更新用户界面
void refresh(list head)
{
	if (head == nullptr || head->next == nullptr)
	{
		cout << "该链表不存在！\n";
		return;
	}
	cout << "请依次输入原商品的名称，品牌\n";
	node ond;
	cin >> ond.sort >> ond.brand;
	cout << "请依次输入更新后商品的名称，品牌，价格和数量\n";
	node nnd;
	cin >> nnd.sort >> nnd.brand >> nnd.price >> nnd.amount;
	updat(head, ond,nnd);
}
//全部显示用户界面
void showall(list head)
{
	if (head == nullptr || head->next == nullptr)
	{
		cout << "该链表不存在！\n";
		return;
	}
	for (list p = head->next; p != nullptr; p = p->next)
		cout << "名称：" << p->sort
			<< "  品牌：" << p->brand
			<< "  价格：" << p->price
			<< "  数量：" << p->amount << endl;
}
//显示单品用户界面
void showitem(list head)
{
	if (head == nullptr || head->next == nullptr)
	{
		cout << "该链表不存在！\n";
		return;
	}
	cout << "请依次输入要查询的商品名称与品牌\n";
	string sort, brand; cin >> sort >> brand;
	for (list p = head->next; p != nullptr;p=p->next)
		if (p->sort == sort && p->brand == brand)
		{
			cout << "名称：" << sort
				<< "  品牌：" << brand
				<< "  价格：" << p->price
				<< "  数量：" << p->amount << endl;
			return;
		}
	cout << "该商品不存在！\n";
}
//菜单
bool menu(list head)
{
	cout << "1.进货  2.提货  3.查询全部  4.查询单品  5.更新信息  6.营业结束\n";
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
//装入文件
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
//初始化链表
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
	cout << "欢迎使用链表库存系统！\n"
		<< "请输入数据文件地址：";
	string addr; cin >> addr;
	list head = makenull();
	tolist(head, addr);
	while (menu(head))
		;
	tofile(head, addr);
	system("pause");
	return 0;
}