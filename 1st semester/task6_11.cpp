#include <iostream>
using namespace std;

int main()
{
	int n;
	cout << "Input n: ";
	cin >> n;
	n++;
	int** arr = new int*[n + 1];

	for (int i = 1; i <= n; i++)
	{
		arr[i] = new int[i] {1};
	}

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			if (i > 2)
				arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
			if (j == i || j == 1)
				arr[i][j] = 1;
		}
	}

	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= n - i; j++)
		{
			cout << ' ';
		}
		for (int j = 1; j <= i; j++)
		{	
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < n; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
}