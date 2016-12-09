//���ߣ����˷�
//ѧ�ţ�1143310119
//�༶��1403103
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
const int MAXWEIGHT = 10000000;//��������һ�ַ����ֵ�������

struct HuffmanNode {
	string bits;//�ԡ�0101110����ʽ��ŵĹ���������
	int weight;//���ַ����ֵĴ���
	int parent;
	int lchild;
	int rchild;
	HuffmanNode();
};
HuffmanNode::HuffmanNode() { parent = lchild = rchild = -1; weight = 0; bits = ""; }

struct HuffmanTree {
	HuffmanNode tree[255];//2*128-1Ϊ���������Ľڵ����
	int count;//�ѽ����Ľڵ���
	HuffmanTree() { count = 128; }
};

//���������ɭ�֣���������������
//����Ȩֵ��С����������λ��
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

//��128������ʼ������������
void build(HuffmanTree &t)
{
	cout << "���ڽ�����������......" << endl;
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
	cout << "���������ѽ���\n";
}

//������������ĸ��ڵ㣬����Ҫ������ļ���
//���ÿ���ַ��ĳ���Ƶ��
//����Ҫ�����Դ�ļ���
string getWeight(HuffmanTree &t)
{
	cout << "��������Ҫ������ļ���ַ(��D:\\\\filename.txt)��";
	string fileName; cin >> fileName;
	ifstream file(fileName, ios::binary);
	if (!file.is_open())
	{
		cout << "�ļ���ʧ�ܣ�\n";
		return "";
	}
	cout << "���ڻ�ȡ�ַ�Ƶ��......\n";
	char ch;
	int illgal = 0;
	while (file.get(ch))
		if (ch >= 0)
			++t.tree[ch].weight;
		else
			++illgal;
	file.close();
	cout << "�ַ�Ƶ���ѻ�ȡ\n";
	if (illgal)
		cout << "���Ǵ��ڷ�ASCII���ַ���ֻ�ܸ�ˣ�\n";
	return fileName;
}

//�ݹ��ȡÿһ���ַ��ġ�0101101����ʽ�ı���
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

//ѹ�����ܺ���
//����Ҫ�����Դ�ļ����Լ��Ѿ������Ĺ�������
//���ѹ�����ܣ�����ѹ�������Ϣ�洢���û�ָ�����ļ���
string encrypt(HuffmanTree const &t, string fileName)
{
	if (fileName == "")
		return "";
	ifstream file(fileName,ios::binary);
	cout << "���½������ļ��ĵ�ַ(��D:\\\\efilename.txt)��";
	string fout; cin >> fout;
	fstream ofile(fout,ios::app | ios::binary);
	if (!ofile.is_open())
	{
		cout << "�ļ���ʧ�ܣ�\n";
		return "";
	}
	cout << "���ڼ���......\n";

	//����stringstream�࣬8��8������'0'��'1'
	stringstream buff;
	//�������ġ�0110110�������ݴ���buff��
	for (char ch; file.get(ch);)
		if(ch>=0)
			buff << t.tree[ch].bits;

	//mark�������β�ͳ���
	char mark = buff.str().size() % 8;
	ofile.write((char*)&mark, sizeof(char));

	//����0110110������ÿ8������һ���ַ��У�����������ļ�
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

		//�������8����Ҫ����
		for (; i < 7; ++i, ch <<= 1);

		ofile.write((char*)&ch, sizeof(char));
	}
	ofile.close();
	file.close();
	cout << "�������\n";
	return fout;
}

//����
//��������ļ����Լ���Ӧ�Ĺ�������
//��ɽ�ѹ����
//������ѹ�����Ϣ���ڽ�ѹ�ļ���
void decode(HuffmanTree const &t, string fileName)
{
	if (fileName == "")
		return;
	cout << "���½��������ļ���ַ(��D:\\\\decode.txt)��";
	string deco; cin >> deco;
	ofstream fout(deco, ios::app | ios::binary);
	ifstream fin(fileName, ios::binary);
	if (!fout.is_open())
	{
		cout << "�ļ���ʧ�ܣ�\n"; 
		return;
	}
	cout << "���ڽ�ѹ......\n";

	//����stringstream���ݴ�����ļ��������ַ��Ķ�����λ
	stringstream stream;

	//mark��ȡ����β�ͳ���
	char mark; fin.get(mark);

	//���ö���һ����������һ���ķ���
	//����ֱ�Ӵ������һ��������������Ϣ���ַ�
	char ch1, ch2;
	fin.get(ch1);
	while (fin.get(ch2))
	{
		for (int i = 0; i < 8; ++i, ch1 <<= 1)
			//����ch1�����λ������<0���ж��Ƿ�Ϊ1
			if (ch1 < 0)
				stream << '1';
			else
				stream << '0';
		ch1 = ch2;
	}

	//����β��
	for (int i = 0; i < mark; ++i, ch1 <<= 1)
		if (ch1 < 0)
			stream << '1';
		else
			stream << '0';

	//����0110110������Ӧ���ڹ��������У��ҵ���Ӧ�Ľڵ�
	//������Ӧ���ַ��������ѹ�ļ���
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
	cout << "��ѹ�ɹ����뵽"<<deco<<"�в鿴\n";
}


int main()
{
	HuffmanTree t;
	string sourceFile=getWeight(t);
	build(t);
	encode(t,254,"");
	//��������볤��<10���ַ�
	for (int i = 0; i < 128; ++i)
		if (t.tree[i].bits.size() < 10)
			cout <<"ascii��"<< i <<" "<<t.tree[i].weight<< " " << t.tree[i].bits << endl;
	decode(t, encrypt(t, sourceFile));
	system("pause");
	return 0;
}