#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
using namespace std;

struct Hotel
{
	// Функция для подсчета дней пребывания
	int calculateDays()
	{
		time_t arrival = mktime(const_cast<tm*>(&dateIn));
		time_t departure = mktime(const_cast<tm*>(&dateOut));
		if (arrival == -1 || departure == -1)
		{
			return -1;
		}
		double seconds = difftime(departure, arrival);
		return static_cast<int>(seconds / (60 * 60 * 24));
	}

	string fullName;
	tm dateIn{};
	tm dateOut{};
};

// Проверка корректности даты
bool isValidDate(int year, int month, int day)
{
	if (month < 1 || month > 12) return false;

	int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
	{
		daysInMonth[1] = 29;
	}

	return day > 0 && day <= daysInMonth[month - 1];
}

// Разбор строки даты и проверка корректности
bool parseDate(const std::string& dateStr, std::tm& date)
{
	int year, month, day;
	char delimiter1, delimiter2;

	std::istringstream ss(dateStr);
	ss >> day >> delimiter1 >> month >> delimiter2 >> year;

	if (ss.fail() || delimiter1 != '.' || delimiter2 != '.')
	{
		return false;
	}

	if (!isValidDate(year, month, day))
	{
		return false;
	}

	date = {};
	date.tm_year = year - 1900;
	date.tm_mon = month - 1;
	date.tm_mday = day;

	return true;
}

int main()
{
	setlocale(LC_ALL, "rus");
	Hotel guest;
	string arrivalInput, departureInput;
	int count;

	cout << "Введите количество туристов: ";
	cin >> count;

	for (int i = 0; i < count; i++)
	{
		cin.ignore();
		cout << "Введите ФИО туриста: ";
		getline(cin, guest.fullName);

		// Ввод и проверка даты прибытия
		cout << "Введите дату прибытия (в формате дд.мм.гггг): ";
		cin >> arrivalInput;
		if (!parseDate(arrivalInput, guest.dateIn))
		{
			cerr << "Некорректный формат даты прибытия!" << endl;
			return 1;
		}

		// Ввод и проверка даты отъезда
		cout << "Введите дату отъезда (в формате ГГГГ-ММ-ДД): ";
		cin >> departureInput;
		if (!parseDate(departureInput, guest.dateOut))
		{
			cerr << "Некорректный формат даты отъезда!" << endl;
			return 1;
		}

		// Проверка корректности диапазона дат
		if (mktime(&guest.dateIn) >= mktime(&guest.dateOut))
		{
			cerr << "Дата отъезда должна быть позже даты прибытия!" << endl;
			return 1;
		}

		// Расчет количества дней пребывания
		int days = guest.calculateDays();
		if (days < 0) {
			cerr << "Ошибка расчета количества дней!" << endl;
			return 1;
		}
		cout << "Турист " << guest.fullName << " проведет в отеле " << days << " дней." << endl;
	}

	return 0;
}
