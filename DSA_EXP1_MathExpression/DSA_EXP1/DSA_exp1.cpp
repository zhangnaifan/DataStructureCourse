#include <iostream>
#include <stack>
#include <string>
#include <cstdlib>
using namespace std;

stack<char> op;//运算符栈
stack<double> num;//数栈，用来存放数

string tnum, expr, buff;
//tnum用来临时存放数的部分字符
//expr用来存放输入的表达式
//buff用来暂存表达式结果

//函数value 输入一个字符，输出运算符的优先级
//其中-号为取反，优先级最高
//左括号为方便出栈处理，优先级最低
int value(char c)//计算运算符的优先级
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

//函数prio，输入两个字符，输出前一个字符相对后一个字符优先级情况
//若a优先或等于b，则输出为1；否则为0
bool prio(char a, char b)
{
	return value(a) >= value(b);
}

//函数cal，弹出运算符栈栈顶，弹出数栈的操作数与运算符进行运算，并将结果送回数栈
//如果顺利计算则返回1，否则返回0
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
				cout << "运算过程中出现除0错误！请重新输入表达式！\n";
				return false;
			}
			num.top() = b/a;
			break;
		case '%':
			if ((a - (int)a > 1e-6 || a-(int)a <-1e-6) || (b-(int)b > 1e-6 || b-(int)b <-1e-6))
			{
				cout << "取模运算只能对整数进行！请重新输入表达式！\n";
				return false;
			}
			if (b<1e-6 && b>-1e-6)
			{
				cout << "发生除零错误！请重新输入表达式！\n";
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

//验证表达式中的字符是否有效
bool islegal(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '(' || c == ')' || c >= '0' && c <= '9' || c == '.' || c==' ';
}


//验证表达式是否正确，如果正确则在减号前补上+号并返回1
bool check_addPlus()
{
	//初始化i，j，分别指向两个相邻的非空位置
	unsigned int i = 0, j = 0;
	//标记是否出现过数字
	bool hasnum = 0;
	//标记左右括号数
	int left_bra = 0, right_bra = 0;

	//第0步：检查字符串非空
	if (expr.empty())
	{
		cout << "不能没有输入！请输入表达式！\n";
		return false;
	}

	//第一步：验证是否存在非法字符
	while (j < expr.size())
		if (!islegal(expr[j++]))
			{
				cout << "存在非法字符！请重新输入表达式！\n";
				return false;
			}

	//第二步：验证当仅有一个非空格有效字符或者许多空格的情形
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
			cout << "表达式必须含有数字！请重新输入！\n";
			return false;
		}
		return true;
	}

	//第三步：验证首个字符
	if (!(expr[j] == '(' || expr[j] == '-' || (expr[j] <= '9' && expr[j] >= '0' || expr[j] == '.')))
	{
		cout << "表达式必须以数字或左括号开头！请重新输入！\n";
		return false;
	}

	//第四步：同时验证左右括号数是否匹配，以及前后字符是否符合表达式规则
	//并完成在减号前补上+号的任务
	while (i < expr.size())//顺序扫描字符串
	{
		//在减号之前补上+号
		if (expr[i] == '-' && ((expr[j] <= '9' && expr[j] >= '0' || expr[j]=='.') || expr[j] == ')'))
			expr.insert(i, 1,'+');

		//j是数字的一部分
		if (expr[j] <= '9' && expr[j] >= '0' || expr[j] == '.')
		{
			if (!hasnum)
				++hasnum;
			if (expr[i] == '(')
			{
				cout << "数字之后不能紧跟括号！请重新输入表达式\n";
				return false;
			}
		}

		//j是右括号
		else if (expr[j] == ')')
		{
			++right_bra;
			if (expr[i] == '(' || (expr[i] <= '9' && expr[i] >= '0' || expr[i] == '.'))
			{
				cout << "右括号之后不合法！请重新输入表达式\n";
				return false;
			}
		}
		else
		{
			if (expr[j] == '(')
				++left_bra;
			if (expr[i] != '(' && expr[i] != '-' && !(expr[i] <= '9' && expr[i] >= '0' || expr[i] == '.'))
			{
				cout << "表达式有误！请重新输入\n";
				return false;
			}
		}

		//为下一次循坏做准备
		j = i;
		++i;
		while (i < expr.size() && expr[i] == ' ')
			++i;
	}

	//第五步：检查最后一个有效字符
	if (expr[j] == ')')
		++right_bra;
	else if (expr[j] <= '9' && expr[j] >= '0' || expr[j] == '.')
		hasnum = 1;
	else
	{
		cout << "表达式必须以数字或右括号结尾！请重新输入！\n";
		return false;
	}

	//第六步：清算左右括号数
	if (left_bra != right_bra)
	{
		cout << "左右括号不匹配！请重新输入表达式！\n";
		return false;
	}

	//第七步：清算是否未出现过数字
	if (!hasnum)
	{
		cout << "表达式中必须含有至少一个数！请重新输入表达式！\n";
		return false;
	}
	return true;
}

