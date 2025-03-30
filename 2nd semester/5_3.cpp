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

    // Добавить элемент в очередь
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

    // Удалить элемент из очереди
    void pop()
    {
        Node* temp = front;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete temp;
    }

    // Получить первый элемент
    int peek() const
    {
        if (!isEmpty()) return front->data;
        throw runtime_error("Queue is empty");
    }

    // Проверить, пуста ли очередь
    bool isEmpty() const
    {
        return front == nullptr;
    }

    // Вывести очередь
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

    // Добавить после каждого минимального последний нечетный элемент
    void insertAfterMin(int oddValue)
    {
        int min = findMin();
        Node* current = front;
        while (current != nullptr)
        {
            if (current->data == min)
            {
                Node* newNode = new Node(oddValue);
                newNode->next = current->next;
                current->next = newNode;
                if (current == rear) rear = newNode;
                current = newNode;
            }
            current = current->next;
        }
    }

    // Найти минимальное значение
    int findMin() const
    {
        if (isEmpty()) throw runtime_error("Queue is empty");
        int minVal = front->data;
        Node* current = front->next;
        while (current != nullptr) {
            if (current->data < minVal) minVal = current->data;
            current = current->next;
        }
        return minVal;
    }

    // Найти последний нечетный элемент
    int findLastOdd() const
    {
        int lastOdd = -10000000;
        Node* current = front;
        while (current != nullptr) 
        {
            if (current->data % 2)
                lastOdd = current->data;
            current = current->next;
        }
        if (lastOdd == -1) 
            throw runtime_error("No odd elements");
        return lastOdd;
    }
};

int main()
{
    Queue q;
    int n, t;

    cout << "Count of elements: ";
    cin >> n;

    cout << "Elements: ";
    for (int i = 0; i < n; ++i)
    {
        cin >> t;
        q.push(t);
    }

    try
    {
        q.insertAfterMin(q.findLastOdd());

        cout << "Result: ";
        q.print();
    }
    catch (const exception& e) 
    {
        cout << e.what() << endl;
    }

    return 0;
}
