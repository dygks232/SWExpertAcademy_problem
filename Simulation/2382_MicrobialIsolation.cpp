// 2019/10/17 NYH
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

void inputAndInit();
void init();
void solve();
void output(int nCase);

void mapInit();
void moveMicro();
bool isBoundary(int nRow, int nCol);
int calMicroNum();

int nInputTestCase, nInputMapLen, nInputResultTime, nInputMicroNum;
int nMapSize;
int nOutputResult;

int nDirR[4] = { -1,1,0,0 };
int nDirC[4] = { 0,0,-1,1 };

struct micro
{
	int row;
	int col;
	int num;
	int dir;
	micro()
	{
		row = 0;
		col = 0;
		num = 0;
		dir = 0;
	}
	void input(int r, int c, int n, int d)
	{
		row = r;
		col = c;
		num = n;
		dir = d;
	}
};

vector<int> nVecMicroNum;
vector<int> nVecOverlapMapIndex;
vector<int> nVecOverlapMicroIndex;
vector<micro> stVecMicroInfo;
vector<micro> stVecMicroInfoClone;

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

int calMicroNum()
{
	int nRet = 0, nCurrMicroNum;
	nCurrMicroNum = stVecMicroInfo.size();
	for (int i = 0; i < nCurrMicroNum; i++)
	{
		nRet += stVecMicroInfo[i].num;
	}
	return nRet;
}

bool isBoundary(int nRow, int nCol)
{
	return nRow == 0 || nCol == 0 || nRow == nInputMapLen - 1 || nCol == nInputMapLen - 1;
}

void mapInit()
{
	nVecMicroNum.clear();
	nVecMicroNum.assign(nMapSize, 0);
	nVecOverlapMapIndex.clear();
	stVecMicroInfoClone.clear();
	stVecMicroInfoClone.assign(stVecMicroInfo.begin(), stVecMicroInfo.end());
}

void moveMicro()
{
	int nCurrRow, nCurrCol, nCurrMicroNum, nCurrDir, nNextRow, nNextCol, nCurrIndex, nNextIndex;
	int i, j;
	int nMaxNum, nMaxIndex, nSum;
	micro stNextMicro;

	nCurrMicroNum = stVecMicroInfoClone.size();

	for (i = 0; i < nCurrMicroNum; i++)
	{
		if (!stVecMicroInfo[i].num)
			continue;
		nCurrDir = stVecMicroInfo[i].dir;
		nCurrRow = stVecMicroInfo[i].row;
		nCurrCol = stVecMicroInfo[i].col;
		nNextRow = nCurrRow + nDirR[nCurrDir];
		nNextCol = nCurrCol + nDirC[nCurrDir];
		nNextIndex = nNextRow * nInputMapLen + nNextCol;
		if (isBoundary(nNextRow, nNextCol))
		{
			if (nCurrDir < 2)
				stNextMicro.input(nNextRow, nNextCol, stVecMicroInfo[i].num / 2, (nCurrDir + 1) % 2);
			else
				stNextMicro.input(nNextRow, nNextCol, stVecMicroInfo[i].num / 2, (nCurrDir + 1) % 2 + 2);
		}
		else
		{
			nVecMicroNum[nNextIndex]++;
			stNextMicro.input(nNextRow, nNextCol, stVecMicroInfo[i].num, nCurrDir);
		}
		stVecMicroInfoClone[i] = stNextMicro;
	}

	for (i = 0; i < nMapSize; i++)
	{
		if (nVecMicroNum[i] > 1)
			nVecOverlapMapIndex.push_back(i);
	}

	for (i = 0; i < nVecOverlapMapIndex.size(); i++)
	{
		nMaxNum = INT_MIN;
		nSum = 0;
		nVecOverlapMicroIndex.clear();
		for (j = 0; j < nCurrMicroNum; j++)
		{
			nCurrIndex = stVecMicroInfoClone[j].row * nInputMapLen + stVecMicroInfoClone[j].col;
			if (nCurrIndex != nVecOverlapMapIndex[i])
				continue;

			nSum += stVecMicroInfoClone[j].num;
			nVecOverlapMicroIndex.push_back(j);
			if (nMaxNum < stVecMicroInfoClone[j].num)
			{
				nMaxNum = stVecMicroInfoClone[j].num;
				nMaxIndex = j;
			}
		}
		for (j = 0; j < nVecOverlapMicroIndex.size(); j++)
		{
			if (nVecOverlapMicroIndex[j] == nMaxIndex)
			{
				stVecMicroInfoClone[nVecOverlapMicroIndex[j]].num = nSum;
			}
			else
			{
				stVecMicroInfoClone[nVecOverlapMicroIndex[j]].num = 0;
			}
		}
	}

}

void init()
{
	stVecMicroInfo.clear();
}

void inputAndInit()
{
	int nRow, nCol, nNum, nDir;
	micro stInput;
	cin >> nInputMapLen >> nInputResultTime >> nInputMicroNum;
	stVecMicroInfo.assign(nInputMicroNum, micro());
	nMapSize = nInputMapLen * nInputMapLen;
	for (int i = 0; i < nInputMicroNum; i++)
	{
		cin >> nRow >> nCol >> nNum >> nDir;
		stInput.input(nRow, nCol, nNum, nDir - 1);
		stVecMicroInfo[i] = stInput;
	}
}

void solve()
{
	for (int nTime = 0; nTime < nInputResultTime; nTime++)
	{
		mapInit();
		moveMicro();
		stVecMicroInfo.clear();
		stVecMicroInfo.assign(stVecMicroInfoClone.begin(), stVecMicroInfoClone.end());
	}
	nOutputResult = calMicroNum();
}

void output(int nCase)
{
	cout << "#" << nCase << " " << nOutputResult << "\n";
}
