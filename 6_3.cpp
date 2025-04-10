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

    void Swap(Node* a, Node* b)
    {
        if (!a || !b || a == b) return;

        if (a->next == b)
        {                                            // a и b - соседние
            a->next = b->next;
            b->prev = a->prev;
            if (b->next) b->next->prev = a;
            if (a->prev) a->prev->next = b;
            b->next = a;
            a->prev = b;
        }
        else if (b->next == a) 
        {                                           // b и a - соседние (переставлены местами)
            b->next = a->next;
            a->prev = b->prev;
            if (a->next) a->next->prev = b;
            if (b->prev) b->prev->next = a;
            a->next = b;
            b->prev = a;
        }
        else 
        {                                           // не соседние узлы
            Node* aPrev = a->prev;
            Node* aNext = a->next;
            Node* bPrev = b->prev;
            Node* bNext = b->next;

            if (aPrev) aPrev->next = b;
            if (aNext) aNext->prev = b;
            if (bPrev) bPrev->next = a;
            if (bNext) bNext->prev = a;

            std::swap(a->prev, b->prev);
            std::swap(a->next, b->next);
        }

        if (!a->prev) head = a;
        if (!b->prev) head = b;
        if (!a->next) tail = a;
        if (!b->next) tail = b;

    }

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

    int size(Node* head, Node* tail)
    {

        Node* current = head;
        int count = 0;
        while (current && current->next)
        {
            count++;
            current = current->next;
        }
        return count;
    }


    void quickSort(Node* head, Node* tail) 
    {
        if (!head || !tail || head == tail || head == tail->next) return;


        bool checkList = 1;
        for (Node* check = this->head; check != this->tail && check->next && checkList; check = check->next)
            checkList = (checkList && check <= check->next);
        if (checkList)
            return;
        
        // 8 3 10 14 7 9 2 1 5
        // 15 3 8 12 1 9 6 11 4 2 10

        Node* pivot = tail;
        Node* r = tail;
        Node* l = head;
        bool flagl = 0, flagr = 0;

        for (int i = 0; i < size(head, tail) / 2; i++)
        {
            if(pivot->prev)
                pivot = pivot->prev;
        }

        while (!flagl)
        {
            auto tl = l, tr = r;
            for (; tr != tail && tr->next; tr = tr->next)
                if (!flagr)
                    flagr = (tr == l);
            if (flagr)
                break;
            while (l != r && l->data < pivot->data)
                l = l->next;
            while (l != r && r->data > pivot->data)
                r = r->prev;
            if (l == r && l == head)
                l = l->next;
            if (l == r && l == tail)
                r = r->prev;
            for (; tl != tail && tl->next; tl = tl->next)
                if (!flagl && r && r->prev)
                    flagl = (tl == r->prev);
            if (flagl)
            {
                Swap(l, r);
                tl = l;
                l = r->next;
                r = tl->prev;
                if (!tl->prev)this->head = tl;
                if (!tl->next)this->tail = tl;
                if (!r->prev)this->head = r;
                if (!r->next)this->tail = r;
                flagl = 0;
                head = this->head;
                tail = this->tail;
            }
            else
                break;
        }

        if (r && r->prev)
            quickSort(head, r->prev);
        if (l && l->next)
            quickSort(l->next, tail);
    }

    Node* GetHead() { return head; }

    Node* GetTail() { return tail; }

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

    list.quickSort(list.GetHead(), list.GetTail());

    cout << "Result: ";
    list.print();

    return 0;
}
