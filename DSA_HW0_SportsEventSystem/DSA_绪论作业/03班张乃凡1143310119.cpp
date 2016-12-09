#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//**********第一题**********
//*[] 用于存储
char *str[] = { "PAB","5C","PABC","CXY","CRSI","7","B899","B9" };
//可以采用单链表存储，体现有序性
struct LIST_1 {
	char* s;
	LIST_1 *next;
};

//函数 value 用来将字符转换为整数值，大小满足题意
int value(char c)
{
	if (c >= 'A' && c <= 'Z')
		return c - 'A';
	if (c >= '0' && c <= '9')
		return c - '0' + 26;
	return -1;		//如果c=='\0'，返回-1
}

//函数 cmp 用来比较两个字符串的大小
int cmp(char *a, char *b)
{
	while (*a != '\0' && *b != '\0' && value(*a) == value(*b))
	{
		++a;
		++b;
	}
	return value(*a) - value(*b);
}

//函数 ssort 用来排序字符串，采用快速排序
void ssort(char **s, int left, int right)
{
	if (left >= right)
		return;
	int i = left, j = right;
	char *key = s[left];
	while (i < j)
	{
		while (i < j && cmp(s[j], key)>0)
			--j;
		s[i] = s[j];
		while (i < j && cmp(s[i], key) < 0)
			++i;
		s[j] = s[i];
	}
	s[i] = key;
	ssort(s, left, i - 1);
	ssort(s, i + 1, right);
}

//用 displ 来输出排序后的字符串
void displ(char **s,int n)
{
	for (int i = 0; i <= n; ++i)
		cout << s[i] << "\t";
	cout << endl;
}

//**********第二题**********
//存储：由于元素个数为100，可以直接考虑用数组线性表存储
struct LIST_2 {
	int p[101];
	int last;
};
//在末尾插入x
void insert(LIST_2 &l, int x)
{
	l.p[++l.last] = x;
}
//将表置空
void makenull(LIST_2 &l)
{
	l.last = 0;
}
//输出结果
void displ(LIST_2 l)
{
	for (int i = 1; i <= l.last; ++i)
		cout << l.p[i] << "\t";
	cout << endl;
}
//函数 findp 找到所有最大值所在的位置
void findp_link(int a[],int n)
{
	LIST_2 list;
	int max=a[1];
	list.p[1] = 1;
	list.last = 1;
	for (int i = 2; i <= n; ++i)
	{
		if (a[i] > max)
		{
			max = a[i];
			makenull(list);
			insert(list, i);
		}
		else if (a[i] == max)
			insert(list, i);
	}
	displ(list);
}
//----------------------------------------------
//也可以用单链表存储
struct LIST_2_LINK {
	int p;
	LIST_2_LINK *next;
};
//在头节点后插入x
void insert(LIST_2_LINK &l, int x)
{
	LIST_2_LINK *pl = new LIST_2_LINK;
	pl->p = x;
	pl->next = l.next;
	l.next = pl;
}
//删除LIST,保留头节点
void del(LIST_2_LINK &l)
{
	if (l.next == nullptr)
		return;
	LIST_2_LINK *pl = l.next->next;
	while (pl != nullptr)
	{
		delete l.next;
		l.next = pl;
		pl = pl->next;
	}
	delete l.next;
	l.next = nullptr;
}
void displ(LIST_2_LINK l)
{
	l = *l.next;
	while (l.next != nullptr)
	{
		cout << l.p << "\t";
		l = *l.next;
	}
	cout << l.p << endl;
}
//找到所有最大值所在的位置
void findp(int a[], int n)
{
	LIST_2_LINK head;
	head.next = new LIST_2_LINK;
	int max = a[1];
	head.next->p = 1;
	head.next->next = nullptr;
	for (int i = 2; i <= n; ++i)
	{
		if (a[i] > max)
		{
			max = a[i];
			del(head);
			insert(head, i);
		}
		else if (a[i] == max)
			insert(head, i);
	}
	displ(head);
	del(head);
}


//**********第三题**********
//采用二维数组rlt[i][j]存储比赛结果
//若rlt[i][j]==1,则i胜j负，否则，rlt[i][j]==0，i负j胜
bool rlt[100][100];
//用 getr 函数来获取胜负关系
void getr(int n)
{
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j < i; ++j)
		{
			cout << "请输入第" << j << "人对第" << i << "人的比赛结果：若i胜则输入1；否则请输入0\t\t";
			bool r;
			cin >> r;
			rlt[j][i] = r;
			rlt[i][j] = !r;
			cout << endl;
		}
}
//用单链表来存放可能的序列
struct LIST_3 {
	int p;
	LIST_3 *next;
};


//**********第四题**********
//测试结果：
//1）完全正确数据，正常运行
//2）部分正确数据和完全错误数据，能够根据取值范围排错，并提醒用户

