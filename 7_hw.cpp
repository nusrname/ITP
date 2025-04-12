#include <iostream>

using namespace std;

const int N = 8;
const int MAX = 64;

// Направления движения коня
int dx[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
int dy[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };

// Очередь
class Queue 
{
public:
    int data[MAX][2];
    int front, rear;

    Queue() { front = rear = 0; }

    void push(int x, int y) 
    {
        data[rear][0] = x;
        data[rear][1] = y;
        rear++;
    }

    void pop(int& x, int& y)
    {
        x = data[front][0];
        y = data[front][1];
        front++;
    }

    bool isEmpty() const { return front == rear; }

    void clear() { front = rear = 0; }
};

// Преобразование строки (например, A2) в координаты (x, y)
void parsePosition(const char* pos, int& x, int& y) 
{
    x = pos[0] - 'A';
    y = pos[1] - '1';
}

// Преобразование координат (x, y) в строку (например, A2)
void toString(int x, int y, char* res) 
{
    res[0] = x + 'A';
    res[1] = y + '1';
    res[2] = '\0';
}

void findPath(const char* startStr, const char* endStr) 
{
    int startX, startY, endX, endY;
    parsePosition(startStr, startX, startY);
    parsePosition(endStr, endX, endY);

    bool visited[N][N] = { false };
    int parentX[N][N], parentY[N][N];

    Queue q;
    q.push(startX, startY);
    visited[startX][startY] = true;
    parentX[startX][startY] = -1;
    parentY[startX][startY] = -1;

    while (!q.isEmpty()) 
    {
        int x, y;
        q.pop(x, y);

        if (x == endX && y == endY) break;

        for (int i = 0; i < 8; ++i) 
        {
            int newx = x + dx[i];
            int newy = y + dy[i];

            if (newx >= 0 && newx < N && newy >= 0 && newy < N && !visited[newx][newy]) 
            {
                visited[newx][newy] = true;
                parentX[newx][newy] = x;
                parentY[newx][newy] = y;
                q.push(newx, newy);
            }
        }
    }

    // Восстановление пути
    int pathX[MAX], pathY[MAX], length = 0;
    int x = endX, y = endY;
    while (x != -1 && y != -1)
    {
        pathX[length] = x;
        pathY[length] = y;
        int px = parentX[x][y];
        int py = parentY[x][y];
        x = px;
        y = py;
        length++;
    }

    // Вывод в правильном порядке
    char pos[3];
    for (int i = length - 1; i >= 0; --i) 
    {
        toString(pathX[i], pathY[i], pos);
        cout << pos;
        if (i > 0) cout << " ";
    }
    cout << endl;
}

int main()
{
    char start[3], end[3];
    cout << "First position: ";
    cin >> start;
    cout << "Last position: ";
    cin >> end;

    findPath(start, end);

    return 0;
}
