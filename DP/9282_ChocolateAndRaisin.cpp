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

int DP(int sR, int eR, int sC, int eC);

int T, R, C, answer;

int board[50][50];
int partialSum[50][50];
int cache[50][50][50][50];

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
	scanf("%d %d", &R, &C);
	memset(cache, -1, sizeof(cache));
	memset(partialSum, 0, sizeof(partialSum));
	

	for (int r = 0; r < R; r++)
	{
		for (int c = 0; c < C; c++)
		{
			scanf("%d", &board[r][c]);
			cache[r][r][c][c] = 0;

			if (!r)
			{
				if (!c)
					partialSum[r][c] = board[r][c];
				else
					partialSum[r][c] = partialSum[r][c - 1] + board[r][c];
			}
			else
			{
				if (!c)
					partialSum[r][c] = partialSum[r - 1][c] + board[r][c];
				else
					partialSum[r][c] = partialSum[r - 1][c] + partialSum[r][c - 1] - partialSum[r - 1][c - 1] + board[r][c];
			}
		}
	}
}


int DP(int sR, int eR, int sC, int eC)
{
	int& ret = cache[sR][eR][sC][eC];
	if (ret != -1)
		return ret;

	ret = INT_MAX;
	for (int c = sC; c < eC; c++)
	{
		ret = min(ret, DP(sR, eR, sC, c) + DP(sR, eR, c + 1, eC));
	}
	for (int r = sR; r < eR; r++)
	{
		ret = min(ret, DP(sR, r, sC, eC) + DP(r + 1, eR, sC, eC));
	}

	if (sR)
	{
		if (sC)
			ret += (partialSum[eR][eC] - partialSum[sR - 1][eC] - partialSum[eR][sC - 1] + partialSum[sR - 1][sC - 1]);
		else
			ret += (partialSum[eR][eC] - partialSum[sR - 1][eC]);
	}
	else
	{
		if (sC)
			ret += (partialSum[eR][eC] - partialSum[eR][sC - 1]);
		else
			ret += partialSum[eR][eC];
	}

	return ret;
}

void solve()
{
	answer = DP(0, R - 1, 0, C - 1);
}

void output(int n)
{
	printf("#%d %d\n", n, answer);
}