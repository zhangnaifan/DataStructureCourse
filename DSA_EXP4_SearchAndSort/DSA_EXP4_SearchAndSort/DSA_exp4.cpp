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

//BST插入函数
//一直往下，直到空节点
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

//BST查找函数
//与节点关键字作比较
//逢大往右，逢小往左，相等找到，节点若空则没找到
BST search(BST const &tree, int key)
{
	if (!tree || tree->key == key)
		return tree;
	if (key < tree->key)
		return search(tree->lchild, key);
	return search(tree->rchild, key);
}

//BST删除函数
void dele(BST &tree, int key)
{
	if (!tree)//树空返回，不删除
		return;
	if (key < tree->key)//左子树上继续找
		dele(tree->lchild, key);
	else if (key > tree->key)//右子树上继续找
		dele(tree->rchild, key);
	else//找到了
	{
		if (!tree->lchild)//左子树空，右子树直接继承，包括右子树也为空的情形
		{
			BST tmp = tree->rchild;
			delete tree;
			tree = tmp;
		}
		else if (!tree->rchild)//右子树不空，左子树空，右子树直接继承
		{
			BST tmp = tree->lchild;
			delete tree;
			tree = tmp;
		}
		else//左右子树都不空，则由右子树的最左节点继承，并删除该继承节点
		{
			BST father = tree;
			BST root = tree->rchild;
			while (root->lchild)//找继承节点
			{
				father = root;
				root = root->lchild;
			}
			tree->key = root->key;//继承
			
			//删除继承节点
			BST tmp = root->rchild;
			delete root;
			if (father == tree)
				tree->rchild = tmp;
			else
				father->lchild = tmp;
		}
	}
}

//递归实现中序遍历
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

//折半查找
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
	cout << "冒泡排序用时：" << (double)(end - beg) / CLOCKS_PER_SEC << endl;
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
	cout << "插入排序用时：" << (double)(end - beg) / CLOCKS_PER_SEC << endl;
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
	cout << "选择排序用时：" << (double)(end-beg)/CLOCKS_PER_SEC << endl;
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
	cout << "请输入四大排序所要排序的个数："; cin >> len;

	//快速排序
	for (int i = 0; i < len; ++i)
		narr.push_back(rand() % len);
	clock_t beg, end;
	beg = clock();
	quickSort(narr, 0, len - 1);
	end = clock();
	cout << "快速排序用时：" << (double)(end - beg) / CLOCKS_PER_SEC << endl;
	narr.resize(0);
	
	//冒泡排序
	for (int i = 0; i < len; ++i)
		narr.push_back(rand() % len);
	bubbleSort(narr);
	narr.resize(0);

	//插入排序
	for (int i = 0; i < len; ++i)
		narr.push_back(rand() % len);
	insertSort(narr);
	narr.resize(0);

	//选择排序
	for (int i = 0; i < len; ++i)
		narr.push_back(rand() % len);
	selectSort(narr);
	narr.resize(0);

	//BST的建立
	BST tree = NULL;
	cout << "请输入二叉查找树的待排序数个数（<100）：";
	int n; cin >> n;
	for (int i = 0; i < n; ++i)
		insert(tree, rand()%100);
	cout << "中序遍历结果：";
	traverse(tree);
	cout << endl;

	//BST查找
	cout << "请输入要查找的关键字的个数：";
	cin >> n;
	cout << "请依次输入要查找的关键字：";
	for (int i = 0; i < n; ++i)
	{
		int k;
		cin >> k;
		if (search(tree, k))
			cout << "找到了！" << endl;
		else
			cout << "没找到！"<<endl;
	}

	//BST插入
	cout << "请输入要插入的个数：";
	cin >> n;
	cout << "请依次输入要插入的关键字：";
	for (int i = 0; i < n; ++i)
	{
		int tmp;
		cin >> tmp;
		insert(tree, tmp);
	}
	traverse(tree);
	cout << endl;

	//BST删除
	cout << "请输入要删除的个数（<=n）：";
	cin >> n;
	cout << "请依次输入要删除的关键字：";
	for (int i = 0; i < n; ++i)
	{
		int tmp;
		cin >> tmp;
		dele(tree, tmp);
	}
	cout << "中序遍历结果：";
	traverse(tree,narr);
	cout << endl;

	//折半查找
	cout << "请输入要折半查找的关键字个数：";
	cin >> n;
	cout << "请依次输入要查找的关键字：";
	for (int i = 0; i < n; ++i)
	{
		int key;
		cin >> key;
		if ((key = bisearch(key, narr, 0, narr.size() - 1)) == -1)
			cout << "找不到！\n";
		else
			cout << "位置是"<<key<<endl;
	}
	system("pause");
	return 0;
}