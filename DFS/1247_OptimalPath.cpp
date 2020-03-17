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

#define MAXN 10
#define START (N)
#define END (N+1)

void inputAndInit();
void solve();
void output(int n);

int calcDist(int idx1, int idx2);
void dfs(int curr, int bit, int tempAns);

int T, N, answer;

pair<int, int> pos[MAXN + 2];
int dist[MAXN][1 << MAXN];
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

int calcDist(int idx1, int idx2)
{
	return abs(pos[idx1].first - pos[idx2].first) + abs(pos[idx1].second - pos[idx2].second);
}

void inputAndInit()
{
	scanf("%d", &N);
	answer = INT_MAX;
	memset(visit, false, sizeof(visit));
	memset(dist, -1, sizeof(dist));
	scanf("%d %d", &pos[START].first, &pos[START].second);
	scanf("%d %d", &pos[END].first, &pos[END].second);
	for (int i = 0; i < N; i++)
		scanf("%d %d", &pos[i].first, &pos[i].second);
}

void dfs(int curr, int bit, int tempAns)
{
	int nextAns;
	if (bit == (1 << N) - 1)
	{
		tempAns += calcDist(curr, END);
		answer = min(answer, tempAns);
		return;
	}

	for (int i = 0; i < N; i++)
	{
		if (curr == i || visit[i])
			continue;
		nextAns = tempAns + calcDist(curr, i);
		if (dist[i][bit | (1 << i)] != -1 && dist[i][bit | (1 << i)] < nextAns)
			continue;
		visit[i] = true;
		dist[i][bit | (1 << i)] = nextAns;
		dfs(i, bit | (1 << i), nextAns);
		visit[i] = false;
	}
}

void solve()
{
	int currDist;
	for (int i = 0; i < N; i++)
	{
		currDist = calcDist(START, i);
		if (dist[i][1 << i] == -1 || currDist <= dist[i][1 << i])
		{
			dist[i][1 << i] = currDist;
			visit[i] = true;
			dfs(i, 1 << i, currDist);
			visit[i] = false;
		}
	}
}

void output(int n)
{
	printf("#%d %d\n", n, answer);
}
