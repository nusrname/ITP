#include <iostream>
using namespace std;

int main()
{
	int n;
	cout << "Input n: ";
	cin >> n;
	int** arr = new int* [n];
	bool flag;

	cout << "Input array: ";
	for (int i = 0; i < n; i++)
	{
		arr[i] = new int[2 * n];
		for (int j = 0; j < 2 * n; j += 2)
		{
			cin >> arr[i][j];
			arr[i][j + 1] = 10000;
		}
	}

	for (int j = 0; j < 2 * n; j += 2)
	{
		flag = true;
		for (int i = 0; i < n; i++)
		{
			if (arr[i][j] % 2)
			{
				flag = !flag;
				break;
			}
		}
		if (flag)
			for (int k = 0; k < n; k++)
			{
				arr[k][j + 1] = arr[k][j];
			}
	}

	cout << endl;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 2 * n; j++)
		{
			if (arr[i][j] != 10000)
			cout << arr[i][j] << ' ';
		}
		cout << endl;
	}


	for (int i = 0; i < n; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
}