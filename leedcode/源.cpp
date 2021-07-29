#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<string>
#include<map>
#include<queue>
#include<stack>
using namespace std;
int f[100][100];
int fa[100];
int head[100];
int dept[100];
int full = 3;//总状态数
struct edge
{
	int v;
	int next;
}e[10000];
int cnt = 1;
void add(int x, int y)
{
	e[cnt].v = y;
	e[cnt].next = head[x];
	head[x] = cnt;
	cnt++;
}
void dfs(int x)
{
	for (int i = 1; i < 20; i++)
		f[x][i] = f[f[x][i - 1]][i - 1];
	for (int i = head[x]; i!=0; i=e[i].next)
	{
		int val = e[i].v;
		f[val][0] = x;
		dept[val] = dept[x] + 1;
		dfs(val);
	}
	
}
int lca(int x, int y)
{
	if (dept[y] > dept[x])
	{
		//swap
	}
	while (dept[x] > dept[y])
	{
		x = fa[x];
	}
	if (x == y)
		return x;
	for (int i = 20; i >= 0; i--)
	{
		if (dept[f[x][i]] != dept[f[y][i]])
		{
			x = f[x][i];
			y = f[y][i];
		}
	}
	return f[x][0];

}
class LRUCache {
private:  int capac;
private: vector<int>p;
private:map<int, int>k;
public:
	LRUCache(int capacity) {
		this->capac = capacity;
	}

	int get(int key) {
		vector<int>::iterator it;
		it = find(p.begin(), p.end(), key);
		if (it != p.end())
		{
			int ans = *it;
			p.erase(it);
			p.push_back(ans);
			return k[ans];
		}
		return -1;
	}

	void put(int key, int value) {
		k[key] = value;
		vector<int>::iterator it;
		it = find(p.begin(), p.end(), key);
		if (it == p.end())
		{
			p.push_back(key);
			if (p.capacity() > capac)
				p.erase(p.begin());
		}
		else {
			int ans = *it;
			p.erase(it);
			p.push_back(ans);
		}
	}
};
class vertex
{
public:
	vertex(vector<int>g, vector<int>o)
	{
		graph = g;
		op = o;
	}
	~vertex()
	{

	}

public:
	vector<int>graph;
	vector<int>op;
};

vector<int> update(vector<int>store,int index)//更新方块状态，适用于排成一列
{
	vector<int> st = store;
	st[index] = st[index] % full + 1;
	if(index-1>=0)
		st[index-1] = st[index-1] % full + 1;
	if (index + 1 < st.size())
		st[index + 1] = st[index + 1] % full + 1;
	return st;
}
vector<int> Update(vector<int>store, int index)//更新方块状态，适用于排成一圈
{
	vector<int> st = store;
	st[index] = st[index] % full + 1;
	st[(index-1)%store.size()]= st[(index - 1) % store.size()] % full + 1;
	st[(index + 1) % store.size()] = st[(index + 1) % store.size()] % full + 1;
	return st;
}
bool check(vector<int>c)//检查是否满足相等
{
	int f = 1;
	for (int i = 0; i <c.size()-1; i++)
	{
		if (c[i] != c[i + 1])
		{
			f = 0;
			break;
		}
	}
	return f;
}
vector<int> bfs(vertex x)//广搜，队列里存的是图状态
{
	queue<vertex>solve;
	solve.push(x);
	while (!solve.empty())
	{
		vertex top = solve.front();
		solve.pop();
		if (check(top.graph))
			return top.op;
		vector<int>::iterator it;
		int i;
		for (i=0,it = top.graph.begin(); it != top.graph.end(); it++,i++)
		{
			vertex temp = top;
			temp.op.push_back(i);
			temp.graph = update(temp.graph, i);
			solve.push(temp);
		}
	}
}
int main()
{
	/*ListNode A(1, NULL);
	ListNode *a=&A;
	ListNode B(2, a);
	ListNode* b=&B;
	ListNode C(3, b);
	ListNode* c = &C;
	ListNode D(4, c);
	ListNode* d = &D;
	ListNode E(5, d);
	ListNode* e = &E;*/
	vector<int>ope;
	vector<int>gra = { 2,1,2,3 };
	vertex init(gra, ope);
	vector<int>ans = bfs(init);
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << " ";
	system("pause");
	LRUCache *c=new LRUCache(3);
	c->put(1, 1);
	c->put(2, 2);
	c->put(3, 3);
	c->put(4, 4);
	cout<<c->get(4);
	cout<<c->get(3);
	cout<<c->get(2);
	cout << c->get(1);
	c->put(5, 5);
	//ListNode* f = s.reverseList(e);
	cout << c->get(1);
	cout << c->get(2);
	cout << c->get(3);
	cout << c->get(4);
	cout << c->get(5);
	system("pause");
}

