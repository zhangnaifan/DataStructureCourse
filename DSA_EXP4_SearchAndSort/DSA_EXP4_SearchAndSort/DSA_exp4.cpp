#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

struct node {
	int key;
	node *lchild, *rchild;
	node() { lchild = rchild = NULL; }
};
typedef node* BST;

//BST���뺯��
//һֱ���£�ֱ���սڵ�
void insert(BST &tree, int key)
{
	if (!tree)
	{
		tree = new node;
		tree->key = key;
	}
	else if (key < tree->key)
		insert(tree->lchild, key);
	else if (key > tree->key)
		insert(tree->rchild, key);
}

//BST���Һ���
//��ڵ�ؼ������Ƚ�
//������ң���С��������ҵ����ڵ�������û�ҵ�
BST search(BST const &tree, int key)
{
	if (!tree || tree->key == key)
		return tree;
	if (key < tree->key)
		return search(tree->lchild, key);
	return search(tree->rchild, key);
}

//BSTɾ������
void dele(BST &tree, int key)
{
	if (!tree)//���շ��أ���ɾ��
		return;
	if (key < tree->key)//�������ϼ�����
		dele(tree->lchild, key);
	else if (key > tree->key)//�������ϼ�����
		dele(tree->rchild, key);
	else//�ҵ���
	{
		if (!tree->lchild)//�������գ�������ֱ�Ӽ̳У�����������ҲΪ�յ�����
		{
			BST tmp = tree->rchild;
			delete tree;
			tree = tmp;
		}
		else if (!tree->rchild)//���������գ��������գ�������ֱ�Ӽ̳�
		{
			BST tmp = tree->lchild;
			delete tree;
			tree = tmp;
		}
		else//�������������գ�����������������ڵ�̳У���ɾ���ü̳нڵ�
		{
			BST father = tree;
			BST root = tree->rchild;
			while (root->lchild)//�Ҽ̳нڵ�
			{
				father = root;
				root = root->lchild;
			}
			tree->key = root->key;//�̳�
			
			//ɾ���̳нڵ�
			BST tmp = root->rchild;
			delete root;
			if (father == tree)
				tree->rchild = tmp;
			else
				father->lchild = tmp;
		}
	}
}

//�ݹ�ʵ���������
void traverse(BST const &tree, vector<int> &n)
{
	if (!tree)
		return;
	traverse(tree->lchild,n);
	cout << tree->key << " ";
	n.push_back(tree->key);
	traverse(tree->rchild,n);
}

void traverse(BST const &tree)
{
	if (!tree)
		return;
	traverse(tree->lchild);
	cout << tree->key << " ";
	traverse(tree->rchild);
}

//�۰����
int bisearch(int key, vector<int> const &n, int low, int up)
{
	if (low > up)
		return -1;
	int mid = low + (up - low) / 2;
	if (n[mid] == key)
		return mid;
	if (key < n[mid])
		return bisearch(key, n, low, mid-1);
	return bisearch(key, n, mid + 1, up);
}

void bubbleSort(vector<int> &n)
{
	clock_t beg, end;
	beg = clock();
	int endi = n.size() - 1;
	for (int i = 0; i < endi; ++i)
		for (int j = endi-1 ; j >= i;--j)
			if (n[j] > n[j + 1])
			{
				int tmp = n[j];
				n[j] = n[j + 1];
				n[j + 1] = tmp;
			}
	end = clock();
	cout << "ð��������ʱ��" << (double)(end - beg) / CLOCKS_PER_SEC << endl;
}

void insertSort(vector<int> &n)
{
	clock_t beg, end;
	beg = clock();
	int endi = n.size() - 1;
	for (int i = 1; i <= endi; ++i)
	{
		int j;
		int key = n[i];
		for (j = i - 1; j >= 0 && key < n[j]; --j)
			n[j + 1] = n[j];
		n[j+1] = key;
	}
	end = clock();
	cout << "����������ʱ��" << (double)(end - beg) / CLOCKS_PER_SEC << endl;
}

