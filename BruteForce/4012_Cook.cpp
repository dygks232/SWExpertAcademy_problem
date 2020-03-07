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

int T, N, answer;

int board[16][16];
vector<int> permuFlag;

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
	answer = INT_MAX;
	permuFlag.assign(N, 1);
	for (int i = 0; i < N / 2; i++)
		permuFlag[i] = 0;
	for (int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
			scanf("%d", &board[r][c]);
}

void solve()
{
	int ret1, ret2;
	do {
		ret1 = ret2 = 0;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (i == j || permuFlag[i] != permuFlag[j])
					continue;
				if (!permuFlag[i])
					ret1 += board[i][j];
				else
					ret2 += board[i][j];
			}
		}
		answer = min(answer, abs(ret1 - ret2));
	} while (next_permutation(permuFlag.begin(), permuFlag.end()));
}

void output(int n)
{
	printf("#%d %d\n", n, answer);
}
