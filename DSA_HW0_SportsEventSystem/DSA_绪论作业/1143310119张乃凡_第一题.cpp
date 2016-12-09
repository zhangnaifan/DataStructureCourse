#include <iostream>
#include <string>
#include <fstream>
using namespace std;
//**********������**********
//���Խ����
//1����ȫ��ȷ���ݣ���������
//2��������ȷ���ݺ���ȫ�������ݣ��ܹ�����ȡֵ��Χ�Ŵ��������û�

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
			cout << "���������1-20֮�䣬����������\t\t";
			cin >> id;
		} while (id > 20 || id < 1);
	}
}
void checkname(string &s)
{
	if (s.size() > 20)
	{
		do {
			cout << "�������ֵĳ��Ȳ��ܳ���20������������\t\t";
			cin >> s;
		} while (s.size() > 20);
	}
}
void checknum(int &num)
{
	if (num != 3 && num != 5)
	{
		do {
			cout << "����������3����5\t\t";
			cin >> num;
		} while (num != 3 && num != 5);
	}
}
void inputdata(ofstream &file, school *schoolset, bool gen, int n)
{
	string gender[2] = { "Ů��","����" };
	int num, eid, sid, score;
	string ename, sname;
	int points[6] = { 0, 7,5,3,2,1 };
	for (int i = 1; i <= n; ++i)
	{
		cout << "�������" << i << "��" << gender[gen] << "��Ŀ�ı�ţ�\t"; cin >> eid; checkid(eid);
		cout << "���������Ŀ�����ƣ�20�ַ�����\t\t"; cin >> ename; checkname(ename);
		cout << "������3����5����ʾҪ¼��ǰn���ĳɼ�\t\t"; cin >> num; checknum(num);
		file << "\t" << num << "\t" << gen << "\t" << eid << "\t" << ename;
		for (int i = 1; i <= num; ++i)
		{
			cout << "�������" << i << "����ѧԺ�ı��\t\t"; cin >> sid; checkid(sid);
			cout << "�������" << i << "����ѧԺ������\t\t"; cin >> sname; checkname(sname);
			cout << "�������" << i << "���ĳɼ�\t\t"; cin >> score;
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
	cout << "������n����ʾҪ¼�����n��ѧԺ\t\t"; cin >> n; checkid(n);
	cout << "������m����ʾҪ¼�����m��������Ŀ\t\t"; cin >> m; checkid(m);
	cout << "������w����ʾҪ¼�����w��ѧԺ\t\t"; cin >> w; checkid(w);
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
	cout << "��������Ҫ��ѯ����Ŀ���t\t";
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
			cout << "��Ŀid��" << eid << "\t��Ŀ���ƣ�" << ename << endl;
			for (int i = 1; i <= num; ++i)
			{
				file >> sid >> sname >> score;
				cout << "��" << i << "����" << "��ţ�" << sid
					<< "ѧԺ��" << sname << "\t�ɼ���" << score << endl;
			}
			break;
		}
		for (int i = 1; i <= num; ++i)
			file >> sid >> sname >> score;
	}
	if (found == 0)
		cout << "δ�ҵ�\n";
	file.close();
}
void showSchoolEvent(string add)
{
	ifstream file(add, ios::in);
	cout << "������ѧԺ�ı��\t\t";
	int tsid; cin >> tsid;
	cout << "��������Ҫ��ѯ����Ŀ���\t\t";
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
					cout << "��õ�" << i << "�����÷�Ϊ" << score << endl;
				}
			}
			break;
		}
		for (int i = 1; i <= num; ++i)
			file >> sid >> sname >> score;
	}
	if (found == 0)
		cout << "��ѧԺ�ڱ���Ŀ��δ�������\n";
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
		cout << "\n��ţ�" << i << "��  ѧԺ���ƣ�" << s[i]->name << "  ѧԺ�ܷ֣�" << s[i]->tot
		<< "  ����������" << s[i]->male << "  Ů��������" << s[i]->female;
}

void checkchoice(int &choice)
{
	if (choice>7 || choice <0)
		do {
			cout << "����������0-7�е�ĳ����\t\t";
			cin >> choice;
		} while (choice > 7 || choice < 1);
}
int menu(string add)
{
	int state = 1;
	cout << "����һ�������Ա�ʾ��Ҫ���еĲ���\n0���˳�ϵͳ\n"
		<< "1����ѯĳѧԺĳ��Ŀ�������\n2����ѯĳ��Ŀ�������\n"
		<< "3.��ѧԺ������ѧԺ�ɼ�\n4.��ѧԺ��������ɼ�\n"
		<< "5.��ѧԺ�ܷ����ѧԺ�ɼ�\n6.�����������ܷ����ѧԺ�ɼ�\n"
		<< "7.��Ů�������ܷ����ѧԺ�ɼ�\n";
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
	cout << "������Ѿ���������ݣ�������1����������0���½�����\t";
	cin >> got_add;
	if (got_add)
	{
		cout << "���������������ݵ��ļ���ַ��ע�ⲻ���пո�\t\t";
		cin >> add;
	}
	else
	{
		cout << "��������Ҫ�������ļ��洢�ĵ�ַ\t\t";
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