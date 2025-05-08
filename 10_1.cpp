#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
using namespace std;

struct Employee
{
	string surname = "", position = "";
	int day = 0, month = 0, year = 0, experience = 0, salary = 0;

	Employee(string s, string p, int d, int m, int y, int exp, int sal) : surname(s), position(p), day(d), month(m), year(y), experience(exp), salary(sal) {}
	Employee() {}

	void print()
	{
		cout << setw(15) << surname
			<< setw(15) << position
			<< setw(10) << day << '.' << setw(2) << month << '.' << year << "  "
			<< setw(10) << experience
			<< setw(10) << fixed << setprecision(2) << salary << endl;
	}
};

class List
{
public:

	struct Node
	{
		Employee data;
		Node* prev;
		Node* next;
		Node(Employee value) : data(value), prev(nullptr), next(nullptr) {}
	};

	Node* head;
	Node* tail;

	List() : head(nullptr), tail(nullptr) {}

	~List()
	{
		while (head)
		{
			Node* temp = head;
			head = head->next;
			delete temp;
		}
	}

	void push(Employee value)
	{
		Node* newNode = new Node(value);
		if (!head)
			head = tail = newNode;
		else
		{
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
	}

	void print() const
	{
		Node* current = head;
		while (current != nullptr)
		{
			current->data.print();
			current = current->next;
		}
	}

	void remove(const string& surname)
	{
		Node* current = head;
		while (current)
		{
			if (current->data.surname == surname)
			{
				if (current->prev)
					current->prev->next = current->next;
				else
					head = current->next;

				if (current->next)
					current->next->prev = current->prev;
				else
					tail = current->prev;

				delete current;
				break;
			}
			current = current->next;
		}
	}

	bool contains(const string& surname) const
	{
		Node* current = head;
		while (current)
		{
			if (current->data.surname == surname)
				return true;
			current = current->next;
		}
		return false;
	}
};

class HashTable
{
	vector<List> table;  // Хеш-таблица, где каждый элемент - это указатель на начало списка
	int size;

	int h(int salary) { return static_cast<int>(salary) % size; }

public:
	HashTable(int table_size) : size(table_size) { table.resize(size); }

	// Вставка сотрудника в хеш-таблицу
	void insert(const Employee& emp)
	{
		int index = h(emp.salary);
		table[index].push(emp);
	}

	// Поиск сотрудника по фамилии
	void search(const Employee& emp)
	{
		int index = h(emp.salary);
		if (table[index].contains(emp.surname))
		{
			cout << "Employee found in bucket " << index << endl;
			table[index].print();
			return;
		}
		cout << "Employee not found." << endl;
	}

	// Удаление всех сотрудников с данной фамилией
	void remove(const Employee& emp)
	{
		int index = h(emp.salary);
		if (table[index].contains(emp.surname))
		{
			table[index].remove(emp.surname);
			cout << "Employee " << emp.surname << " removed." << endl;
			return;
		}
		cout << "Employee not found to remove." << endl;
	}

	// Вывод всей хеш-таблицы
	void display() const
	{
		for (int i = 0; i < size; ++i)
		{
			cout << "Bucket " << i << ":\n";
			table[i].print();
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

	cout << "Enter new employee. ";
	emp = inputEmployee(false);
	ht.insert(emp);
	ht.display();

	cout << "Enter employee to search. ";
	emp = inputEmployee(true);
	ht.search(emp);

	cout << "Enter employee to remove. ";
	emp = inputEmployee(true);
	ht.remove(emp);

	cout << "Hash Table after removal:" << endl;
	ht.display();
}