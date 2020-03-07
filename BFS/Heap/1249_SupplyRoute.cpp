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
void bfs(int r, int c, int val);

int T, N, answer;

int dirR[4] = { -1,0,1,0 };
int dirC[4] = { 0,-1,0,1 };

int board[100][100];
bool visit[100][100];

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

void bfs(int r, int c, int val)
{
	priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int> > >, greater<pair<int, pair<int, int> > > > PQ;
	int currR, currC, nextR, nextC, currDist;
	PQ.push({ 0,{0,0} });
	visit[0][0] = true;

	while (!PQ.empty())
	{
		currR = PQ.top().second.first;
		currC = PQ.top().second.second;
		currDist = PQ.top().first;
		PQ.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			nextR = currR + dirR[dir];
			nextC = currC + dirC[dir];
			if (isOutOfRange(nextR, nextC) || visit[nextR][nextC])
				continue;
			if (nextR == N - 1 && nextC == N - 1)
			{
				answer = currDist;
				return;
			}
			visit[nextR][nextC] = true;
			PQ.push({ currDist + board[nextR][nextC],{nextR,nextC} });
		}
	}
}

void inputAndInit()
{
	int in;
	scanf("%d", &N);
	answer = INT_MAX;
	for(int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
		{
			scanf("%1d", &in);
			board[r][c] = in;
			visit[r][c] = false;
		}
}

void solve()
{
	visit[0][0] = true;
	bfs(0, 0, 0);
}

void output(int n)
{
	printf("#%d %d\n", n, answer);
}
