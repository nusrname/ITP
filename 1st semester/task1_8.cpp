//задание 8
#include <iostream>
#include <cmath>
using namespace std;

double f(double x, double y)
{
	return sqrt((sqrt(cos(x) + sin(y)) + exp(x + y)) / (sqrt(x + y + log(x) * log(x))));						//вычисление значени€ функции при заданных ползователем параметрах
}

int main()
{
	setlocale(LC_ALL, "rus");

	double x, y;																								//создаЄм 2 параметра-переменные
	cout << "¬ведите x:";																						//пользовательский ввод переменных
	cin >> x;
	cout << "¬ведите y:";
	cin >> y;
																												//исключаем ошибку пользовательского ввода (суть ошибки на 24 строке)
	try
	{
		if (x <= 0)
			throw exception("„исло под логарифмом (x) должно быть больше 0");									//провер€ем корректность ввода и при возникновении ошибки переходим к 27 строке (блоку catch)
		cout << f(x, y) << endl;																				//если ввод корректен, выводим ответ (полученное значение из функции f), иначе эта строка не будет выполнена 
	}
	catch (const std::exception& ex)
	{
		cout << ex.what();																						//выводим сообщение об ошибке
	}

	return 0;
}