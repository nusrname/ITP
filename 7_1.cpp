#include <iostream>
#include <string>
using namespace std;

class Stack
{
    struct StackNode
    {
        char data;
        StackNode* next;
        StackNode(char val) : data(val), next(nullptr) {}
    };
    StackNode* topNode;

public:
    Stack() : topNode(nullptr) {}

    void push(char val) 
    {
        StackNode* newNode = new StackNode(val);
        newNode->next = topNode;
        topNode = newNode;
    }

    char pop()
    {
        if (isEmpty()) return '\0';
        char val = topNode->data;
        StackNode* temp = topNode;
        topNode = topNode->next;
        delete temp;
        return val;
    }

    char top() 
    {
        return isEmpty() ? '\0' : topNode->data;
    }

    bool isEmpty() 
    {
        return topNode == nullptr;
    }

    ~Stack() 
    {
        while (!isEmpty()) pop();
    }
};

// Проверка приоритета оператора
int precedence(char op) 
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Проверка на оператор
bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Инвертирование строки и замена скобок
string reverseAndSwap(string expr)
{
    string rev = "";
    for (int i = expr.length() - 1; i >= 0; --i) 
    {
        if (expr[i] == '(') rev += ')';
        else if (expr[i] == ')') rev += '(';
        else rev += expr[i];
    }
    return rev;
}

// Преобразование инфиксной формы в постфиксную 
string infixToPrefix(const string& infix)
{
    string expr = reverseAndSwap(infix);
    Stack st;
    string output = "";

    for (char c : expr) 
    {
        if (isalnum(c))
        {
            output += c;
        }
        else if (c == '(')
        {
            st.push(c);
        }
        else if (c == ')') 
        {
            while (!st.isEmpty() && st.top() != '(')
            {
                output += st.pop();
            }
            st.pop(); // убрать '('
        }
        else if (isOperator(c)) 
        {
            while (!st.isEmpty() && precedence(c) < precedence(st.top())) 
            {
                output += st.pop();
            }
            st.push(c);
        }
    }

    while (!st.isEmpty())
        output += st.pop();

    return reverseAndSwap(output);
}

int main()
{
    string infix;
    cout << "Input infix: ";
    cin >> infix;

    string prefix = infixToPrefix(infix);
    cout << "Result: " << prefix << endl;

    return 0;
}