void selectSort(vector<int> &n)
{
	clock_t beg, end;
	beg = clock();
	int endi = n.size() - 1;
	for (int i = 0; i < endi ; ++i)
	{
		int min = n[i];
		int minIndex = i;
		for (int j = i + 1; j <=endi ;++j)
			if (n[j] < min)
			{
				min = n[j];
				minIndex = j;
			}
		int tmp = n[minIndex];
		n[minIndex] = n[i];
		n[i] = tmp;
	}
	end = clock();
	cout << "ѡ��������ʱ��" << (double)(end-beg)/CLOCKS_PER_SEC << endl;
}

void quickSort(vector<int> &n, int low, int up)
{
	if (low >= up)
		return;
	int key = n[low];
	int i = low, j = up;
	while (i < j)
	{
		while (i < j && n[j] >= key)
			--j;
		n[i] = n[j];
		while (i < j && n[i] <= key)
			++i;
		n[j] = n[i];
	}
	n[i] = key;
	quickSort(n, low, i - 1);
	quickSort(n, i + 1, up);
}

int main()
{
	srand((unsigned int)time(NULL));
	vector<int> narr;
	int len;
	cout << "�������Ĵ�������Ҫ����ĸ�����"; cin >> len;

	//��������
	for (int i = 0; i < len; ++i)
		narr.push_back(rand() % len);
	clock_t beg, end;
	beg = clock();
	quickSort(narr, 0, len - 1);
	end = clock();
	cout << "����������ʱ��" << (double)(end - beg) / CLOCKS_PER_SEC << endl;
	narr.resize(0);
	
	//ð������
	for (int i = 0; i < len; ++i)
		narr.push_back(rand() % len);
	bubbleSort(narr);
	narr.resize(0);

	//��������
	for (int i = 0; i < len; ++i)
		narr.push_back(rand() % len);
	insertSort(narr);
	narr.resize(0);

	//ѡ������
	for (int i = 0; i < len; ++i)
		narr.push_back(rand() % len);
	selectSort(narr);
	narr.resize(0);

	//BST�Ľ���
	BST tree = NULL;
	cout << "���������������Ĵ�������������<100����";
	int n; cin >> n;
	for (int i = 0; i < n; ++i)
		insert(tree, rand()%100);
	cout << "������������";
	traverse(tree);
	cout << endl;

	//BST����
	cout << "������Ҫ���ҵĹؼ��ֵĸ�����";
	cin >> n;
	cout << "����������Ҫ���ҵĹؼ��֣�";
	for (int i = 0; i < n; ++i)
	{
		int k;
		cin >> k;
		if (search(tree, k))
			cout << "�ҵ��ˣ�" << endl;
		else
			cout << "û�ҵ���"<<endl;
	}

	//BST����
	cout << "������Ҫ����ĸ�����";
	cin >> n;
	cout << "����������Ҫ����Ĺؼ��֣�";
	for (int i = 0; i < n; ++i)
	{
		int tmp;
		cin >> tmp;
		insert(tree, tmp);
	}
	traverse(tree);
	cout << endl;

	//BSTɾ��
	cout << "������Ҫɾ���ĸ�����<=n����";
	cin >> n;
	cout << "����������Ҫɾ���Ĺؼ��֣�";
	for (int i = 0; i < n; ++i)
	{
		int tmp;
		cin >> tmp;
		dele(tree, tmp);
	}
	cout << "������������";
	traverse(tree,narr);
	cout << endl;

	//�۰����
	cout << "������Ҫ�۰���ҵĹؼ��ָ�����";
	cin >> n;
	cout << "����������Ҫ���ҵĹؼ��֣�";
	for (int i = 0; i < n; ++i)
	{
		int key;
		cin >> key;
		if ((key = bisearch(key, narr, 0, narr.size() - 1)) == -1)
			cout << "�Ҳ�����\n";
		else
			cout << "λ����"<<key<<endl;
	}
	system("pause");
	return 0;
}