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

void makeLCP();
void calcAnswer();

int T, K;
string input, answer;

map<string, int> suffixArr;
int LCP[401];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> T;
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
	int len;
	cin >> K;
	cin >> input;
	len = input.length();
	suffixArr.clear();
	for (int i = 0; i < len; i++)
		suffixArr.insert({ input.substr(i),i });
	makeLCP();
}

void makeLCP()
{
	map<string, int>::iterator it1, it2;
	int idx = 1, len;
	LCP[0] = 0;
	it1 = suffixArr.begin();
	it1++;
	for (it2 = suffixArr.begin(); it1 != suffixArr.end(); it1++, it2++, idx++)
	{
		len = min((it1->first).length(), (it2->first).length());
		for (int i = 0; i < len; i++)
		{
			if ((it1->first)[i] != (it2->first)[i])
			{
				LCP[idx] = i;
				break;
			}
			if (i == len - 1)
			{
				LCP[idx] = len;
				break;
			}
		}
	}
}

void calcAnswer()
{
	int kth, idx = 1;
	map<string, int>::iterator it1, it2;
	it1 = suffixArr.begin();
	if (K <= (kth = (it1->first).length()))
	{
		answer = (it1->first).substr(0, K);
		return;
	}
	it1++;
	for (it2 = suffixArr.begin(); it1 != suffixArr.end(); it1++, it2++, idx++)
	{
		if ((it1->first)[0] == (it2->first)[0])
		{
			if (kth + (it1->first).length() - LCP[idx] < K)
			{
				kth += (it1->first).length() - LCP[idx];
				continue;
			}
			else
			{
				answer = (it1->first).substr(0, K - kth + LCP[idx]);
				return;
			}
		}
		else
		{
			if (kth + (it1->first).length() < K)
			{
				kth += (it1->first).length();
				continue;
			}
			else
			{
				answer = (it1->first).substr(0, K - kth);
				return;
			}
		}
	}
	answer = "none";
}

void solve()
{
	calcAnswer();
}

void output(int n)
{
	printf("#%d %s\n", n, answer.c_str());
}