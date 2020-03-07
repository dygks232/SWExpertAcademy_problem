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

bool isOutOfRange(int r, int c);
void dfs();

int T, R, C, answer, limit;

int board[21][21];
int dirR[4] = { -1,0,1,0 };
int dirC[4] = { 0,-1,0,1 };

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

bool isOutOfRange(int r, int c)
{
	return r < 0 || c < 0 || r >= R || c >= C;
}

void dfs()
{
	int currR, currC, nextR, nextC, currDist, currVisit;
	stack<pair<pair<int, int>, pair<int, int> > > Stack;
	Stack.push({ {1,1 << board[0][0]},{0,0} });

	while (!Q.empty())
	{
		currR = Stack.top().second.first;
		currC = Stack.top().second.second;
		currDist = Stack.top().first.first;
		currVisit = Stack.top().first.second;
		Stack.pop();
		for (int dir = 0; dir < 4; dir++)
		{
			nextR = currR + dirR[dir];
			nextC = currC + dirC[dir];
			if (isOutOfRange(nextR, nextC))
				continue;
			if (currVisit & (1 << board[nextR][nextC]))
				continue;
			Stack.push({ { currDist + 1,currVisit | (1 << board[nextR][nextC]) }, { nextR,nextC } });
			answer = max(answer, currDist + 1);
			if (answer == limit)
				return;
		}
	}
}

void inputAndInit()
{
	char in[21];
	scanf("%d %d", &R, &C);
	answer = 1;
	limit = min(R * C, 26);
	for (int r = 0; r < R; r++)
	{
		scanf("%s", in);
		for (int c = 0; c < C; c++)
		{
			board[r][c] = in[c] - 'A';
		}
	}
}

void solve()
{
	dfs();
}

void output(int n)
{
	printf("#%d %d\n", n, answer);
}