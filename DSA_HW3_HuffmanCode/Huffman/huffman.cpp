//作者：张乃凡
//学号：1143310119
//班级：1403103
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
const int MAXWEIGHT = 10000000;//文章中任一字符出现的最大次数

struct HuffmanNode {
	string bits;//以“0101110”形式存放的哈夫曼编码
	int weight;//该字符出现的次数
	int parent;
	int lchild;
	int rchild;
	HuffmanNode();
};
HuffmanNode::HuffmanNode() { parent = lchild = rchild = -1; weight = 0; bits = ""; }

struct HuffmanTree {
	HuffmanNode tree[255];//2*128-1为哈夫曼树的节点个数
	int count;//已建立的节点数
	HuffmanTree() { count = 128; }
};

//输入哈夫曼森林，和两个整数引用
//返回权值最小的两棵树的位置
void getChild(HuffmanTree const &t, int &p1, int &p2)
{
	int min1 = MAXWEIGHT, min2 = MAXWEIGHT;
	p1 = p2 = 0;
	for (int i = 0; i < t.count; ++i)
		if (t.tree[i].parent == -1)
		{
			if (t.tree[i].weight < min1)
			{
				p2 = p1;
				p1 = i;
				min2 = min1;
				min1 = t.tree[i].weight;
			}
			else if (t.tree[i].weight < min2)
			{
				p2 = i;
				min2 = t.tree[i].weight;
			}
		}
}

//由128棵树开始建立哈夫曼树
void build(HuffmanTree &t)
{
	cout << "正在建立哈夫曼树......" << endl;
	for (int i = 128; i < 255; ++i)
	{
		int p1, p2;
		getChild(t, p1, p2);
		t.tree[p2].parent = t.tree[p1].parent = i;
		t.tree[i].lchild = p1;
		t.tree[i].rchild = p2;
		t.tree[i].weight = t.tree[p1].weight + t.tree[p2].weight;
		++t.count;
	}
	cout << "哈夫曼树已建立\n";
}

//输入哈夫曼树的根节点，和所要编码的文件名
//获得每个字符的出现频率
//返回要编码的源文件名
string getWeight(HuffmanTree &t)
{
	cout << "请输入所要编码的文件地址(如D:\\\\filename.txt)：";
	string fileName; cin >> fileName;
	ifstream file(fileName, ios::binary);
	if (!file.is_open())
	{
		cout << "文件打开失败！\n";
		return "";
	}
	cout << "正在获取字符频率......\n";
	char ch;
	int illgal = 0;
	while (file.get(ch))
		if (ch >= 0)
			++t.tree[ch].weight;
		else
			++illgal;
	file.close();
	cout << "字符频率已获取\n";
	if (illgal)
		cout << "但是存在非ASCII码字符，只能割爱了！\n";
	return fileName;
}

//递归获取每一个字符的“0101101”形式的编码
void encode(HuffmanTree &t, int root, string code)
{
	if (t.tree[root].lchild == -1 && t.tree[root].rchild == -1)
	{
		t.tree[root].bits = code;
		return;
	}
	if (t.tree[root].lchild != -1)
		encode(t, t.tree[root].lchild, code+'0');
	if (t.tree[root].rchild != -1)
		encode(t, t.tree[root].rchild, code+'1');
}

//压缩加密函数
//输入要编码的源文件名以及已经建立的哈夫曼树
//完成压缩加密，并将压缩后的信息存储在用户指定的文件中
string encrypt(HuffmanTree const &t, string fileName)
{
	if (fileName == "")
		return "";
	ifstream file(fileName,ios::binary);
	cout << "请新建编码文件的地址(如D:\\\\efilename.txt)：";
	string fout; cin >> fout;
	fstream ofile(fout,ios::app | ios::binary);
	if (!ofile.is_open())
	{
		cout << "文件打开失败！\n";
		return "";
	}
	cout << "正在加密......\n";

	//借助stringstream类，8个8个处理'0'和'1'
	stringstream buff;
	//将编码后的”0110110“序列暂存在buff中
	for (char ch; file.get(ch);)
		if(ch>=0)
			buff << t.tree[ch].bits;

	//mark标记最后的尾巴长度
	char mark = buff.str().size() % 8;
	ofile.write((char*)&mark, sizeof(char));

	//将”0110110“序列每8个存在一个字符中，并存入加密文件
	for (char tmp; buff >> tmp;)
	{
		int i=0;
		char ch = 0;
		ch <<= 1;
		if (tmp == '1')
			ch += 1;
		for (; i < 7 && buff >> tmp; ++i)
		{
			ch <<= 1;
			if (tmp == '1')
				ch += 1;
		}

		//如果不足8个，要补齐
		for (; i < 7; ++i, ch <<= 1);

		ofile.write((char*)&ch, sizeof(char));
	}
	ofile.close();
	file.close();
	cout << "加密完成\n";
	return fout;
}

//解码
//输入加密文件民以及对应的哈夫曼树
//完成解压功能
//并将解压后的信息存在解压文件中
void decode(HuffmanTree const &t, string fileName)
{
	if (fileName == "")
		return;
	cout << "请新建解码后的文件地址(如D:\\\\decode.txt)：";
	string deco; cin >> deco;
	ofstream fout(deco, ios::app | ios::binary);
	ifstream fin(fileName, ios::binary);
	if (!fout.is_open())
	{
		cout << "文件打开失败！\n"; 
		return;
	}
	cout << "正在解压......\n";

	//借助stringstream类暂存加密文件中所有字符的二进制位
	stringstream stream;

	//mark读取最后的尾巴长度
	char mark; fin.get(mark);

	//采用读下一个，处理上一个的方法
	//避免直接处理最后一个可能有冗余信息的字符
	char ch1, ch2;
	fin.get(ch1);
	while (fin.get(ch2))
	{
		for (int i = 0; i < 8; ++i, ch1 <<= 1)
			//处理ch1的最高位，可用<0来判断是否为1
			if (ch1 < 0)
				stream << '1';
			else
				stream << '0';
		ch1 = ch2;
	}

	//处理尾巴
	for (int i = 0; i < mark; ++i, ch1 <<= 1)
		if (ch1 < 0)
			stream << '1';
		else
			stream << '0';

	//将”0110110“序列应用于哈夫曼树中，找到对应的节点
	//并将相应的字符输出到解压文件中
	for (char ch; stream >> ch;)
	{
		unsigned char root = 254;
		if (ch == '1')
			root = t.tree[root].rchild;
		else
			root = t.tree[root].lchild;
		while (root > 127)
		{
			stream >> ch;
			if (ch == '1')
				root = t.tree[root].rchild;
			else
				root = t.tree[root].lchild;
		}
		fout.put(root);
	}
	fin.close();
	fout.close();
	cout << "解压成功，请到"<<deco<<"中查看\n";
}


int main()
{
	HuffmanTree t;
	string sourceFile=getWeight(t);
	build(t);
	encode(t,254,"");
	//仅输出编码长度<10的字符
	for (int i = 0; i < 128; ++i)
		if (t.tree[i].bits.size() < 10)
			cout <<"ascii："<< i <<" "<<t.tree[i].weight<< " " << t.tree[i].bits << endl;
	decode(t, encrypt(t, sourceFile));
	system("pause");
	return 0;
}