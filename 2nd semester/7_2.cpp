/*пример данных для проверки
   1 2 4 5 -1
   0 3 -1
   0 5 -1
   1 -1
   0 6 -1
   0 2 6 -1
   4 5 -1
*/
#include <iostream>
using namespace std;


struct Node
{
    int data;
    Node* next;
};

class Queue 
{
    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    void push(int value)
    {
        Node* node = new Node{ value, nullptr };
        if (!rear)
            front = rear = node;
        else
        {
            rear->next = node;
            rear = node;
        }
    }

    int pop() 
    {
        if (isEmpty()) return -1;
        Node* temp = front;
        int value = temp->data;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
        return value;
    }

    bool isEmpty() const { return front == nullptr; }
};

class Stack 
{
    Node* top;

public:
    Stack() : top(nullptr) {}

    void push(int value) 
    {
        Node* node = new Node{ value, top };
        top = node;
    }

    int pop()
    {
        if (isEmpty()) return -1;
        Node* temp = top;
        int value = temp->data;
        top = top->next;
        delete temp;
        return value;
    }

    int peek()
    {
        if (isEmpty()) return -1;
        return top->data;
    }

    bool isEmpty() const { return top == nullptr; }
};

class Graph
{
    Node** adjList;
    int vertices;

public:

    Graph(int v) : vertices(v) 
    {
        adjList = new Node*[v];
        for (int i = 0; i < v; ++i) 
            adjList[i] = nullptr;
    }

    void addEdge(int src, int dest) 
    {
        Node* node = new Node{ dest, adjList[src] };
        adjList[src] = node;
    }

    void BFS(int start, int сv)
    {
        bool* visited = new bool[vertices];
        for (int i = 0; i < vertices; ++i) visited[i] = false;

        Queue q;
        q.push(start);
        visited[start] = true;

        cout << "BFS: ";

        while (!q.isEmpty()) 
        {
            int v = q.pop();
            cout << v << " ";

            // Собираем смежные вершины
            int* neighbors = new int[сv]; // Максимум на 1 вершину
            int count = 0;
            Node* temp = adjList[v];
            while (temp)
            {
                neighbors[count++] = temp->data;
                temp = temp->next;
            }

            // Сортируем по возрастанию
            for (int i = 0; i < count - 1; ++i)
            {
                for (int j = i + 1; j < count; ++j)
                {
                    if (neighbors[i] > neighbors[j])
                    {
                        int t = neighbors[i];
                        neighbors[i] = neighbors[j];
                        neighbors[j] = t;
                    }
                }
            }

            // Обрабатываем в отсортированном порядке
            for (int i = 0; i < count; ++i)
            {
                int u = neighbors[i];
                if (!visited[u]) 
                {
                    visited[u] = true;
                    q.push(u);
                }
            }
        }

        cout << endl;
        delete[] visited;
    }

    //обход в глубину
    void DFS(int start, int cv)
    {
        bool* visited = new bool[vertices];
        for (int i = 0; i < vertices; ++i) visited[i] = false;

        Stack s;
        s.push(start);
        visited[start] = true;

        cout << "DFS: " << start << " ";

        while (!s.isEmpty())
        {
            int current = s.peek();

            // Собираем непосещённых соседей
            int* neighbors = new int[cv];
            int count = 0;
            Node* neighbor = adjList[current];

            while (neighbor)
            {
                if (!visited[neighbor->data])
                    neighbors[count++] = neighbor->data;
                neighbor = neighbor->next;
            }

            if (count == 0) 
            {
                s.pop();
                continue;
            }

            // Сортируем по возрастанию
            for (int i = 0; i < count - 1; ++i)
            {
                for (int j = i + 1; j < count; ++j)
                {
                    if (neighbors[i] > neighbors[j])
                    {
                        int temp = neighbors[i];
                        neighbors[i] = neighbors[j];
                        neighbors[j] = temp;
                    }
                }
            }

            // Добавляем только первого (наименьшего) соседа
            int next = neighbors[0];
            visited[next] = true;
            s.push(next);
            cout << next << " ";
        }

        cout << endl;
        delete[] visited;
    }


    ~Graph() 
    {
        for (int i = 0; i < vertices; ++i) 
        {
            Node* curr = adjList[i];
            while (curr)
            {
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
        delete[] adjList;
    }
};

int main()
{
    int v, e;
    cout << "Enter number of vertices: ";
    cin >> v;

    Graph g(v);

    cout << "Enter number of edges: ";
    cin >> e;

    cout << "Enter adjacency list for each vertex (end with -1):" << endl;
    for (int i = 0; i < v; ++i)
    {
        cout << "Vertex " << i << ": ";
        int neighbor;
        while (cin >> neighbor && neighbor != -1)
            g.addEdge(i, neighbor);
    }

    g.BFS(0, v);
    g.DFS(0, v);

    return 0;
}