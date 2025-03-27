//#2
//Дано трехзначное число 𝐴 и однозначное число 𝑋. Если все цифры числа 𝐴
//больше 𝑋, уменьшить число 𝐴 на 100; если первая и вторая цифры числа 𝐴
//больше 𝑋, увеличить число 𝐴 на 100; если все цифры числа 𝐴 меньше 𝑋,
//уменьшить число 𝐴 на 50; если вторая и третья цифры числа 𝐴 меньше 𝑋,
//увеличить число 𝐴 на 50; в остальных случаях — увеличить число 𝐴 на 10.

#include<iostream>
using namespace std;

int main()
{
	int a, x;
	cout << "Input a: ";
	cin >> a;
	cout << "Input x: ";
	cin	>> x;
	try
	{
		if (a > 1000 || a < 99)
			throw exception("99 < A < 1000");
		if (x > 9 || x < 1)
			throw exception("0 < x < 10");
		bool condition[3] = { a / 100 > x, a / 10 % 10 > x,  a % 10 > x };
		if (condition[0] && condition[1])
			if (condition[2]) a -= 100;
			else a += 100;
		else if (!condition[1] && !condition[2])
			if (!condition[0]) a -= 50;
			else a += 50;
		else a += 10;
		cout << a;
	}
	catch (const std::exception& ex)
	{
		cerr << ex.what();
	}
	
}