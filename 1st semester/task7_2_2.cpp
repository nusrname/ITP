#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
using namespace std;

struct Hotel
{
	// ������� ��� �������� ���� ����������
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

// �������� ������������ ����
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

// ������ ������ ���� � �������� ������������
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

	cout << "������� ���������� ��������: ";
	cin >> count;

	for (int i = 0; i < count; i++)
	{
		cin.ignore();
		cout << "������� ��� �������: ";
		getline(cin, guest.fullName);

		// ���� � �������� ���� ��������
		cout << "������� ���� �������� (� ������� ��.��.����): ";
		cin >> arrivalInput;
		if (!parseDate(arrivalInput, guest.dateIn))
		{
			cerr << "������������ ������ ���� ��������!" << endl;
			return 1;
		}

		// ���� � �������� ���� �������
		cout << "������� ���� ������� (� ������� ����-��-��): ";
		cin >> departureInput;
		if (!parseDate(departureInput, guest.dateOut))
		{
			cerr << "������������ ������ ���� �������!" << endl;
			return 1;
		}

		// �������� ������������ ��������� ���
		if (mktime(&guest.dateIn) >= mktime(&guest.dateOut))
		{
			cerr << "���� ������� ������ ���� ����� ���� ��������!" << endl;
			return 1;
		}

		// ������ ���������� ���� ����������
		int days = guest.calculateDays();
		if (days < 0) {
			cerr << "������ ������� ���������� ����!" << endl;
			return 1;
		}
		cout << "������ " << guest.fullName << " �������� � ����� " << days << " ����." << endl;
	}

	return 0;
}
