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

#define MAXV 101

void inputAndInit();
void solve();
void output(int n);

void dfs(int r, int c);

int T, N, answer;

int board[20][20];
bool use[MAXV];

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
	scanf("%d", &N);
	answer = -1;
	for(int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
		{
			scanf("%d", &board[r][c]);
		}
}

void dfs(int r, int c)
{
	bool flag;
	for (int L = 1; c - L >= 0; L++)
	{
		for (int R = 1; c + R < N; R++)
		{
			if (r + L + R >= N)
				continue;
			flag = false;
			memset(use, false, sizeof(use));

			for (int cc = 0; cc < R; cc++)
			{
				if (!use[board[r + cc][c + cc]])
					use[board[r + cc][c + cc]] = true;
				else
				{
					flag = true;
					break;
				}
			}
			if (flag) continue;
			for (int rr = 0; rr < L; rr++)
			{
				if (!use[board[r + R + rr][c + R - rr]])
					use[board[r + R + rr][c + R - rr]] = true;
				else
				{
					flag = true;
					break;
				}
			}
			if (flag) continue;
			for (int rr = 1; rr <= L; rr++)
			{
				if (!use[board[r + rr][c - rr]])
					use[board[r + rr][c - rr]] = true;
				else
				{
					flag = true;
					break;
				}
			}
			if (flag) continue;
			for (int cc = 1; cc <= R; cc++)
			{
				if (!use[board[r + L + cc][c - L + cc]])
					use[board[r + L + cc][c - L + cc]] = true;
				else
				{
					flag = true;
					break;
				}
			}
			if (flag) continue;
			answer = max(answer, (L + R) << 1);
		}
	}
}

void solve()
{
	for (int r = 0; r < N - 2; r++)
	{
		for (int c = 1; c < N - 1; c++)
		{
			dfs(r, c);
		}
	}
}

void output(int n)
{
	printf("#%d %d\n", n, answer);
}