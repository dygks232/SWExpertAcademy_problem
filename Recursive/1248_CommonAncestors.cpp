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

void inputAndInit();
void solve();
void output(int n);

void calcSize(int curr);

int T, V, E, q1, q2, answer, treeSize;
int parent[10001];
pair<int, int> child[10001];

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

void inputAndInit()
{
	int p, c;
	scanf("%d %d %d %d", &V, &E, &q1, &q2);
	memset(parent, -1, sizeof(int) * (V + 1));
	memset(child, -1, sizeof(pair<int,int>) * (V + 1));
	for (int i = 0; i < E; i++)
	{
		scanf("%d %d", &p, &c);
		parent[c] = p;
		if (child[p].first != -1)
			child[p].second = c;
		else
			child[p].first = c;
	}
}

void solve()
{
	set<int> set;
	int curr, next;
	curr = q1; next = parent[q1];
	while (curr != 1)
	{
		set.insert(next);
		curr = next;
		next = parent[curr];
	}

	curr = q2; next = parent[q2];
	while (curr != 1)
	{
		if (set.find(next) != set.end())
		{
			answer = next;
			break;
		}
		curr = next;
		next = parent[curr];
	}

	treeSize = 0;
	calcSize(answer);
}

void calcSize(int curr)
{
	treeSize += 1;
	if (child[curr].second != -1)
		calcSize(child[curr].second);
	if (child[curr].first != -1)
		calcSize(child[curr].first);
}

void output(int n)
{
	printf("#%d %d %d\n", n, answer, treeSize);
}
