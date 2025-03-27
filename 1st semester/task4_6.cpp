#include <iostream>
using namespace std;

int main()
{
	int a, b, count = 0;

	cout << "Input first number (a): ";
	cin >> a;
	cout << "Input second number (b): ";
	cin >> b;

	while (a >= b)
	{
		count++;
		a -= b;
	}
	cout << "Quotient: " << count << "\nRemainder of division: " << a;
}