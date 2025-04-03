#include <iostream>
#include <vector>
using namespace std;

class List
{
public:

	struct Node
	{
		int data;
		Node* prev;
		Node* next;
		Node(int value) : data(value), prev(nullptr), next(nullptr) {}
	};


	void Swap(Node* a, Node* b)
	{
		if (!a || !b || a == b) return;

		// ћен€ем значени€, а не указатели
		swap(a->data, b->data);
	}


private:
	Node* head;
	Node* tail;

public:
	List() : head(nullptr), tail(nullptr) {}

	List(const List& other) : head(nullptr), tail(nullptr) 
	{
		Node* current = other.head;
		while (current) {
			append(current->data);
			current = current->next;
		}
	}

	~List()
	{
		while (head)
		{
			Node* temp = head;
			head = head->next;
			delete temp;
		}
	}

	void append(int value)
	{
		Node* newNode = new Node(value);
		if (!head)
		{
			head = tail = newNode;
		}
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
		while (current)
		{
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}

	Node* GetHead() { return head; }

	Node* GetTail() { return tail; }

};

List::Node* partition(List::Node* low, List::Node* high, List& valueList) 
{
	if (!low || !high || low == high) return low;

	int pivot = high->data;
	List::Node* i = low->prev;

	for (List::Node* j = low; j != high; j = j->next) 
	{
		if (j->data < pivot) 
		{
			i = (i == nullptr) ? low : i->next;
			valueList.Swap(i, j);
		}
	}

	i = (i == nullptr) ? low : i->next;
	valueList.Swap(i, high);
	return i;
}

void quickSort(List::Node* low, List::Node* high, List& list, List& valueList)
{
	if (!low || !high || low == high || low == high->next) return;

	List::Node* pivot = partition(low, high, valueList);

	// Ќаходим соответствующие узлы в основном списке
	List::Node* originalLow = list.GetHead();
	List::Node* originalHigh = list.GetTail();
	List::Node* originalPivot = list.GetHead();

	while (originalPivot && originalPivot->data != pivot->data)
		originalPivot = originalPivot->next;

	while (originalLow && originalLow->data != low->data)
		originalLow = originalLow->next;

	while (originalHigh && originalHigh->data != high->data)
		originalHigh = originalHigh->prev;

	if (originalPivot && originalPivot->prev)
		quickSort(originalLow, originalPivot->prev, list, valueList);

	if (originalPivot && originalPivot->next)
		quickSort(originalPivot->next, originalHigh, list, valueList);
}

int main()
{
	List list;
	int value;

	cout << "Input elements (to stop input non-number): ";
	while (cin >> value)
		list.append(value);

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	List valueList(list);

	quickSort(list.GetHead(), list.GetTail(), list, valueList);

	cout << "Result: ";
	list.print();

	return 0;
}
