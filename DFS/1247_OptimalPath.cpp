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

#define TESTCASE 10

void inputAndInit();
void solve();
void output(int n);

void dfs(int curr);
bool isAllVisit();
int dist(int idx1, int idx2);

int answer, N, tempAns;

vector<pair<int, int> > input;
vector<bool> visit;

int main()
{
	int i;
	cin >> i;
	for (i = 1; i <= TESTCASE; i++)
	{
		inputAndInit();
		solve();
		output(i);
	}
	return 0;
}

bool isAllVisit()
{
	for(int i = 0; i < N; i++)
		if (!visit[i])
			return false;
	return true;
}

void dfs(int curr)
{
	if (!isAllVisit())
	{
		for (int i = 1; i <= N; i++)
		{
			if (!visit[i - 1])
			{
				tempAns += abs(input[i].first - input[curr].first) + abs(input[i].second - input[curr].second);
				if (tempAns > answer)
				{
					tempAns -= abs(input[i].first - input[curr].first) + abs(input[i].second - input[curr].second);
					continue;
				}
				visit[i - 1] = true;
				dfs(i);
				visit[i - 1] = false;
				tempAns -= abs(input[i].first - input[curr].first) + abs(input[i].second - input[curr].second);
			}
		}
	}
	else
	{
		tempAns += abs(input[N + 1].first - input[curr].first) + abs(input[N + 1].second - input[curr].second);
		answer = min(tempAns, answer);
		tempAns -= abs(input[N + 1].first - input[curr].first) + abs(input[N + 1].second - input[curr].second);
		return;
	}
}

void inputAndInit()
{
	cin >> N;
	input = vector<pair<int, int> >(N + 2);
	visit.assign(N, false);
	answer = 0;
	tempAns = 0;
	cin >> input[0].first >> input[0].second >> input[N + 1].first >> input[N + 1].second;
	for (int i = 1; i < N + 1; i++)
	{
		cin >> input[i].first >> input[i].second;
		if (i)
			answer += dist(i - 1, i);
	}
	answer += dist(N, N + 1);
}

int dist(int idx1, int idx2)
{
	return abs(input[idx1].first - input[idx2].first) + abs(input[idx1].second - input[idx2].second);
}

void solve()
{
	dfs(0);
}

void output(int n)
{
	printf("#%d %d\n", n, answer);
}
