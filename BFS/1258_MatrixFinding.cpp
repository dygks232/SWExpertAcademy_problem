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

void bfs(int r, int c);
bool isOutOfRange(int r, int c);
bool comp(pair<int, int> a, pair<int, int> b);

int T, N;

int dirR[4] = { -1,0,1,0 };
int dirC[4] = { 0,-1,0,1 };

int board[100][100];
bool visit[100][100];

vector<pair<int, int> > mat;

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
	scanf("%d", &N);
	memset(visit, false, sizeof(visit));
	mat.clear();
	for (int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
			scanf("%d", &board[r][c]);
}

void bfs(int r, int c)
{
	queue<pair<int, int> > Q;
	int currR, currC, nextR, nextC, endR, endC;
	visit[r][c] = true;
	Q.push({ r,c });

	while (!Q.empty())
	{
		endR = currR = Q.front().first;
		endC = currC = Q.front().second;
		Q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			nextR = currR + dirR[dir];
			nextC = currC + dirC[dir];
			if (isOutOfRange(nextR, nextC) || visit[nextR][nextC] || !board[nextR][nextC])
				continue;
			visit[nextR][nextC] = true;
			Q.push({ nextR,nextC });
		}
	}
	mat.push_back({ endR - r + 1,endC - c + 1 });
}

bool comp(pair<int, int> a, pair<int, int> b)
{
	int sizeA = a.first * a.second;
	int sizeB = b.first * b.second;
	if (sizeA < sizeB)
		return true;
	else if (sizeA == sizeB)
	{
		if (a.first < b.first)
			return true;
		return false;
	}
	return false;
}

void solve()
{
	for (int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
			if (board[r][c] && !visit[r][c])
				bfs(r, c);
	sort(mat.begin(), mat.end(), comp);
}

void output(int n)
{
	int len = mat.size();
	printf("#%d %d ", n, len);
	for (int i = 0; i < len; i++)
		printf("%d %d ", mat[i].first, mat[i].second);
	printf("\n");
}
