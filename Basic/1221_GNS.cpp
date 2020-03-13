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

#define MAXN 10000

void inputAndInit();
void solve();
void output(int n);

int T, N;

int arr[MAXN];
char strToInt[10][5] = { "ZRO","ONE","TWO","THR","FOR","FIV","SIX","SVN","EGT","NIN" };

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
	char in[5];
	scanf("%s", in);
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%s", in);
		switch (in[0])
		{
		case 'Z': arr[i] = 0; break;
		case 'O': arr[i] = 1; break;
		case 'T': in[1] == 'W' ? arr[i] = 2 : arr[i] = 3; break;
		case 'F': in[1] == 'O' ? arr[i] = 4 : arr[i] = 5; break;
		case 'S': in[1] == 'I' ? arr[i] = 6 : arr[i] = 7; break;
		case 'E': arr[i] = 8; break;
		case 'N': arr[i] = 9; break;
		}
	}
}

void solve()
{
	sort(arr, arr + N);
}

void output(int n)
{
	printf("#%d ", n);
	for (int i = 0; i < N; i++)
		printf("%s ", strToInt[arr[i]]);
	printf("\n");
}
