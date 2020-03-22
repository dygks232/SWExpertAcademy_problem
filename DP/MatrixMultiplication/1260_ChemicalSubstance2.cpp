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
void makeLink();
void dfs(int curr, int num);
int DP(int i, int j);
void calcMat();
void sortMat();

int T, N, maxLen, matNum, answer;

int dirR[4] = { -1,0,1,0 };
int dirC[4] = { 0,-1,0,1 };

int board[100][100];
bool visit[100][100];
int cache[21][21];

vector<pair<int, int> > mat;
vector<vector<int> > link;
vector<bool> use;
vector<int> preAns, postAns, tempAns;

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
	memset(cache, -1, sizeof(cache));
	preAns.clear();
	mat.clear();
	maxLen = 1;
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
	int sizeA, sizeB;
	if ((sizeA = a.first * a.second) < (sizeB = b.first * b.second))
		return true;
	else if (sizeA == sizeB)
	{
		if (a.first < b.first)
			return true;
		return false;
	}
	return false;
}

void makeLink()
{
	matNum = mat.size();
	link = vector<vector<int> >(matNum);
	use.assign(matNum, false);
	for (int i = 0; i < matNum; i++)
	{
		for (int j = 0; j < matNum; j++)
		{
			if (i != j && mat[i].second == mat[j].first)
				link[i].push_back(j);
		}
	}
}

void dfs(int curr, int num)
{
	int len = link[curr].size();
	for (int i = 0; i < len; i++)
	{
		if (use[link[curr][i]])
			continue;
		use[link[curr][i]] = true;
		tempAns.push_back(link[curr][i]);
		dfs(link[curr][i], num + 1);
		use[link[curr][i]] = false;
		tempAns.pop_back();
	}
	if (maxLen < num)
	{
		preAns = tempAns;
		maxLen = num;
	}
}

int DP(int i, int j)
{
	int minV = INT_MAX;
	int& ret = cache[i][j];
	if (ret != -1)
		return ret;
	if (i == j)
	{
		ret = 0;
		return ret;
	}
	for (int k = i; k < j; k++)
	{
		minV = min(minV, DP(i, k) + DP(k + 1, j) + postAns[i - 1] * postAns[k] * postAns[j]);
	}
	return ret = minV;
}

void calcMat()
{
	for (int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
			if (board[r][c] && !visit[r][c])
				bfs(r, c);
}

void sortMat()
{
	for (int i = 0; i < matNum; i++)
	{
		use[i] = true;
		tempAns.push_back(i);
		dfs(i, 1);
		use[i] = false;
		tempAns.pop_back();
	}
	postAns = vector<int>(maxLen + 1);
	postAns[0] = mat[preAns[0]].first;
	for (int i = 1; i < maxLen + 1; i++)
		postAns[i] = mat[preAns[i - 1]].second;
}

void solve()
{
	calcMat();
	makeLink();
	sortMat();
	answer = DP(1, maxLen);
}

void output(int n)
{
	printf("#%d %d\n", n, answer);
}
