#include <iostream>
#include <cmath>
using namespace std;

bool check(int num) 
{
	for (int i = 2; i < sqrt(num) + 1; i++)			//��������� �� �������� ��������� ���������
	{
		if (!(num % i)) return false;				//���� ������� ������ ����� ���������
	}
	return true;
}

int main() 
{
	int n, count = 0;
	cout << "Input count of numbers: ";
	cin >> n;
	for (int i = 1; n != count; i++)				//������� �����
	{
		if (check(i)) 
		{
			cout << i << endl;
			count++;
		}
	}
}