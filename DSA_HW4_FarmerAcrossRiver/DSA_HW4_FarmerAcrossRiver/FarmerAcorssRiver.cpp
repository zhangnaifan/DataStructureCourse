//���ߣ����˷�
//ѧ�ţ�1143310119
//�༶��11403103
#include <iostream>
#include <vector>
using namespace std;

struct edge {
	int vnum;
	edge* next;
	edge() { next = NULL; }
};

//��ͼ�ڵ��ʾũ��ǰ���ڵİ����ð���ǰͣ������Ʒ״̬
struct vnode {
	bool shore;//shoreΪ0��ʾ������1��ʾ�԰�
	//����0��ʾû�У�1��ʾ��
	bool wolf;
	bool sheep;
	bool vegetable;
	edge* firstEdge;
	vnode() { firstEdge = NULL; }
};

vector<vnode> gra;

//��ʼ�����������п��ܴ��ڵ�״̬���㣩���Լ�����֮����ܵ�ת�����ߣ�
//���س�ʼ״̬�µ�ͼ�ڵ�λ�ã����±꣩
int init()
{
	int ret = 0;

	//������
	for (int p = 0; p<=1;++p)
		for (int i = 0; i<=1; ++i)
			for (int j = 0; j<=1; ++j)
				for (int k = 0; k<=1; ++k)
					//���ҽ���������ũ����һ��
					//�������ڣ��Ǻ��򶼺�ũ����һ��ʱ���ܷ���
					if (j || i && k)
					{
						vnode tmp;
						tmp.shore = p;
						tmp.wolf = i;
						tmp.sheep = j;
						tmp.vegetable = k;

						//���س�ʼ״̬�����������ǣ����߲˶���ũ����һ��ʱ
						//��λ��
						if (!p && i && j && k)
							ret = gra.size();

						gra.push_back(tmp);
					}

	//������
	int total = gra.size();
	for (int i = 0; i < total; ++i)
		for (int j = 0; j < total;++j)

			//���ҽ���ũ�����ڵİ������仯
			//��������һ������ʱ�����ֱ仯���ܷ���
			if ((gra[i].shore != gra[j].shore) && 
				((gra[i].wolf == gra[j].wolf) + (gra[i].sheep == gra[j].sheep) + (gra[i].vegetable == gra[j].vegetable) <=1))
			{
				edge* tmp = new edge;
				tmp->vnum = j;
				tmp->next = gra[i].firstEdge;
				gra[i].firstEdge = tmp;
			}
	return ret;
}

//����Ѿ����ֹ���״̬
//���ֹ��ľͲ����ٳ�����
bool visited[32];

//��������λ��tail���յ��λ��arrow
//���ũ��Ķ���
bool showhow(int tail, int arrow)
{
	if (gra[tail].shore)
		cout << "ũ��Ӷ԰��ߵ�����";
	else
		cout << "ũ��ӱ����ߵ��԰�";
	if (gra[tail].wolf == gra[arrow].wolf)
		cout << "����������";
	if (gra[tail].sheep == gra[arrow].sheep)
		cout << "����������";
	if (gra[tail].vegetable == gra[arrow].vegetable)
		cout << "���������߲�";
	cout << endl;
	return true;
}

//�ݹ�ʵ�֣�������ȱ���ֱ���ҵ�����·����������ù���
//��������ڵ��λ��start
//���start������·���еĵ㣬�򷵻�true�����򣬷���false
bool traverse(int start)
{
	if (gra[start].shore && gra[start].wolf && gra[start].sheep && gra[start].vegetable)
		return true;
	for (edge* e = gra[start].firstEdge; e; e = e->next)//����ÿһ��δ���ʹ��ĵ㣬������ѷ���
		if (!visited[e->vnum] && (visited[e->vnum] = true))
			if (traverse(e->vnum))//�����������Ϣ����·���ϣ�
				return showhow(start, e->vnum);//����ù��̣��������ϴ��ݺ���Ϣ
	return false;//�������·���ϣ�����false
}

int main()
{
	traverse(init());
	system("pause");
	return 0;
}