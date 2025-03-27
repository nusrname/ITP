#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;
#define q

struct Employee 
{
    string surname = "";
    string position = "";
    int day = 0, month = 0, year = 0;
    int experience = 0;
    int salary = 0;

#ifdef m
    bool operator<(const Employee& other)
    {
        if (salary == other.salary)
            return year < other.year;
        return salary < other.salary;
    }
#endif

#ifdef b
    bool operator<(const Employee& other)
    {
        if (position != other.position)
            return position > other.position;

        if (experience != other.experience)
            return experience > other.experience;

        return salary > other.salary;
    }
#endif
};

void quickSort(vector<Employee>& employees, int left, int right)
{
    int i = left, j = right;
    int pivot = employees[(left + right) / 2].salary;
    while (i <= j) 
    {
        while (employees[i].salary < pivot) i++;
        while (employees[j].salary > pivot) j--;
        if (i <= j) 
        {
            swap(employees[i], employees[j]);
            i++;
            j--;
        }
    }
    if (left < j) quickSort(employees, left, j);
    if (i < right) quickSort(employees, i, right);
}

#ifdef m
void merge(vector<Employee>& v, int left, int right, vector<Employee>& temp)
{
    if (left >= right) return;
    int mid = (left + right) / 2;
    merge(v, left, mid, temp);
    merge(v, mid + 1, right, temp);

    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right)
    {
        if (v[i] < v[j])
            temp[k++] = v[i++];
        else
            temp[k++] = v[j++];
    }

    while (i <= mid)
        temp[k++] = v[i++];

    while (j <= right)
        temp[k++] = v[j++];

    for (int i = left; i <= right; ++i)
        v[i] = temp[i];
}
#endif

#ifdef b
void bubbleSort(vector<Employee>& employees)
{
    int n = employees.size();
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (employees[j] < employees[j + 1])
            {
                swap(employees[j], employees[j + 1]);
            }
        }
    }
}
#endif

void readEmployees(const string& filename, vector<Employee>& employees)
{
    ifstream file(filename);
    if (!file)
    {
        cerr << "Ошибка открытия файла!" << endl;
        exit(1);
    }
    Employee emp;
    while (file >> emp.surname >> emp.position >> emp.day >> emp.month >> emp.year >> emp.experience >> emp.salary)
    {
        employees.push_back(emp);
    }
    file.close();
}

void writeEmployees(const string& filename, const vector<Employee>& employees)
{
    ofstream file(filename);
    if (!file)
    {
        cerr << "Ошибка открытия файла!" << endl;
        exit(1);
    }
    file << left << setw(15) << "Фамилия" << setw(15) << "Должность" << setw(10) << "Дата рождения" << setw(10) << "Стаж" << setw(10) << "Зарплата" << endl;
    file << string(60, '-') << endl;
    for (const auto& emp : employees) 
    {
        file << setw(15) << emp.surname
            << setw(15) << emp.position
            << setw(2) << emp.day << '.' << setw(2) << emp.month << '.' << emp.year << "  "
            << setw(10) << emp.experience
            << setw(10) << fixed << setprecision(2) << emp.salary << endl;
    }
    file.close();
}

int main()
{
    setlocale(LC_ALL, "rus");
    vector<Employee> employees;
    readEmployees("Test.txt", employees);

#ifdef q
    quickSort(employees, 0, employees.size() - 1);
#endif

#ifdef m
    vector<Employee> temp(employees.size());
    merge(employees, 0, employees.size() - 1, temp);
#endif

#ifdef b
    bubbleSort(employees);
#endif

    writeEmployees("sorted.txt", employees);
    cout << "Файл отсортирован и записан в sorted.txt" << endl;
    return 0;
}