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

void dfs(int curr, int num);

void makeLink();

int T, N, maxLen;

vector<pair<int, int> > bar;
vector<vector<int> > link;
vector<bool> use;
vector<int> answer, tempAns;

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

void makeLink()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (i != j && bar[i].second == bar[j].first)
				link[i].push_back(j);
		}
	}
}

void inputAndInit()
{
	int in1, in2;
	scanf("%d", &N);
	maxLen = 1;
	answer.clear();
	bar = vector<pair<int, int> >(N);
	link = vector<vector<int> >(N);
	use.assign(N, false);
	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &in1, &in2);
		bar[i] = make_pair(in1, in2);
	}
	makeLink();
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
		answer = tempAns;
		maxLen = num;
	}
}

void solve()
{
	for (int i = 0; i < N; i++)
	{
		use[i] = true;
		tempAns.push_back(i);
		dfs(i, 1);
		use[i] = false;
		tempAns.pop_back();
	}
}

void output(int n)
{
	printf("#%d ", n);
	if(maxLen > 1)
		for(int i = 0; i < maxLen; i++)
			printf("%d %d ", bar[answer[i]].first, bar[answer[i]].second);
	printf("\n");
}