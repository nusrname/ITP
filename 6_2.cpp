#include <iostream>
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
    void removeDuplicates()
    {
        if (!head) return;

        Node* current = head;
        while (current && current->next)
        {
            if (current->data == current->next->data)
            {
                Node* temp = current->next;
                current->next = temp->next;

                if (temp->next)
                    temp->next->prev = current;
                else
                    tail = current;

                delete temp;
            }
            else 
                current = current->next;
        }
    }
};

int main() {
    List list;
    int value;

    cout << "Input elements (to stop input press '!'): ";
    while (cin >> value && value != '!')
        list.append(value);

    list.removeDuplicates();

    cout << "Result: ";
    list.print();

    return 0;
}
