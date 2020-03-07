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

void calcAns(int r, int c);
int calcProfit(int r, int c);

int T, N, M, C, answer;

vector<vector<int> > board;
vector<vector<int> > profit;

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
	scanf("%d %d %d", &N, &M, &C);
	board = vector<vector<int> >(N, vector<int>(N));
	profit = vector<vector<int> >(N, vector<int>(N));
	answer = INT_MIN;
	for (int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
		{
			scanf("%d", &board[r][c]);
			profit[r][c] = board[r][c] * board[r][c];
		}
}

int calcProfit(int r, int c)
{
	int ret = INT_MIN;
	int currC, currP;

	for (int i = 1; i < 1 << M; i++)
	{
		currC = currP = 0;
		for (int j = 0; j < M; j++)
		{
			if (i & (1 << j))
			{
				currC += board[r][c + M - 1 - j];
				currP += profit[r][c + M - 1 - j];
			}
		}
		if (currC > C)
			continue;
		ret = max(ret, currP);
	}

	return ret;
}

void calcAns(int r, int c)
{
	if (r == N - 1 && c + M + M > N)
		return;
	int first = calcProfit(r, c);

	for (int col = c + M; col < N - M + 1; col++)
	{
		answer = max(answer, first + calcProfit(r, col));
	}

	for (int row = r + 1; row < N; row++)
	{
		for (int col = 0; col < N - M + 1; col++)
		{
			answer = max(answer, first + calcProfit(row, col));
		}
	}
}

void solve()
{
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N - M + 1; c++)
		{
			calcAns(r, c);
		}
	}
}

void output(int n)
{
	printf("#%d %d\n", n, answer);
}