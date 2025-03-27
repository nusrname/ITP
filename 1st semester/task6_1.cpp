#include <iostream>
using namespace std;

int main()
{
	int n;
	cout << "Input n: ";
	cin >> n;
	n++;
	int* arr = new int[n];

	cout << "Input array: ";
	for (int i = 0; i < n; i++)
	{	
		cin >> arr[i];
	}
	
	for (int i = 1; i < n; i++)
	{
		cout << arr[i] * i << ", ";
	}

	delete[] arr;
}