#include <iostream>
#include <stack>
#include <string>
#include <cstdlib>
using namespace std;

stack<char> op;//�����ջ
stack<double> num;//��ջ�����������

string tnum, expr, buff;
//tnum������ʱ������Ĳ����ַ�
//expr�����������ı��ʽ
//buff�����ݴ���ʽ���

//����value ����һ���ַ����������������ȼ�
//����-��Ϊȡ�������ȼ����
//������Ϊ�����ջ�������ȼ����
int value(char c)//��������������ȼ�
{
	switch (c)
	{
	case '(':
		return 0;
	case '+':
		return 1;
	case '*':
	case '/':
	case '%':
		return 2;
	case '-':
		return 3;
	}
	return -1;
}

//����prio�����������ַ������ǰһ���ַ���Ժ�һ���ַ����ȼ����
//��a���Ȼ����b�������Ϊ1������Ϊ0
bool prio(char a, char b)
{
	return value(a) >= value(b);
}

//����cal�����������ջջ����������ջ�Ĳ�������������������㣬��������ͻ���ջ
//���˳�������򷵻�1�����򷵻�0
bool cal()
{
	char c = op.top();
	if (c == '-')
	{
		num.top() = -num.top();
	}
	else
	{
		double a = num.top();
		num.pop();
		double b = num.top();
		switch (c)
		{
		case '+':
			num.top() = a + b;
			break;
		case '*':
			num.top() = a*b;
			break;
		case '/':
			if (a < 1e-6 && a>-1e-6)
			{
				cout << "��������г��ֳ�0����������������ʽ��\n";
				return false;
			}
			num.top() = b/a;
			break;
		case '%':
			if ((a - (int)a > 1e-6 || a-(int)a <-1e-6) || (b-(int)b > 1e-6 || b-(int)b <-1e-6))
			{
				cout << "ȡģ����ֻ�ܶ��������У�������������ʽ��\n";
				return false;
			}
			if (b<1e-6 && b>-1e-6)
			{
				cout << "�����������������������ʽ��\n";
				return false;
			}
			num.top() = int(b) % int(a);
			break;
		}
	}
	buff += c;
	buff += ' ';
	op.pop();
	return true;
}

//��֤���ʽ�е��ַ��Ƿ���Ч
bool islegal(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '(' || c == ')' || c >= '0' && c <= '9' || c == '.' || c==' ';
}


//��֤���ʽ�Ƿ���ȷ�������ȷ���ڼ���ǰ����+�Ų�����1
bool check_addPlus()
{
	//��ʼ��i��j���ֱ�ָ���������ڵķǿ�λ��
	unsigned int i = 0, j = 0;
	//����Ƿ���ֹ�����
	bool hasnum = 0;
	//�������������
	int left_bra = 0, right_bra = 0;

	//��0��������ַ����ǿ�
	if (expr.empty())
	{
		cout << "����û�����룡��������ʽ��\n";
		return false;
	}

	//��һ������֤�Ƿ���ڷǷ��ַ�
	while (j < expr.size())
		if (!islegal(expr[j++]))
			{
				cout << "���ڷǷ��ַ���������������ʽ��\n";
				return false;
			}

	//�ڶ�������֤������һ���ǿո���Ч�ַ��������ո������
	while (i < expr.size()-1 && expr[i] == ' ')
		++i;
	j = i;
	if (i < expr.size()-1)
		++i;
	while (i < expr.size()-1 && expr[i] == ' ')
		++i;
	if (expr[i] == ' ')
		i = j;
	if (i == j)
	{
		if (!(expr[j] <= '9' && expr[j] >= '0' || expr[j] == '.'))
		{
			cout << "���ʽ���뺬�����֣����������룡\n";
			return false;
		}
		return true;
	}

	//����������֤�׸��ַ�
	if (!(expr[j] == '(' || expr[j] == '-' || (expr[j] <= '9' && expr[j] >= '0' || expr[j] == '.')))
	{
		cout << "���ʽ���������ֻ������ſ�ͷ�����������룡\n";
		return false;
	}

	//���Ĳ���ͬʱ��֤�����������Ƿ�ƥ�䣬�Լ�ǰ���ַ��Ƿ���ϱ��ʽ����
	//������ڼ���ǰ����+�ŵ�����
	while (i < expr.size())//˳��ɨ���ַ���
	{
		//�ڼ���֮ǰ����+��
		if (expr[i] == '-' && ((expr[j] <= '9' && expr[j] >= '0' || expr[j]=='.') || expr[j] == ')'))
			expr.insert(i, 1,'+');

		//j�����ֵ�һ����
		if (expr[j] <= '9' && expr[j] >= '0' || expr[j] == '.')
		{
			if (!hasnum)
				++hasnum;
			if (expr[i] == '(')
			{
				cout << "����֮���ܽ������ţ�������������ʽ\n";
				return false;
			}
		}

		//j��������
		else if (expr[j] == ')')
		{
			++right_bra;
			if (expr[i] == '(' || (expr[i] <= '9' && expr[i] >= '0' || expr[i] == '.'))
			{
				cout << "������֮�󲻺Ϸ���������������ʽ\n";
				return false;
			}
		}
		else
		{
			if (expr[j] == '(')
				++left_bra;
			if (expr[i] != '(' && expr[i] != '-' && !(expr[i] <= '9' && expr[i] >= '0' || expr[i] == '.'))
			{
				cout << "���ʽ��������������\n";
				return false;
			}
		}

		//Ϊ��һ��ѭ����׼��
		j = i;
		++i;
		while (i < expr.size() && expr[i] == ' ')
			++i;
	}

	//���岽��������һ����Ч�ַ�
	if (expr[j] == ')')
		++right_bra;
	else if (expr[j] <= '9' && expr[j] >= '0' || expr[j] == '.')
		hasnum = 1;
	else
	{
		cout << "���ʽ���������ֻ������Ž�β�����������룡\n";
		return false;
	}

	//����������������������
	if (left_bra != right_bra)
	{
		cout << "�������Ų�ƥ�䣡������������ʽ��\n";
		return false;
	}

	//���߲��������Ƿ�δ���ֹ�����
	if (!hasnum)
	{
		cout << "���ʽ�б��뺬������һ������������������ʽ��\n";
		return false;
	}
	return true;
}

