#include <iostream>
using namespace std;

long long fact(long long n) 
{
	if (n < 2) return 1;
	return fact(n - 1) * n;
}

long long f(int n) {
	long long result = 1;
	for (int i = 1; i <= n; ++i) {
		result *= i;
	}
	return result;
}

int main()
{
	int n;
	cout << "Input {n}!: ";
	cin >> n;

	cout << fact(n) << endl << f(n);
}