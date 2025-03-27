#include <iostream>
using namespace std;

int main() 
{
	int n;
	cout << "Input n: ";
	cin >> n;
	int** arr = new int* [2 * n];
	int* str = new int[n];
	
	cout << "Input array: ";
	for (int i = 0; i < 2 * n; i++)
	{
		arr[i] = new int[n];
		if (i % 2 && i != 0)
			for (int j = 0; j < n; j++)
			{
				cin >> arr[i - 1][j];
				arr[i][j] = 10000;
			}
	}

	cout << "Input string: ";
	for (int j = 0; j < n; j++)
	{
		cin >> str[j];
	}

	for (int i = 0; i < 2 * n; i+= 2)
	{
		for (int j = 0; j < n; j++)
		{
			if (arr[i][j] < 1)
			{
				for (int k = 0; k < n; k++)
				{
					arr[i + 1][k] = str[k];
				}
				break;
			}
		}
	}

	cout << endl;
	for (int i = 0; i < 2 * n; i++)
	{
		if (arr[i][0] != 10000)
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
	delete[] str;
}