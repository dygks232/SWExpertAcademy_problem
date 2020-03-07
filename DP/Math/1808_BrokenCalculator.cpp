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

#define MAXN 1000000
#define WRONG 99999999

void inputAndInit();
void solve();
void output(int n);

void calcPrime();
int DP(int n);

int T, X, answer;

bool use[10];
bool prime[MAXN + 1];
int cache[MAXN + 1];

int main()
{
	scanf("%d", &T);
	calcPrime();
	for (int i = 1; i <= T; i++)
	{
		inputAndInit();
		solve();
		output(i);
	}
	return 0;
}

void calcPrime()
{
	for (int i = 0; i <= MAXN; i++)
		prime[i] = true;

	long long ii;
	for (int i = 2; i <= MAXN; i++)
	{
		if (prime[i])
		{
			ii = (long long)i * i;
			if (ii > MAXN)
				break;
			else
			{
				for (int j = ii; j <= MAXN; j += i)
				{
					prime[j] = false;
				}
			}
		}
	}
	prime[1] = false;
}

void inputAndInit()
{
	int in;
	memset(cache, -1, sizeof(cache));
	for (int i = 0; i < 10; i++)
	{
		scanf("%d", &in);
		use[i] = (bool)in;
	}
	scanf("%d", &X);
}

int DP(int n)
{
	int& ret = cache[n];
	if (ret != -1)
		return ret;

	string text;
	int len, root = sqrt(n), a, b, retA, retB;
	bool flag = false;
	vector<int> divisor;
	text = to_string(n);
	len = text.length();
	divisor.push_back(1);
	divisor.push_back(n);
	

	for (int i = 0; i < len; i++)
	{
		if (!use[text[i] - '0'])
		{
			flag = true;
			break;
		}
	}
	if (flag)
		ret = WRONG;
	else
	{
		ret = len;
		return ret;
	}

	if (prime[n])
	{
		return ret;
	}

	for (a = 2; a <= root; a++)
	{
		if (!(n % a))
		{
			b = n / a;
			retA = DP(a);
			retB = DP(b);
			if (retA != WRONG && retB != WRONG)
				ret = min(ret, retA + retB + 1);
		}
	}

	return ret;
}

void solve()
{
	answer = DP(X);
	if (answer != WRONG)
		answer++;
	else
		answer = -1;
}

void output(int n)
{
	printf("#%d %d\n", n, answer);
}
