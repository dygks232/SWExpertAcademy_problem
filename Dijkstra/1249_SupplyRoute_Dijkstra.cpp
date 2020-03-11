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
void dijkstra();

int T, N, answer;

int dirR[4] = { -1,0,1,0 };
int dirC[4] = { 0,-1,0,1 };

int board[100][100];
int dist[100][100];

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

void inputAndInit()
{
	int in;
	scanf("%d", &N);
	answer = INT_MAX;
	for (int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
		{
			scanf("%1d", &in);
			board[r][c] = in;
			dist[r][c] = INT_MAX;
		}
}

void dijkstra()
{
	int currR, currC, nextR, nextC, currDist, nextDist;
	priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, greater<pair<int, pair<int, int> > > > PQ;
	PQ.push({ 0,{0,0} });
	dist[0][0] = 0;

	while (!PQ.empty())
	{
		currDist = PQ.top().first;
		currR = PQ.top().second.first;
		currC = PQ.top().second.second;
		PQ.pop();

		if (dist[currR][currC] < currDist)
			continue;

		for (int dir = 0; dir < 4; dir++)
		{
			nextR = currR + dirR[dir];
			nextC = currC + dirC[dir];			
			if (isOutOfRange(nextR, nextC))
				continue;
			nextDist = currDist + board[nextR][nextC];
			if (nextDist < dist[nextR][nextC])
			{
				dist[nextR][nextC] = nextDist;
				PQ.push({ nextDist,{nextR,nextC} });
			}
		}
	}
}

void solve()
{
	dijkstra();
	answer = dist[N - 1][N - 1];
}

void output(int n)
{
	printf("#%d %d\n", n, answer);
}
