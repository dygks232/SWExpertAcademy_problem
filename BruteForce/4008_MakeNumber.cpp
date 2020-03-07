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

#define PLUS 0
#define MINUS 1
#define MUL 2
#define DIV 3

void inputAndInit();
void solve();
void output(int n);

int T, N, ansMax, ansMin;

vector<int> num;
vector<int> oper;

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
	int in, idx;
	scanf("%d", &N);
	num = vector<int>(N);
	oper = vector<int>(N - 1);
	idx = 0;
	ansMax = INT_MIN;
	ansMin = INT_MAX;
	for (int i = 0; i < 4; i++)
	{
		scanf("%d", &in);
		for (int j = 0; j < in; j++)
		{
			oper[idx++] = i;
		}
	}
	for (int i = 0; i < N; i++)
		scanf("%d", &num[i]);
}

void solve()
{
	do {
		int ret = num[0];
		for (int i = 0; i < N - 1; i++)
		{
			switch (oper[i])
			{
			case PLUS:
				ret += num[i + 1];
				break;
			case MINUS:
				ret -= num[i + 1];
				break;
			case MUL:
				ret *= num[i + 1];
				break;
			case DIV:
				ret /= num[i + 1];
				break;
			}
		}
		ansMax = max(ansMax, ret);
		ansMin = min(ansMin, ret);
	} while (next_permutation(oper.begin(), oper.end()));
}

void output(int n)
{
	printf("#%d %d\n", n, ansMax - ansMin);
}