//初始化各全局变量
void ini()
{
	while (!op.empty())
		op.pop();
	while (!num.empty())
		num.pop();
	tnum = expr = buff = "";
}

//输出程序运行时的说明信息
void displ()
{
	cout << "***********************************************************************\n"
		<< "***********************************************************************\n"
		<< "本程序中，所有的-号将当作单操作数运算符取反处理\n"
		<< "并自动在减号前补上+号，使之完整\n"
		<< "因此在输入负数时无需加上括号，甚至可以将任意多个-号连在一起使用\n"
		<< "而且，本程序提供了表达式检查功能，因此无需担心程序崩溃。试试吧！\n"
		<< "***********************************************************************\n"
		<< "***********************************************************************\n";
}

//判断一个由数字和小数点组成的字符串是否为合法的数
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
		cout<< "\n请输入一个中缀表达式，以换行符结尾：\n";
		getline(cin, expr);
		if (!check_addPlus())
			continue;
		
		//扫描字符串
		for (int i = 0, endi = expr.size(); i != endi; ++i)
		{
			//跳过所有空格
			if (expr[i] == ' ')
				continue;
			//如果是数的一部分，则加入tnum
			if (expr[i] <= '9' && expr[i] >= '0' || expr[i] == '.')
					tnum += expr[i];
			//处理运算符和括号
			else
			{
				//如果还有未处理的数，则把这个数压入数栈
				if (!tnum.empty())
				{
					if (!is_legal_num(tnum))
					{
						cout << "数字输入不合法！请重新输入表达式！\n";
						goto restart;
					}
					num.push(atof(tnum.c_str()));
					buff += tnum;
					buff += ' ';
					tnum.resize(0);
					//由于-号具有最高的优先级，必须一次性处理完所有连在一起的-号
					while (!op.empty() && op.top() == '-')
						if (!cal())
							goto restart;
				}

				//如果遇到'('或者栈空，直接压入当前运算符或左括号
				if (expr[i] == '(' || op.empty())
				{
					if (expr[i] != ')')
						op.push(expr[i]);
					else
					{
						cout << "括号使用错误！请重新输入表达式！\n";
						goto restart;
					}
				}

				//如果遇到右括号，依次弹出栈内的运算符，直到遇到左括号，并将左括号弹出
				else if (expr[i] == ')')
				{
					while (!op.empty() && op.top() != '(')
						if (!cal())
							goto restart;
					if (op.empty())
					{
						cout << "左右括号不匹配！请重新输入表达式！\n";
						goto restart;
					}
					op.pop();
				}
				//处理多个-号连在一起的情况
				else if (expr[i] == '-' && op.top()=='-')
					op.push('-');
				else
				{
					//如果栈顶运算符优先级>=待比较的字符，则弹出栈顶运算符，并立即计算结果，返回num
					if (prio(op.top(), expr[i]))
					{
						if (!cal())
							goto restart;
						op.push(expr[i]);
					}

					//否则，直接将带比较字符入栈
					else
						op.push(expr[i]);
				}
			}
		}

		//遍历过后，如果还有未入数栈的数，则入栈
		if (!tnum.empty())
		{
			if (!is_legal_num(tnum))
			{
				cout << "数字输入不合法！请重新输入表达式！\n";
				goto restart;
			}
			num.push(atof(tnum.c_str()));
			buff += tnum;
			buff += ' ';
			tnum.resize(0);
			//立即处理负数
			while (!op.empty() && op.top() == '-')
				if (!cal())
					goto restart;
		}

		//如果运算符栈中还有运算符，则依次从栈顶弹出，并计算结果
		while (!op.empty())
			if (!cal())
				goto restart;
		cout << "后缀表达式为：" << buff << endl;
		cout << "结果是：" << num.top() << endl;
		cout << "***************************************************\n";
	}
	system("pause");
	return 0;
}