#include <iostream>
using namespace std;

class Stack 
{
private:
    struct Node
    {
        int data;
        Node* next;
        Node(int value) : data(value), next(nullptr) {}
    };

    Node* topNode;

public:
    Stack() : topNode(nullptr) {}

    ~Stack() 
    {
        while (!isEmpty())
        {
            pop();
        }
    }

    void push(int value) 
    {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
    }

    void pop()
    {
        if (isEmpty()) return;
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
    }

    int top() const
    {
        if (!isEmpty()) return topNode->data;
        cout << "Stack is empty" << endl;
        return 0;
    }

    bool isEmpty() const
    {
        return topNode == nullptr;
    }

    void print() const
    {
        Node* current = topNode;
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
    Stack original, odd, even, temp;
    int n, t;

    cout << "Count of elements: ";
    cin >> n;
    cout << "Elements: ";

    for (int i = n; i > 0; --i) 
    {
        cin >> t;
        original.push(t);
    }

    // Распределяем числа по четности
    while (!original.isEmpty())
    {
        int value = original.top();
        original.pop();

        if (value % 2 == 0)
            even.push(value);
        else
            odd.push(value);
    }


    // Сначала четные
    while (!even.isEmpty())
    {
        temp.push(even.top());
        even.pop();
    }
    while (!temp.isEmpty())
    {
        original.push(temp.top());
        temp.pop();
    }

    // Затем нечетные
    while (!odd.isEmpty())
    {
        temp.push(odd.top());
        odd.pop();
    }
    while (!temp.isEmpty())
    {
        original.push(temp.top());
        temp.pop();
    }


    cout << "Result: ";
    original.print();

    return 0;
}
