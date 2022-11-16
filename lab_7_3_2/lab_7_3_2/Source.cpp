#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

void Create(int** y, const int n, const int Low, const int High, int i, int j)
{
	y[i][j] = Low + rand() % (High - Low + 1);

	if (j < n - 1)
		Create(y, n, Low, High, i, j + 1);
	else
		if (i < n - 1)
			Create(y, n, Low, High, i + 1, 0);
}

void Print(int** y, const int n, int i, int j)
{
	cout << setw(4) << y[i][j];
	if (j < n - 1)
		Print(y, n, i, j + 1);
	else
		if (i < n - 1)
		{
			cout << endl;
			Print(y, n, i + 1, 0);
		}
		else
			cout << endl << endl;
}

pair<int, int> Max(int** y, const int n, int top, int max, int i, int j, pair<int, int> result) {
	
	if (i < top && j == i) {
		j++;
	}
	if (y[i][j] > max) {
		max = y[i][j];
		result = { i,j };
	}

	if (j < n - 1) {
		Max(y, n, top, max, i, j + 1, result);
	}
	else {
		if (i < n - 1) {
			Max(y, n, top, max, i + 1, 0, result);
		}
		else
			return result;
	}
}

void Change(int** y, const int n, int max, int i, int j, pair<int, int> result, int top) {

	pair<int, int> indexMax = Max(y, n, top, max, i, j, result);

	int tmp;
	tmp = y[indexMax.first][indexMax.second];
	y[indexMax.first][indexMax.second] = y[top][top];
	y[top][top] = tmp;

	if (top < n - 1)
		Change(y, n, max, i,j, result, top+1);
}

int noPlus(int** y, const int n, int i, int j, int h)
{
	if (y[i][j] < 0)
		h++;

	if (j < n - 1) {
		noPlus(y, n, i, j + 1, h);
	}
	else {
		if (j == n)
			return i + 1;
		if (i < n - 1) {
			noPlus(y, n, i + 1, 0, h);
		}
		else 
			return -1;
	}
}

int main()
{
	srand((unsigned)time(NULL));
	int Low = -30;
	int High = 5;
	int n = 5;
	int** y = new int* [n];
	for (int i = 0; i < n; i++)
		y[i] = new int[n];
	int max = -123;
	pair<int, int> result = { 0, 0 };
	Create(y, n, Low, High, 0, 0);
	Print(y, n, 0, 0);
	cout << noPlus(y, n, 0, 0, 0) << endl;
	Change(y, n, max, 0, 0, result, 0);
	Print(y, n, 0, 0);
	cout << noPlus(y, n, 0, 0, 0) << endl;
	for (int i = 0; i < n; i++)
		delete[] y[i];
	delete[] y;
	return 0;
}
