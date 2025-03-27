//������� 8
#include <iostream>
#include <cmath>
using namespace std;

double f(double x, double y)
{
	return sqrt((sqrt(cos(x) + sin(y)) + exp(x + y)) / (sqrt(x + y + log(x) * log(x))));						//���������� �������� ������� ��� �������� ������������ ����������
}

int main()
{
	setlocale(LC_ALL, "rus");

	double x, y;																								//������ 2 ���������-����������
	cout << "������� x:";																						//���������������� ���� ����������
	cin >> x;
	cout << "������� y:";
	cin >> y;
																												//��������� ������ ����������������� ����� (���� ������ �� 24 ������)
	try
	{
		if (x <= 0)
			throw exception("����� ��� ���������� (x) ������ ���� ������ 0");									//��������� ������������ ����� � ��� ������������� ������ ��������� � 27 ������ (����� catch)
		cout << f(x, y) << endl;																				//���� ���� ���������, ������� ����� (���������� �������� �� ������� f), ����� ��� ������ �� ����� ��������� 
	}
	catch (const std::exception& ex)
	{
		cout << ex.what();																						//������� ��������� �� ������
	}

	return 0;
}