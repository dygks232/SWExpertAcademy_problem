#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<stack>
#include<queue>
#include<deque>
#include<algorithm>
#include<cmath>
#include<climits>
#include<set>
#include<map>
#include<string>
#include<cstring>
#include<functional>
using namespace std;

#define MAXN 1001

struct pos {
	int x, y;
	pos() { x = y = 0; }
	pos(int a, int b) { x = a; y = b; }
};

void inputAndInit();
void solve();
void output(int n);

long long calcDist(int x1, int y1, int x2, int y2);
void makeEdge();
int find(int u);
bool merge(int u, int v);
void kruskal();

int T, N;
long long ans;
double E, answer;

pos input[MAXN];
vector<pair<long long, pair<int, int> > > edge;
int parent[MAXN];

int main()
{
	scanf("%d", &T);
	for (int i = 1; i <= T; i++)
	{
		inputAndInit();
		solve();
		output(i);
	}
	return 0;
}

long long calcDist(int x1, int y1, int x2, int y2)
{
	return (long long)(x1 - x2) * (long long)(x1 - x2) + (long long)(y1 - y2) * (long long)(y1 - y2);
}

void makeEdge()
{
	edge.clear();
	for (int i = 1; i <= N; i++)
	{
		for (int j = i + 1; j <= N; j++)
		{
			edge.push_back({ calcDist(input[i].x,input[i].y,input[j].x,input[j].y),{i,j} });		
		}
	}
	sort(edge.begin(), edge.end());
}

int find(int u)
{
	if (u == parent[u])
		return u;
	return parent[u] = find(parent[u]);
}

bool merge(int u, int v)
{
	u = find(u);
	v = find(v);

	if (u == v)
		return false;

	parent[u] = v;
	return true;
}

void kruskal()
{
	int len = edge.size();
	for (int i = 0; i < len; i++)
	{
		if (merge(edge[i].second.first, edge[i].second.second))
			ans += edge[i].first;
	}
}

void inputAndInit()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &input[i].x);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &input[i].y);
		parent[i] = i;
	}
	scanf("%lf", &E);
	makeEdge();
	ans = 0;
}

void solve()
{
	kruskal();
	answer = E * ans;
}

void output(int n)
{
	printf("#%d %.0lf\n", n, answer);
}
