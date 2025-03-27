#include <iostream>
using namespace std;

double f(int n, double x)
{
	if (n == 0) return 1;
	if (n == 1) return 2 * x;
	return 2 * x * f(n - 1, x) - 2 * (n - 1) * f(n - 2, x);
}

double p(int n, double x)
{
    if (n == 0)
    {
        return 1;
    }
    else if (n == 1) 
    {
        return 2 * x; 
    }

    double H_prev2 = 1, H_prev1 = 2 * x, H_current = 0;

    for (int i = 2; i <= n; ++i) 
    {
        H_current = 2 * x * H_prev1 - 2 * (i - 1) * H_prev2;
        H_prev2 = H_prev1;
        H_prev1 = H_current;
    }

    return H_current;
}

int main() 
{
	int n;
	double x;
	cout << "Input n and x: ";
	cin >> n >> x;

    cout << f(n, x) << endl << p(n, x);
}