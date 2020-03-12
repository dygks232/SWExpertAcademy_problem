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

typedef pair<long long, int> pldi;

struct pos {
	int x, y;
	pos() { x = y = 0; }
	pos(int a, int b) { x = a; y = b; }
};

void inputAndInit();
void solve();
void output(int n);

void makeLink();
void mst_prim(int start);

int T, N;
long long ans;
double E, answer;

pos input[MAXN];
long long linkCost[MAXN][MAXN-2];
int linkIdx[MAXN][MAXN-2];
bool visit[MAXN];

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

void makeLink()
{
	int idx;
	for (int i = 1; i <= N; i++)
	{
		idx = 0;
		for (int j = 1; j <= N; j++)
		{
			if (i == j)
				continue;
			linkCost[i][idx] = (long long)(input[i].x - input[j].x) * (long long)(input[i].x - input[j].x) + (long long)(input[i].y - input[j].y) * (long long)(input[i].y - input[j].y);
			linkIdx[i][idx++] = j;
		}
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
		visit[i] = false;
	}
	scanf("%lf", &E);
	makeLink();
	ans = 0;
}

void mst_prim(int start)
{
	int currIdx, chk = 1;
	long long currCost;
	priority_queue<pldi, vector<pldi>, greater<pldi> > PQ;
	visit[start] = true;

	for (int i = 0; i < N - 1; i++)
	{
		PQ.push({ linkCost[start][i],linkIdx[start][i] });
	}

	while (!PQ.empty())
	{
		if (chk == N)
			break;
		currCost = PQ.top().first;
		currIdx = PQ.top().second;
		PQ.pop();
		if (visit[currIdx])
			continue;
		visit[currIdx] = true;
		ans += currCost;
		chk++;
		for (int i = 0; i < N - 1; i++)
		{
			PQ.push({ linkCost[currIdx][i],linkIdx[currIdx][i] });
		}
	}
}

void solve()
{
	mst_prim(1);
	answer = E * ans;
}

void output(int n)
{
	printf("#%d %.0lf\n", n, answer);
}
