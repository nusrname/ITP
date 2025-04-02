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

    //void Swap(Node* a, Node* b)
    //{
    //    if (!a || !b || a == b) return;

    //    if (a->next == b)
    //    {                                            // a и b - соседние
    //        a->next = b->next;
    //        b->prev = a->prev;
    //        if (b->next) b->next->prev = a;
    //        if (a->prev) a->prev->next = b;
    //        b->next = a;
    //        a->prev = b;
    //    }
    //    else if (b->next == a) 
    //    {                                           // b и a - соседние (переставлены местами)
    //        b->next = a->next;
    //        a->prev = b->prev;
    //        if (a->next) a->next->prev = b;
    //        if (b->prev) b->prev->next = a;
    //        a->next = b;
    //        b->prev = a;
    //    }
    //    else 
    //    {                                           // не соседние узлы
    //        Node* aPrev = a->prev;
    //        Node* aNext = a->next;
    //        Node* bPrev = b->prev;
    //        Node* bNext = b->next;

    //        if (aPrev) aPrev->next = b;
    //        if (aNext) aNext->prev = b;
    //        if (bPrev) bPrev->next = a;
    //        if (bNext) bNext->prev = a;

    //        std::swap(a->prev, b->prev);
    //        std::swap(a->next, b->next);
    //    }

    //    if (!a->prev) head = a;
    //    if (!b->prev) head = b;
    //    if (!a->next) tail = a;
    //    if (!b->next) tail = b;
    //}

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

    Node* partition(Node* low, Node* high) 
    {
        if (!low || !high || low == high) return low;

        int pivot = high->data;
        Node* i = low->prev;

        for (Node* j = low; j != high; j = j->next) 
        {
            if (j->data < pivot)
            {
                (i == nullptr) ? i = low : i = i->next;
                /*Swap(i, j);*/
                swap(i->data, j->data);
            }
        }

        (i == nullptr) ? i = low : i = i->next;
        /*Swap(i, high);*/
        swap(i->data, high->data);
        return i;
    }


    void quickSort(Node* low, Node* high) 
    {
        if (!low || !high || low == high || low == high->next) return;

        Node* pivot = partition(low, high);
        if (pivot && pivot->prev) 
            quickSort(low, pivot->prev);
        if (pivot && pivot->next) 
            quickSort(pivot->next, high);
    }

    Node* GetHead() { return head; }

    Node* GetTail() { return tail; }

};

int main()
{
    List list;
    int value;

    cout << "Input elements (to stop input non-number): ";
    while (cin >> value)
        list.append(value);

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    //list.print();

    list.quickSort(list.GetHead(), list.GetTail());

    cout << "Result: ";
    list.print();

    return 0;
}
