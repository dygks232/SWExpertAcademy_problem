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

void makeDir();
bool isOutOfRange(int r, int c);
void bfs(int r, int c);
bool isLink(int idx, int dir);

int T, R, C, startR, startC, L, answer;

int board[50][50];
bool visit[50][50];

int dirR[4] = { -1,0,1,0 };
int dirC[4] = { 0,-1,0,1 };
vector<int> dirList[8];

int main()
{
	scanf("%d", &T);
	makeDir();
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
	return r < 0 || c < 0 || r >= R || c >= C;
}

void makeDir()
{
	int arr1[] = { 0,1,2,3 };
	int arr2[] = { 0,2 };
	int arr3[] = { 1,3 };
	int arr4[] = { 0,3 };
	int arr5[] = { 2,3 };
	int arr6[] = { 1,2 };
	int arr7[] = { 0,1 };
	dirList[1].assign(arr1, arr1 + 4);
	dirList[2].assign(arr2, arr2 + 2);
	dirList[3].assign(arr3, arr3 + 2);
	dirList[4].assign(arr4, arr4 + 2);
	dirList[5].assign(arr5, arr5 + 2);
	dirList[6].assign(arr6, arr6 + 2);
	dirList[7].assign(arr7, arr7 + 2);
}

void inputAndInit()
{
	scanf("%d %d %d %d %d", &R, &C, &startR, &startC, &L);
	memset(visit, false, sizeof(visit));
	answer = 1;
	for (int r = 0; r < R; r++)
	{
		for (int c = 0; c < C; c++)
		{
			scanf("%d", &board[r][c]);
		}
	}
}

bool isLink(int idx, int dir)
{
	for (int i = 0; i < dirList[idx].size(); i++)
	{
		if (dirList[idx][i] == dir)
			return true;
	}
	return false;
}

void bfs(int r, int c)
{
	int currR, currC, nextR, nextC, currDist, currIdx;
	queue<pair<int, pair<int, int> > > Q;
	visit[r][c] = true;
	Q.push({ 1,{r,c} });

	while (!Q.empty())
	{
		currR = Q.front().second.first;
		currC = Q.front().second.second;
		currDist = Q.front().first;
		currIdx = board[currR][currC];
		Q.pop();
		if (currDist == L)
			return;

		for (int d = 0; d < dirList[currIdx].size(); d++)
		{
			nextR = currR + dirR[dirList[currIdx][d]];
			nextC = currC + dirC[dirList[currIdx][d]];
			if (isOutOfRange(nextR, nextC) || visit[nextR][nextC] || !board[nextR][nextC])
				continue;
			if (!isLink(board[nextR][nextC], (dirList[currIdx][d] + 2) % 4))
				continue;
			visit[nextR][nextC] = true;
			answer++;
			Q.push({ currDist + 1,{nextR,nextC} });
		}
	}
}

void solve()
{
	bfs(startR, startC);
}

void output(int n)
{
	printf("#%d %d\n", n, answer);
}