struct school {
	string name="????";
	int id=-1;
	int tot=0;
	int male=0;
	int female=0;
};

void checkid(int &id)
{
	if (id > 20 || id < 1)
	{
		do {
			cout << "输入必须在1-20之间，请重新输入\t\t";
			cin >> id;
		} while (id > 20 || id < 1);
	}
}
void checkname(string &s)
{
	if (s.size() > 20)
	{
		do {
			cout << "输入名字的长度不能超过20，请重新输入\t\t";
			cin >> s;
		} while (s.size() > 20);
	}
}
void checknum(int &num)
{
	if (num != 3 && num != 5)
	{
		do {
			cout << "请重新输入3或者5\t\t";
			cin >> num;
		} while (num != 3 && num != 5);
	}
}
void inputdata(ofstream &file, school *schoolset, bool gen, int n)
{
	string gender[2] = { "女生","男生" };
	int num, eid, sid, score;
	string ename, sname;
	int points[6] = { 0, 7,5,3,2,1 };
	for (int i = 1; i <= n; ++i)
	{
		cout << "请输入第" << i << "个" << gender[gen] << "项目的编号：\t"; cin >> eid; checkid(eid);
		cout << "请输入该项目的名称，20字符以内\t\t"; cin >> ename; checkname(ename);
		cout << "请输入3或者5，表示要录入前n名的成绩\t\t"; cin >> num; checknum(num);
		file << "\t" << num << "\t"<<gen<<"\t" << eid << "\t" << ename;
		for (int i = 1; i <= num; ++i)
		{
			cout << "请输入第" << i << "名的学院的编号\t\t"; cin >> sid; checkid(sid);
			cout << "请输入第" << i << "名的学院的名称\t\t"; cin >> sname; checkname(sname);
			cout << "请输入第" << i << "名的成绩\t\t"; cin >> score;
			schoolset[sid].id = sid;
			schoolset[sid].name = sname;
			int pot = num == 3 ? points[i + 2] : points[i];
			if (gen == 0)
			{
				schoolset[sid].female += pot;
				schoolset[sid].tot += pot;
			}
			else
			{
				schoolset[sid].male += pot;
				schoolset[sid].tot += pot;
			}
			file << "\t" << sid << "\t" << sname << "\t" << score;
		}
	}
}
void input(string add)
{
	ofstream file(add, ios::out);

	int n, m, w;
	cout << "请输入n，表示要录入的有n个学院\t\t"; cin >> n; checkid(n);
	cout << "请输入m，表示要录入的有m个男生项目\t\t"; cin >> m; checkid(m);
	cout << "请输入w，表示要录入的有w个学院\t\t"; cin >> w; checkid(w);
	file << "\t" << n << "\t" << m << "\t" << w;

	school schoolset[21];

	inputdata(file, schoolset, 1, m);
	inputdata(file, schoolset, 0, w);

	for (int i = 1; i <= n; ++i)
		file << "\t" << i << "\t" << schoolset[i].name << "\t" << schoolset[i].tot
		<< "\t" << schoolset[i].male << "\t" << schoolset[i].female;

	file.close();
}

void showEvent(string add)
{
	ifstream file(add, ios::in);
	cout << "请输入所要查询的项目编号t\t";
	int teid; cin >> teid;
	int n, m, w;
	file >> n >> m >> w;
	int num, gen, eid,sid,score;
	string ename, sname;
	int found = 0;
	for (int i = 1; i <= n; ++i)
	{
		file >> num >> gen >> eid>>ename;
		if (eid == teid)
		{
			found = 1;
			cout << "项目id：" << eid << "\t项目名称：" << ename << endl;
			for (int i = 1; i <= num; ++i)
			{
				file >> sid >> sname >> score;
				cout << "第" << i << "名：" << "编号：" << sid
					<< "学院：" << sname << "\t成绩：" << score << endl;
			}
			break;
		}
		for (int i = 1; i <= num; ++i)
			file >> sid >> sname >> score;
	}
	if (found == 0)
		cout << "未找到\n";
	file.close();
}
void showSchoolEvent(string add)
{
	ifstream file(add, ios::in);
	cout << "请输入学院的编号\t\t";
	int tsid; cin >> tsid; 
	cout << "请输入所要查询的项目编号\t\t";
	int teid; cin >> teid;

	int n, m, w;
	file >> n >> m >> w;

	int num, gen,eid,sid,score;
	string ename,sname;
	int found=0;
	for (int i = 1; i <= m + w;++i)
	{
		file >> num >>gen>> eid >> ename;
		if (eid == teid)
		{
			for (int i = 1; i <= num; ++i)
			{
				file >> sid >> sname >> score;
				if (sid == tsid)
				{
					found = 1;
					cout << "获得第" << i << "名，得分为" << score << endl;
				}
			}
			break;
		}
		for (int i = 1; i <= num; ++i)
			file >> sid >> sname >> score;
	}
	if (found==0)
		cout << "该学院在本项目并未获得名次\n";
	file.close();
}

