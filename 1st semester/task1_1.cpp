//задание 1
#include <iostream>
#include <cmath>
using namespace std;

double f(double x, double y)											
{
	return (exp((x * x + y * y) / 2) - y * x) / (2 * (x * x + y * y)) + log(x * x / (y * y));	//вычисляем значение выражения с заданными параметрами
}

int main()
{

	double x, y;																				//создаём 2 параметра-переменные								

	cout << "Enter x: " << endl;																//вводим переменные для функции
	cin >> x;
	cout << "Enter y: " << endl;
	cin >> y;

	cout << f(x, y) << endl;																	//вызываем функцию, принимающую вводимые пользователем параметры, сразу же выводим результат её работы

	return 0;
}