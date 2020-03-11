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

#define DOWN 2
#define RIGHT 3

void inputAndInit();
void solve();
void output(int n);

bool isOutOfRange(int r, int c);
void dfs(int r, int c, int val);
void greedy();

int T, N, answer, greedyAns;

int dirR[4] = { -1,0,1,0 };
int dirC[4] = { 0,-1,0,1 };

int board[100][100];
bool visit[100][100];
int memVal[100][100];

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
	return r < 0 || c < 0 || r >= N || c >= N;
}

void dfs(int r, int c, int val)
{
	int nextR, nextC, len, nextVal;
	memVal[r][c] = val;

	for(int dir = 0; dir < 4; dir++)
	{
		nextR = r + dirR[dir];
		nextC = c + dirC[dir];
		if (isOutOfRange(nextR, nextC) || visit[nextR][nextC])
			continue;
		if (nextR == N - 1 && nextC == N - 1)
		{
			answer = min(answer, val);
			continue;
		}
		nextVal = val + board[nextR][nextC];
		if (nextVal >= memVal[nextR][nextC])
			continue;
		if (nextVal >= answer)
			continue;

		visit[nextR][nextC] = true;
		dfs(nextR, nextC, nextVal);
		visit[nextR][nextC] = false;
	}
}

void inputAndInit()
{
	int in;
	scanf("%d", &N);
	greedyAns = 0;
	memset(visit, false, sizeof(visit));
	for (int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
		{
			scanf("%1d", &in);
			board[r][c] = in;
			memVal[r][c] = INT_MAX;
		}
}

void greedy()
{
	int currR = 0, currC = 0, downR, downC, rightR, rightC;
	while (currR != N - 1 || currC != N - 1)
	{
		downR = currR + dirR[DOWN];
		downC = currC + dirC[DOWN];
		rightR = currR + dirR[RIGHT];
		rightC = currC + dirC[RIGHT];
		if (downR < N && rightC < N)
		{
			if (board[downR][downC] < board[rightR][rightC])
			{
				greedyAns += board[downR][downC];
				currR = downR;	currC = downC;
			}
			else
			{
				greedyAns += board[rightR][rightC];
				currR = rightR;	currC = rightC;
			}
		}
		else if (currR == N - 1)
		{
			greedyAns += board[rightR][rightC];
			currR = rightR;	currC = rightC;			
		}
		else
		{
			greedyAns += board[downR][downC];
			currR = downR;	currC = downC;
		}
	}
	answer = greedyAns;
}

void solve()
{
	greedy();
	visit[0][0] = true;
	dfs(0, 0, 0);
}

void output(int n)
{
	printf("#%d %d\n", n, answer);
}