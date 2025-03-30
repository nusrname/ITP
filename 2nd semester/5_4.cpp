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

    void findMinMax(int& minVal, int& maxVal) 
    {
        if (isEmpty()) throw runtime_error("Stack is empty");
        Stack temp;
        minVal = maxVal = top();
        while (!isEmpty())
        {
            int val = top();
            pop();
            if (val < minVal) minVal = val;
            if (val > maxVal) maxVal = val;
            temp.push(val);
        }
        // ������������ ����
        while (!temp.isEmpty())
        {
            push(temp.top());
            temp.pop();
        }
    }

    // �������� �������� ������� ������������ ����� ������� � ���������� ���������
    void insert() 
    {
        if (isEmpty()) return;

        int minVal, maxVal;
        findMinMax(minVal, maxVal);

        Stack reversed, result;
        int maxCount = 0;

        // ������� ���������� ����
        while (!isEmpty())
        {
            int val = top();
            pop();
            if (val == maxVal) ++maxCount;
            reversed.push(val);
        }

        bool firstInserted = false;

        // ��������� result
        while (!reversed.isEmpty()) 
        {
            int val = reversed.top();
            reversed.pop();
            result.push(val);
            if (val == maxVal)
            {
                if (!firstInserted)
                {
                    result.push(minVal); // ����� ������� max
                    firstInserted = true;
                }
                else if (maxCount == 1) 
                {
                    result.push(minVal); // ���� max ����������� ������ ���� ���
                }
                else
                {
                    --maxCount;
                    if (maxCount == 1) 
                    {
                        result.push(minVal); // ����� ���������� max
                    }
                }
            }
        }

        // ������ ��������� � �������� ����
        while (!result.isEmpty()) 
        {
            push(result.top());
            result.pop();
        }
    }
};

int main()
{
    Stack stack, odd, even, temp;
    int n, t;

    cout << "Count of elements: ";
    cin >> n;
    cout << "Elements: ";

    for (int i = n; i > 0; --i)
    {
        cin >> t;
        stack.push(t);
    }

    stack.insert();

    cout << "Result: ";
    stack.print();

    return 0;
}
