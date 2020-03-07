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

void calcAns(int n);

int T, N, answer, peopleNum;
bool flag;

int board[15][15];
int row[15], col[15];

int stR[2];
int stC[2];
int stV[2];
vector<int> dist[2];
vector<int> TIME[2];
bool use[20][400];

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
	int idx = 0;
	scanf("%d", &N);
	answer = 999999;
	flag = false;
	for (int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
		{
			scanf("%d", &board[r][c]);
			if (board[r][c] == 1)
			{
				row[idx] = r;
				col[idx++] = c;
			}
			else if (board[r][c])
			{
				if (!flag)
				{
					stR[0] = r;
					stC[0] = c;
					stV[0] = board[r][c];
					flag = true;
				}
				else
				{
					stR[1] = r;
					stC[1] = c;
					stV[1] = board[r][c];
				}
			}
		}

	peopleNum = idx;
	dist[0].assign(idx, 0);
	dist[1].assign(idx, 0);
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < idx; j++)
		{
			dist[i][j] = abs(stR[i] - row[j]) + abs(stC[i] - col[j]);
		}
}

void calcAns(int n)
{
	int ret, idx, currCnt, temp;
	int len[2];
	int tempAns[2] = { 0,0 };

	TIME[0].clear();
	TIME[1].clear();

	for (int i = 0; i < peopleNum; i++)
	{
		if (n & (1 << i))
			TIME[1].push_back(dist[1][i]);
		else
			TIME[0].push_back(dist[0][i]);
	}
	len[0] = TIME[0].size();
	len[1] = TIME[1].size();
	sort(TIME[0].begin(), TIME[0].end());
	sort(TIME[1].begin(), TIME[1].end());

	for (int k = 0; k < 2; k++)
	{
		if (len[k] <= 0)
			tempAns[k] = 0;
		else if (len[k] <= 3)
		{
			tempAns[k] = TIME[k][len[k] - 1] + stV[k] + 1;
		}
		else
		{
			memset(use, false, sizeof(use));
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < stV[k]; j++)
				{
					use[i][TIME[k][i] + j] = true;
				}
			}
			for (int i = 3; i < len[k]; i++)
			{
				do {
					currCnt = 0;
					for (int j = i - 1; j >= 0; j--)
					{
						if (use[j][TIME[k][i]])
							currCnt++;
					}
					if (currCnt >= 3)
					{
						TIME[k][i]++;
					}
				} while (currCnt >= 3);

				for (int jj = 0; jj < stV[k]; jj++)
				{
					use[i][TIME[k][i] + jj] = true;
				}
			}
			tempAns[k] = 0;
			for (int i = 0; i < len[k]; i++)
				tempAns[k] = max(tempAns[k], TIME[k][i] + stV[k] + 1);
		}
	}

	ret = max(tempAns[0], tempAns[1]);
	answer = min(answer, ret);
}

void solve()
{
	for (int i = 0; i < (1 << peopleNum); i++)
	{
		calcAns(i);
	}
}

void output(int n)
{
	printf("#%d %d\n", n, answer);
}
