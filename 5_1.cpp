#include <iostream>
using namespace std;

class Queue
{
private:
    struct Node
    {
        int data;
        Node* next;
        Node(int value) : data(value), next(nullptr) {}
    };

    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    ~Queue()
    {
        while (!isEmpty())
        {
            pop();
        }
    }

    // �������� ������� � �������
    void push(int value)
    {
        Node* newNode = new Node(value);
        if (rear == nullptr)
            front = rear = newNode;
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

    // ������� ������� �� �������
    void pop()
    {
        Node* temp = front;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete temp;
    }

    // �������� ������ �������
    int peek() const
    {
        if (!isEmpty()) return front->data;
        cout << "������� �����!" << endl;
    }

    // ���������, ����� �� �������
    bool isEmpty() const
    {
        return front == nullptr;
    }

    // ������� ������ ������ ���������
    void removeDuplicates()
    {
        if (isEmpty()) return;

        Node* current = front;
        while (current != nullptr && current->next != nullptr)
        {
            if (current->data == current->next->data)
            {
                Node* temp = current->next;
                current->next = temp->next;
                if (temp == rear) rear = current;
                delete temp;
            }
            else
            {
                current = current->next;
            }
        }
    }

    // ������� �������
    void print() const
    {
        Node* current = front;
        while (current != nullptr) 
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() 
{
    Queue q;
    int n, t;

    cout << "Count of elements: ";
    cin >> n;

    // ���������� �������
    int arr[] = { 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5 };
    cout << "Elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> t;
        q.push(t);
    }

    q.removeDuplicates();

    cout << "Result: ";
    q.print();

    return 0;
}