//��ʼ����ȫ�ֱ���
void ini()
{
	while (!op.empty())
		op.pop();
	while (!num.empty())
		num.pop();
	tnum = expr = buff = "";
}

//�����������ʱ��˵����Ϣ
void displ()
{
	cout << "***********************************************************************\n"
		<< "***********************************************************************\n"
		<< "�������У����е�-�Ž������������������ȡ������\n"
		<< "���Զ��ڼ���ǰ����+�ţ�ʹ֮����\n"
		<< "��������븺��ʱ����������ţ��������Խ�������-������һ��ʹ��\n"
		<< "���ң��������ṩ�˱��ʽ��鹦�ܣ�������赣�ĳ�����������԰ɣ�\n"
		<< "***********************************************************************\n"
		<< "***********************************************************************\n";
}

//�ж�һ�������ֺ�С������ɵ��ַ����Ƿ�Ϊ�Ϸ�����
bool is_legal_num(string num)
{
	int count = 0;
	for (string::iterator it = num.begin(), endit = num.end(); it != endit; ++it)
		if (*it == '.')
			if (++count > 1)
				return false;
	return true;
}

int main()
{
	displ();
	while (true)
	{
	restart:		
		ini();
		cout<< "\n������һ����׺���ʽ���Ի��з���β��\n";
		getline(cin, expr);
		if (!check_addPlus())
			continue;
		
		//ɨ���ַ���
		for (int i = 0, endi = expr.size(); i != endi; ++i)
		{
			//�������пո�
			if (expr[i] == ' ')
				continue;
			//���������һ���֣������tnum
			if (expr[i] <= '9' && expr[i] >= '0' || expr[i] == '.')
					tnum += expr[i];
			//���������������
			else
			{
				//�������δ�����������������ѹ����ջ
				if (!tnum.empty())
				{
					if (!is_legal_num(tnum))
					{
						cout << "�������벻�Ϸ���������������ʽ��\n";
						goto restart;
					}
					num.push(atof(tnum.c_str()));
					buff += tnum;
					buff += ' ';
					tnum.resize(0);
					//����-�ž�����ߵ����ȼ�������һ���Դ�������������һ���-��
					while (!op.empty() && op.top() == '-')
						if (!cal())
							goto restart;
				}

				//�������'('����ջ�գ�ֱ��ѹ�뵱ǰ�������������
				if (expr[i] == '(' || op.empty())
				{
					if (expr[i] != ')')
						op.push(expr[i]);
					else
					{
						cout << "����ʹ�ô���������������ʽ��\n";
						goto restart;
					}
				}

				//������������ţ����ε���ջ�ڵ��������ֱ�����������ţ����������ŵ���
				else if (expr[i] == ')')
				{
					while (!op.empty() && op.top() != '(')
						if (!cal())
							goto restart;
					if (op.empty())
					{
						cout << "�������Ų�ƥ�䣡������������ʽ��\n";
						goto restart;
					}
					op.pop();
				}
				//������-������һ������
				else if (expr[i] == '-' && op.top()=='-')
					op.push('-');
				else
				{
					//���ջ����������ȼ�>=���Ƚϵ��ַ����򵯳�ջ���������������������������num
					if (prio(op.top(), expr[i]))
					{
						if (!cal())
							goto restart;
						op.push(expr[i]);
					}

					//����ֱ�ӽ����Ƚ��ַ���ջ
					else
						op.push(expr[i]);
				}
			}
		}

		//���������������δ����ջ����������ջ
		if (!tnum.empty())
		{
			if (!is_legal_num(tnum))
			{
				cout << "�������벻�Ϸ���������������ʽ��\n";
				goto restart;
			}
			num.push(atof(tnum.c_str()));
			buff += tnum;
			buff += ' ';
			tnum.resize(0);
			//����������
			while (!op.empty() && op.top() == '-')
				if (!cal())
					goto restart;
		}

		//��������ջ�л���������������δ�ջ����������������
		while (!op.empty())
			if (!cal())
				goto restart;
		cout << "��׺���ʽΪ��" << buff << endl;
		cout << "����ǣ�" << num.top() << endl;
		cout << "***************************************************\n";
	}
	system("pause");
	return 0;
}