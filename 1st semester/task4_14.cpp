#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	double a, b, h;
	cout << "Input parameters a and b and h: ";
	cin >> a >> b >> h;

	for (double x = a; x <= b; x += h)
	{
		try
		{
			if (x == 1)
				throw exception("\tLogarithm of a non-positive number");
			else if (x < 1 && x >= -1)
				throw exception("\tRoot of a negative number and logarithm of a non-positive number");
			else if (x < 1)
				throw exception("\tRoot of a negative number");
			else if (x == 2)
				throw exception("\tDivision by zero");

			cout << "x = " << x << "\tf(x) = " << log(x * x - 1) / (1 - sqrt(x - 1)) << endl;
		}
		catch (const exception& ex)
		{
			cerr << "x = " << x << ex.what() << endl;
		}
	}

}