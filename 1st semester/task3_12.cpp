//#12
//ƒаны день, мес€ц и год.ѕроверить корректность ввода данных.Ќе использовать
//библиотеку time.¬ывести дату в виде Ђ23 ма€ 1978 года.ї.ќпределить сколько
//дней осталось до конца мес€ца.
#include<iostream>
using namespace std;

void date(int d, int m, int y)
{
	int months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	
	string monthsStr[] = { "€нвар€", "феврал€" ,  "марта" , "апрел€", "ма€" , "июн€" , "июл€" , "августа" , "сент€бр€"  ,"окт€бр€" , "но€бр€" , "декабр€" };

	try
	{
		if (m < 1 || m > 12) throw exception("неправильный мес€ц");
		else if (((y % 400 == 0 || y % 100 != 0 && y % 4 == 0) && m == 2 && (d > 29 || d < 1)) || ((y % 400 != 0 && y % 4 != 0) && m == 2 && (d > 28 || d < 1)) || (d < 1 || d > months[m - 1]))throw exception("неправильный день");

		cout << d << " " << monthsStr[m - 1] << " " << y << " года\t осталось дней: ";
		if ((y % 400 == 0 || y % 100 != 0 && y % 4 == 0) && m == 2)
			cout << 29 - d;
		else
			cout << months[m - 1] - d;
	}
	catch (const std::exception& ex)
	{
		cout << ex.what();
	}
}

int main() 
{
	setlocale(LC_ALL, "rus");
	int d, m, y;
	cout << "Input dd mm yyyy: ";
	cin >> d >> m >> y;
	date(d, m, y);
	
}