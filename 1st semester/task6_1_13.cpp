#include <iostream>
using namespace std;

void f(int n)
{
	if (n == 0)
	{
		return;
	}
	f(n / 2);
	cout << n % 2;
}

int main() {
	int n;
	cout << "Input n: ";
	cin >> n;

	if (n == 0)
	{
		cout << "0";
	}
	else
	{
		f(n);
	}

	return 0;
}