bool namecmp(school **s, int j)
{
	return s[j]->name > s[j + 1]->name;
}
bool femalecmp(school** s, int j)
{
	return s[j]->female < s[j + 1]->female;
}
bool malecmp(school **s, int j)
{
	return s[j]->male < s[j + 1]->male;
}
bool totcmp(school** s, int j)
{
	return s[j]->tot < s[j + 1]->tot;
}
bool idcmp(school** s, int j)
{
	return s[j]->id > s[j + 1]->id;
}
void sortAndOut(string addr,bool f(school **,int))
{
	ifstream file(addr, ios::in);
	int n, m, w;
	file >> n >> m >> w;
	int num, gen, eid, sid, score;
	string ename, sname;

	for (int i = 1; i <= m + w; ++i)
	{
		file >> num >> gen >> eid >> ename;
		for (int i = 1; i <= num; ++i)
			file >> sid >> sname >> score;
	}

	school schoolset[21],*s[21];
	for (int i = 1; i <= n; ++i)
	{
		file >> schoolset[i].id >> schoolset[i].name >> schoolset[i].tot >> schoolset[i].male >> schoolset[i].female;
		s[i] = &schoolset[i];
	}

	for (int i = 1; i <= n; ++i)
		for (int j = n - 1; j >= i; --j)
			if (f(s,j))
			{
				school *tmp = s[j];
				s[j] = s[j + 1];
				s[j + 1] = tmp;
			}

	file.close();

	for (int i = 1; i <= n; ++i)
		cout << "\n序号：" << i << "：  学院名称：" << s[i]->name << "  学院总分：" << s[i]->tot 
		<< "  男生分数：" << s[i]->male << "  女生分数："<< s[i]->female;
}

void checkchoice(int &choice)
{
	if (choice>7 || choice <0)
		do {
			cout << "请重新输入0-7中的某个数\t\t";
			cin >> choice;
		} while (choice > 7 || choice < 1);
}
int menu(string add)
{
	int state = 1;
	cout << "输入一个数字以表示所要进行的操作\n0：退出系统\n"
		<< "1：查询某学院某项目的情况；\n2：查询某项目的情况；\n"
		<< "3.按学院编号输出学院成绩\n4.按学院名称输出成绩\n"
		<< "5.按学院总分输出学院成绩\n6.按男生团体总分输出学院成绩\n"
		<< "7.按女生团体总分输出学院成绩\n";
	int choice; cin >> choice; checkchoice(choice);
	switch (choice)
	{
	case 0:
		state = 0;
		break;
	case 1:
		showSchoolEvent(add);
		break;
	case 2:
		showEvent(add);
		break;
	case 3:
		sortAndOut(add, idcmp);
		break;
	case 4:
		sortAndOut(add, namecmp);
		break;
	case 5:
		sortAndOut(add, totcmp);
		break;
	case 6:
		sortAndOut(add, malecmp);
		break;
	case 7:
		sortAndOut(add, femalecmp);
		break;
	}
	return state;
}

string getAdd()
{
	bool got_add;
	string add;
	cout << "如果您已经输入过数据，请输入1；否则，输入0以新建数据\t";
	cin >> got_add;
	if (got_add)
	{
		cout << "请输入您保存数据的文件地址，注意不能有空格\t\t";
		cin >> add;
	}
	else
	{
		cout << "请输入您要将数据文件存储的地址\t\t";
		cin >> add;
		input(add);
	}
	return add;
}

int main()
{
	//**********第一题**********
	ssort(str, 0, 7);
	displ(str, 7);
	

	//**********第二题**********
	int a[101];
	cout << "请输入数的个数\n";
	int n; cin >> n;
	cout << "请依次输入这n个数\n";
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	findp(a, n);
	

	//**********第三题**********
	cout << "请输入参与比赛的总人数\n";
	int n3; cin >> n3;
	getr(n3);
	LIST_3 head;
	head.next = nullptr;
	for (int i = 1; i <= n3; ++i)
	{
		LIST_3 *pt = &head;
		LIST_3 *pl = new LIST_3;
		pl->p = i;
		while (pt->next != nullptr && !rlt[i][pt->next->p])
			pt = pt->next;
		pl->next = pt->next;
		pt->next = pl;
	}
	cout << "其中一种序列是：\t";
	for (int i = 1; i <= n3; ++i)
	{
		cout << head.next->p << "  ";
		LIST_3 *tmp = head.next;
		head.next = head.next->next;
		delete tmp;
	}
	cout << endl;


	//**********第四题**********
	string addr = getAdd();
	while (menu(addr))
		;

	return 0;
}