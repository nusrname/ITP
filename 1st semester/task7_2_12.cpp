#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}

class fraction
{
	int integer{0};
	int numerator;
	int denominator;
	float Fl;
	

public:

	void ToFloat()
	{
		Fl = float(numerator) / float(denominator) + float(integer);
		cout << Fl << endl;
	}

	void ToInteger()
	{
		if (numerator >= denominator)
		{
			int t = numerator / denominator;
			integer += t;
			numerator -= denominator * t;
		}
	}

	fraction() 
	{
		string str;
		cout << "Введите дробь через / : ";
		cin >> str;

		istringstream iss(str);
		char slash;
		iss >> numerator >> slash >> denominator;
		
		if (denominator == 0)
			throw ("Делитель равен нулю!");

		ToInteger();

	}

	void print() 
	{
		if (integer == 0)
		{
			if (numerator == 0)
				cout << 0;
			else
				cout << numerator << "/" << denominator;
		}
		else if (numerator != 0)
			cout << integer << ' ' << numerator << "/" << denominator;
		else
			cout << integer;
		cout << endl;
	}

	void reducing() 
	{
		int g = gcd(this->denominator, this->numerator);
		this->numerator /= g;
		this->denominator /= g;
	}


	void operator+=(fraction a) 
	{
		this->integer += a.integer;
		if (this->denominator == a.denominator)
			this->numerator += a.numerator;
		else
		{
			int temp = this->denominator;
			this->denominator *= a.denominator;
			this->numerator *= a.denominator;
			a.numerator *= temp;
			this->numerator += a.numerator;

			reducing();
		}
		ToInteger();
		reducing();
	}

	void operator-=(fraction a) 
	{
		this->integer -= a.integer;
		if (this->denominator == a.denominator)
			this->numerator -= a.numerator;
		else
		{
			int temp = this->denominator;
			this->denominator *= a.denominator;
			this->numerator *= a.denominator;
			a.numerator *= temp;
			this->numerator -= a.numerator;

			int g = gcd(this->denominator, this->numerator);
			this->numerator /= g;
			this->denominator /= g;
		}
		ToInteger();
		reducing();
	}

	void operator*=(fraction a) 
	{
		this->denominator *= a.denominator;
		this->numerator += this->denominator * this->integer;
		a.numerator += a.denominator * a.integer;
		this->numerator *= a.numerator;

		ToInteger();
		reducing();
	}

	void operator/=(fraction a) 
	{
		if (a.numerator == 0)
			throw ("Втрая дробь равна нулю!");
		this->numerator += this->denominator * this->integer;
		a.numerator += a.denominator * a.integer;
		this->numerator *= a.denominator;
		this->denominator *= a.numerator;

		ToInteger();
		reducing();
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	try
	{
		fraction fr1, fr2;

		fr1.reducing();
		fr1.print();

		fr1 *= fr2;
		fr1.print();

		fr1 -= fr2;
		fr1.print();

		fr1 += fr2;
		fr1.print();

		fr1 /= fr2;
		fr1.print();

		fr1.ToFloat();
	}
	catch (const std::exception& ex)
	{
		cerr << ex.what();
	}

}