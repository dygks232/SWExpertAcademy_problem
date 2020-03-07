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

struct pos {
	int r, c;
	pos() { r = c = 0; }
	pos(int a, int b) { r = a; c = b; }
};

void inputAndInit();
void solve();
void output(int n);

bool isOutOfRange(int r, int c);
void dfs(int r, int c, int dist, bool dig);

int T, N, K, answer;

int board[8][8];
bool visit[8][8];
int dirR[4] = { -1,0,1,0 };
int dirC[4] = { 0,-1,0,1 };

vector<pos> start;

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

void dfs(int r, int c, int dist, bool dig)
{
	int nextR, nextC, temp;
	for (int dir = 0; dir < 4; dir++)
	{
		nextR = r + dirR[dir];
		nextC = c + dirC[dir];
		if (isOutOfRange(nextR, nextC) || visit[nextR][nextC])
			continue;
		if (dig)
		{
			if (board[r][c] <= board[nextR][nextC])
				continue;
			visit[nextR][nextC] = true;
			answer = max(answer, dist + 1);
			dfs(nextR, nextC, dist + 1, dig);
			visit[nextR][nextC] = false;
		}
		else
		{
			if (board[r][c] > board[nextR][nextC])
			{
				visit[nextR][nextC] = true;
				answer = max(answer, dist + 1);
				dfs(nextR, nextC, dist + 1, dig);
				visit[nextR][nextC] = false;
			}
			else
			{
				temp = board[nextR][nextC] - board[r][c] + 1;
				if (temp <= K)
				{
					board[nextR][nextC] -= temp;
					visit[nextR][nextC] = true;
					answer = max(answer, dist + 1);
					dfs(nextR, nextC, dist + 1, true);
					visit[nextR][nextC] = false;
					board[nextR][nextC] += temp;
				}
			}
		}
	}
}

void inputAndInit()
{
	int maxH = INT_MIN;
	scanf("%d %d", &N, &K);
	answer = INT_MIN;
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			scanf("%d", &board[r][c]);
			if (maxH < board[r][c])
			{
				start.clear();
				start.push_back(pos(r, c));
				maxH = board[r][c];
			}
			else if (maxH == board[r][c])
			{
				start.push_back(pos(r, c));
			}
		}
	}
}

void solve()
{
	for (int i = 0; i < start.size(); i++)
	{
		memset(visit, false, sizeof(visit));
		visit[start[i].r][start[i].c] = true;
		dfs(start[i].r, start[i].c, 1, false);
	}
}

void output(int n)
{
	printf("#%d %d\n", n, answer);
}
