// 2019/10/18 NYH
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<climits>
#include<stack>
#include<queue>
#include<deque>
#include<vector>
#include<set>
#include<map>
#include<string>
using namespace std;

#define MONTH_NUM 12

#define PAY_DAY 0
#define PAY_MONTH 1
#define PAY_3MONTHS 2
#define PAY_YEAR 3

void inputAndInit();
void init();
void solve();
void output(int nCase);

int calMinPayByDFS(int nMonth, int nPayMethod);

int nInputTestCase;
int nOutputResult;

vector<int> nVecPlan;
vector<int> nVecPay;

int main()
{
	cin >> nInputTestCase;
	for (int i = 1; i <= nInputTestCase; i++)
	{
		init();
		inputAndInit();
		solve();
		output(i);
	}
	return 0;
}

void init()
{
	nVecPlan.clear();
	nVecPlan.assign(12, 0);
	nVecPay.clear();
	nVecPay.assign(4, 0);
	nOutputResult = INT_MAX;
}

void inputAndInit()
{
	int nInput, i;
	for (i = 0; i < 4; i++)
	{
		cin >> nInput;
		nVecPay[i] = nInput;
	}
	for (i = 0; i < 12; i++)
	{
		cin >> nInput;
		nVecPlan[i] = nInput;
	}
}

int calMinPayByDFS(int nMonth, int nPayMethod)
{
	if (nMonth >= MONTH_NUM)
		return 0;
	int nRet = INT_MAX, nNextPayMethod;

	switch (nPayMethod)
	{
	case PAY_DAY:
		for (nNextPayMethod = 0; nNextPayMethod < 3; nNextPayMethod++)
		{
			nRet = min(nRet, nVecPlan[nMonth] * nVecPay[PAY_DAY] + calMinPayByDFS(nMonth + 1, nNextPayMethod));
		}
		break;
	case PAY_MONTH:
		for (nNextPayMethod = 0; nNextPayMethod < 3; nNextPayMethod++)
		{
			nRet = min(nRet, nVecPay[PAY_MONTH] + calMinPayByDFS(nMonth + 1, nNextPayMethod));
		}
		break;
	case PAY_3MONTHS:
		for (nNextPayMethod = 0; nNextPayMethod < 3; nNextPayMethod++)
		{
			nRet = min(nRet, nVecPay[PAY_3MONTHS] + calMinPayByDFS(nMonth + 3, nNextPayMethod));
		}
		break;
	case PAY_YEAR:
		nRet = nVecPay[PAY_YEAR];
		break;
	}

	return nRet;
}

void solve()
{
	for (int nPayMethod = 0; nPayMethod < 4; nPayMethod++)
	{
		nOutputResult = min(nOutputResult, calMinPayByDFS(0, nPayMethod));
	}
}

void output(int nCase)
{
	cout << "#" << nCase << " " << nOutputResult << "\n";
}