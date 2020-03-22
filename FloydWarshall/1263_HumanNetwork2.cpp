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

#define INF 555555555

void inputAndInit();
void solve();
void output(int n);

void floyd();

int T, N, answer;

int link[1000][1000];

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
	int in;
	scanf("%d", &N);
	answer = INT_MAX;
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			link[r][c] = INF;
			scanf("%d", &in);
			if (in) link[r][c] = 1;
		}
	}
}

void floyd()
{
	for (int k = 0; k < N; k++)
	{
		for (int i = 0; i < N; i++)
		{
			if (k == i || link[i][k] >= INF) continue;
			for (int j = 0; j < N; j++)
			{
				if (j == k || j == i) continue;
				link[i][j] = min(link[i][j], link[i][k] + link[k][j]);
			}
		}
	}
}

void solve()
{
	floyd();

	int sum;
	for (int r = 0; r < N; r++)
	{
		sum = 0;
		for (int c = 0; c < N; c++)
		{
			if (link[r][c] >= INF)
				continue;
			sum += link[r][c];
		}
		answer = min(answer, sum);
	}
}

void output(int n)
{
	printf("#%d %d\n", n, answer);
}
