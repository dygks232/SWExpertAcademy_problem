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

int DP(int idx1, int idx2);

int T, N;
float answer;

string input1, input2;

int cache[501][501];

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
	cin >> N;
	cin >> input1 >> input2;
	memset(cache, -1, sizeof(cache));
	memset(cache, 0, sizeof(cache[0]));
	for (int r = 1; r <= N; r++)
		cache[r][0] = 0;
}

int DP(int idx1, int idx2)
{
	int& ret = cache[idx1][idx2];
	if (ret != -1)
		return ret;
	if (input1[idx1 - 1] != input2[idx2 - 1])
		ret = max(DP(idx1 - 1, idx2), DP(idx1, idx2 - 1));
	else
		ret = DP(idx1 - 1, idx2 - 1) + 1;
	return ret;
}

void solve()
{
	answer = 100.0f * DP(N, N) / (float)N;
}

void output(int n)
{
	printf("#%d %.2f\n", n, answer);
}
