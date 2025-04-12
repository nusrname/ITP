#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class List
{
private:
    struct Node
    {
        int data;
        Node* prev;
        Node* next;
        Node(int value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
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

    int findMin() const
    {
        if (!head) throw runtime_error("List is empty");
        int minVal = head->data;
        Node* current = head->next;
        while (current)
        {
            if (current->data < minVal) minVal = current->data;
            current = current->next;
        }
        return minVal;
    }

    void insert(Node* node, int value) 
    {
        if (!node || !head) return;

        Node* newNode = new Node(value);
        newNode->next = node;
        newNode->prev = node->prev;

        if (node->prev)
            node->prev->next = newNode;
        else 
            head = newNode;

        node->prev = newNode;
    }

    void insertMin()
    {
        if (!head) return;

        int minVal = findMin();
        int lastValue = tail->data;

        Node* current = head;
        while (current)
        {
            if (current->data == lastValue)
            {
                insert(current, minVal);
            }
            current = current->next;
        }
    }
};

int main()
{
    List list;
    string line;
    int value;

    cout << "Input elements: ";
    getline(cin, line);

    istringstream iss(line);
    while (iss >> value)
        list.append(value);

    list.insertMin();

    cout << "Result: ";
    list.print();

    return 0;
}
