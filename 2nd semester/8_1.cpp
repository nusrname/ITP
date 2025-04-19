#include <iostream>
#include <windows.h>
#include <iomanip>
#include <vector>
using namespace std;

HANDLE outp = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbInfo;

class Tree 
{
    struct Node 
    {
        int data;
        Node* left;
        Node* right;
        Node(int value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insert(Node* current, int value) 
    {
        if (!current) return new Node(value);
        if (value < current->data)
            current->left = insert(current->left, value);
        else if (value > current->data)
            current->right = insert(current->right, value);
        return current;
    }

    void maxHeight(Node* x, short& max, short depth = 1)
    {
        if (depth > max) max = depth;
        if (x->left) maxHeight(x->left, max, depth + 1);
        if (x->right) maxHeight(x->right, max, depth + 1);
    }

    void printHelper(Node* x, const COORD pos, const short offset) 
    {
        SetConsoleCursorPosition(outp, pos);
        cout << setw(offset + 1) << x->data;
        if (x->left) printHelper(x->left, { pos.X, short(pos.Y + 1) }, offset >> 1);
        if (x->right) printHelper(x->right, { short(pos.X + offset), short(pos.Y + 1) }, offset >> 1);
    }

    bool findPath(Node* node, int x, vector<int>& path)
    {
        if (!node) return false;
        path.push_back(node->data);
        if (node->data == x) return true;
        if ((x < node->data && findPath(node->left, x, path)) ||
            (x > node->data && findPath(node->right, x, path)))
            return true;
        path.pop_back();
        return false;
    }

    bool isSizeOfConsoleCorrect(const short& width, const short& height)
    {
        GetConsoleScreenBufferInfo(outp, &csbInfo);
        COORD szOfConsole = csbInfo.dwSize;
        if (szOfConsole.X < width && szOfConsole.Y < height)
            cout << "Please increase the height and width of the terminal.";
        else if (szOfConsole.X < width)
            cout << "Please increase the width of the terminal. ";
        else if (szOfConsole.Y < height)
            cout << "Please increase the height of the terminal. ";
        if (szOfConsole.X < width || szOfConsole.Y < height) {
            cout << "Size of your terminal now: " << szOfConsole.X << ' ' << szOfConsole.Y
                << ". Minimum required: " << width << ' ' << height << ".\n";
            return false;
        }
        return true;
    }

public:
    Tree() : root(nullptr) {}

    void insert(int value) { root = insert(root, value); }

    bool getPathTo(int x, vector<int>& path) { return findPath(root, x, path); }

    void print() 
    {
        if (root) 
        {
            short max = 1;
            maxHeight(root, max);
            short width = 1 << (max + 1), max_w = 128;
            if (width > max_w) width = max_w;
            while (!isSizeOfConsoleCorrect(width, max)) system("pause");
            for (short i = 0; i < max; ++i) cout << '\n';
            GetConsoleScreenBufferInfo(outp, &csbInfo);
            COORD endPos = csbInfo.dwCursorPosition;
            printHelper(root, { 0, short(endPos.Y - max) }, width >> 1);
            SetConsoleCursorPosition(outp, endPos);
        }
    }
};

int main()
{
    Tree tree;
    int n, x;
    cout << "Enter number of elements: ";
    cin >> n;
    cout << "Enter elements: ";
    for (int i = 0, val; i < n; ++i)
    {
        cin >> val;
        tree.insert(val);
    }

    cout << "Enter target value X: ";
    cin >> x;

    vector<int> path;
    if (tree.getPathTo(x, path))
    {
        cout << "Path to " << x << ": ";
        for (int val : path) cout << val << ' ';
        cout << endl;
    }
    else
        cout << "Value not found." << endl;

    tree.print();
    return 0;
}