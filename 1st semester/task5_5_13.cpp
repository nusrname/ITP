#include <iostream>
using namespace std;

int main()
{
	int n, x;
	cout << "Input n and x: ";
	cin >> n >> x;
	int** arr = new int* [n];

	cout << "Input array: ";
	for (int i = 0; i < n; i++)
	{
		arr[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			cin >> arr[i][j];
		}
	}

	for (int i = 0; i < n; i ++)
	{
		for (int j = 0; j < n; j++)
		{
			if(arr[i][j] == x)
				for (int k = 0; k < n; k++)
				{
					arr[i][k] = 0;
				}
		}
	}


	cout << endl;

	for (int i = 0; i < n; i++)
	{
		if (arr[i][0] != 0)
		{
			for (int j = 0; j < n; j++)
			{
				cout << arr[i][j] << ' ';
			}
			cout << endl;
		}
	}


	for (int i = 0; i < n; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
}