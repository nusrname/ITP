#include <iostream>
using namespace std;

int main() 
{
	int count;
	cout << "Input count of layers: ";
	cin >> count;
	for (int i = 1; i <= count; i++)
	{
		for (int j = i; j >= 1; j--)
		{
			cout << j << ' ';
		}
		cout << endl;
		for (int j = i; j >= 1; j--)
		{
			cout << j * 2 << ' ';
		}
		cout << endl;
	}
}