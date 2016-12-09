#include <iostream>
#include <string>
#include <fstream>
using namespace std;
//**********第四题**********
//测试结果：
//1）完全正确数据，正常运行
//2）部分正确数据和完全错误数据，能够根据取值范围排错，并提醒用户

struct school {
	string name = "????";
	int id = -1;
	int tot = 0;
	int male = 0;
	int female = 0;
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
		file << "\t" << num << "\t" << gen << "\t" << eid << "\t" << ename;
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
	int num, gen, eid, sid, score;
	string ename, sname;
	int found = 0;
	for (int i = 1; i <= n; ++i)
	{
		file >> num >> gen >> eid >> ename;
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

	int num, gen, eid, sid, score;
	string ename, sname;
	int found = 0;
	for (int i = 1; i <= m + w; ++i)
	{
		file >> num >> gen >> eid >> ename;
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
	if (found == 0)
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
void sortAndOut(string addr, bool f(school **, int))
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

	school schoolset[21], *s[21];
	for (int i = 1; i <= n; ++i)
	{
		file >> schoolset[i].id >> schoolset[i].name >> schoolset[i].tot >> schoolset[i].male >> schoolset[i].female;
		s[i] = &schoolset[i];
	}

	for (int i = 1; i <= n; ++i)
		for (int j = n - 1; j >= i; --j)
			if (f(s, j))
			{
				school *tmp = s[j];
				s[j] = s[j + 1];
				s[j + 1] = tmp;
			}

	file.close();

	for (int i = 1; i <= n; ++i)
		cout << "\n序号：" << i << "：  学院名称：" << s[i]->name << "  学院总分：" << s[i]->tot
		<< "  男生分数：" << s[i]->male << "  女生分数：" << s[i]->female;
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
	string addr = getAdd();
	while (menu(addr))
		;
	system("pause");
	return 0;
}