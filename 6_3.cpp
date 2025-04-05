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

    //int size(Node* head, Node* tail)
    //{

    //    Node* current = head;
    //    int count = 0;
    //    while (current && current->next)
    //    {
    //        count++;
    //        current = current->next;
    //    }
    //    return count;
    //}


    //void quickSort(Node* head, Node* tail) 
    //{
    //    if (!head || !tail || head == tail || head == tail->next) return;


    //    bool checkList = 1;
    //    for (Node* check = this->head; check != this->tail && check->next && checkList; check = check->next)
    //        checkList = (checkList && check <= check->next);
    //    if (checkList)
    //        return;

    //    Node* pivot = tail;
    //    Node* r = tail;
    //    Node* l = head;
    //    bool flagl = 0, flagr = 0;

    //    for (int i = 0; i < size(head, tail) / 2; i++)
    //    {
    //        if(pivot->prev)
    //            pivot = pivot->prev;
    //    }

    //    while (!flagl)
    //    {
    //        auto tl = l, tr = r;
    //        for (; tr != tail && tr->next; tr = tr->next)
    //            if (!flagr)
    //                flagr = (tr == l);
    //        if (flagr)
    //            break;
    //        while (l != r && l->data < pivot->data)
    //            l = l->next;
    //        while (l != r && r->data > pivot->data)
    //            r = r->prev;
    //        if (l == r && l == head)
    //            l = l->next;
    //        if (l == r && l == tail)
    //            r = r->prev;
    //        for (; tl != tail && tl->next; tl = tl->next)
    //            if (!flagl)
    //                flagl = (tl == r->prev);
    //        if (flagl)
    //        {
    //            Swap(l, r);
    //            tl = l;
    //            l = r->next;
    //            r = tl->prev;
    //            flagl = 0;
    //        }
    //        else
    //            break;
    //    }

    //    if (r && r->prev)
    //        quickSort(head, r->prev);
    //    if (l && l->next)
    //        quickSort(l->next, tail);
    //}
    int size(Node* head, Node* tail)
    {
        Node* current = head;
        int count = 0;
        while (current) // исправлено условие
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

        Node* pivot = tail;
        Node* l = head;
        Node* r = tail->prev;

        while (l != r)
        {
            while (l != tail && l->data < pivot->data) l = l->next;
            while (r != head && r->data > pivot->data) r = r->prev;

            if (l != r)
            {
                if (l != pivot && r != pivot)
                    Swap(l, r);
            }
        }

        if (l != pivot)
            Swap(l, pivot);

        if (l && l->prev)
            quickSort(head, l->prev);
        if (l && l->next)
            quickSort(l->next, tail);
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

    list.quickSort(list.GetHead(), list.GetTail());

    cout << "Result: ";
    list.print();

    return 0;
}
