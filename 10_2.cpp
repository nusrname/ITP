#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

struct Employee
{
    string surname, position;
    int day, month, year, experience, salary;
    bool isDeleted = false;

    Employee(string s, string p, int d, int m, int y, int exp, int sal) : surname(s), position(p), day(d), month(m), year(y), experience(exp), salary(sal) {}
    Employee() {}

    void print() const
    {
        cout << setw(15) << surname
            << setw(15) << position
            << setw(10) << day << '.' << setw(2) << month << '.' << year << "  "
            << setw(10) << experience
            << setw(10) << fixed << setprecision(2) << salary << endl;
    }
};

class HashTable 
{
    vector<Employee> table;
    int size;
    int count = 0;

    // Основная хэш-функция (по году, метод деления)
    int h(int year) const { return year % size; }

public:
    HashTable(int tableSize) : size(tableSize) { table.resize(size); }


    // Вставка сотрудника с линейным пробированием
    void insert(const Employee& emp)
    {
        int index = h(emp.year);
        int start = index;
        while (!table[index].surname.empty() && !table[index].isDeleted) 
        {
            index = (index + 1) % size;
            if (index == start)
            {
                cout << "Hash table is full!" << endl;
                return;
            }
        }
        table[index] = emp;
        table[index].isDeleted = false;
        count++;
    }

    // Поиск сотрудника по фамилии
    void search(const string& surname) const
    {
        for (int i = 0; i < size; ++i) 
        {
            if (!table[i].surname.empty() && !table[i].isDeleted && table[i].surname == surname)
            {
                cout << "Employee found at index " << i << ":" << endl;
                table[i].print();
                return;
            }
        }
        cout << "Employee not found." << endl;
    }

    // Вывод всей хеш-таблицы
    void display() const
    {
        for (int i = 0; i < size; ++i)
        {
            cout << setw(10) << i;
            if (!table[i].surname.empty() && !table[i].isDeleted) 
                table[i].print();
            else
                cout << "Empty" << endl;
        }
    }
};

Employee inputEmployee(bool find)
{
    string surname, position = "";
    int day, month, year, experience, salary;
    day = month = year = experience = 0;

    cout << "Enter surname: ";
    cin >> surname;
    if (!find)
    {
        cout << "Enter position: ";
        cin >> position;
        cout << "Enter birthdate (day month year): ";
        cin >> day >> month >> year;
        cout << "Enter years of experience: ";
        cin >> experience;
    }
    cout << "Enter salary: ";
    cin >> salary;
    return Employee(surname, position, day, month, year, experience, salary);
}

Employee inputEmployee(stringstream& s)
{
    string surname, position;
    int day, month, year, experience;
    double salary;

    s >> surname >> position >> day >> month >> year >> experience >> salary;

    return Employee(surname, position, day, month, year, experience, salary);
}

int main()
{
    int M;
    cout << "Enter size of table: ";
    cin >> M;
    HashTable ht(M);
    Employee emp;
    
    ifstream file("Test.txt");
    if (!file)
    {
        cout << "Unable to open file!" << endl;
        return 1;
    }

    string line;
    while (file >> ws && getline(file, line))
    {
        stringstream s(line);
        emp = inputEmployee(s);
        ht.insert(emp);
    }

    cout << "Hash Table:" << endl;
    ht.display();

    string searchName;
    cout << "Enter employee to search. ";
    cin >> searchName;
    ht.search(searchName);

    return 0;
}