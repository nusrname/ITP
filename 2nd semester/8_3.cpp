#include <iostream>
#include <windows.h>
#include <iomanip>
#include <vector>
#include <algorithm>
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

    vector<int> getLeavesHelper(Node* node)
    {
        vector<int> leaves;
        if (!node) return leaves;

        if (!node->left && !node->right)
            leaves.push_back(node->data);
        if (node->left)
        {
            vector<int> leftLeaves = getLeavesHelper(node->left);
            leaves.insert(leaves.end(), leftLeaves.begin(), leftLeaves.end());
        }
        if (node->right)
        {
            vector<int> rightLeaves = getLeavesHelper(node->right);
            leaves.insert(leaves.end(), rightLeaves.begin(), rightLeaves.end());
        }

        return leaves;
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

    Node* deleteNode(Node* root, int value)
    {
        if (!root) return root;

        if (value < root->data)
            root->left = deleteNode(root->left, value);
        else if (value > root->data)
            root->right = deleteNode(root->right, value);
        else
        {
            // ”зел с одним или двум€ детьми
            if (!root->left)
            {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (!root->right)
            {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
        return root;
    }

    Node* findMin(Node* node)
    {
        while (node && node->left) node = node->left;
        return node;
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

    vector<int> getLeaves() { return getLeavesHelper(root); }

    int getAverageLeafValue()
    {
        vector<int> leaves = getLeaves();
        if (leaves.empty()) return -1;

        int sum = 0;
        for (int leaf : leaves)
            sum += leaf;

        return sum / leaves.size();
    }

    void deleteNode(int value) { root = deleteNode(root, value); }
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
    cout << "Tree before deleting: " << endl;
    tree.print();

    // ѕолучаем среднее значение среди всех листьев
    int avgLeaf = tree.getAverageLeafValue();
    if (avgLeaf != -1) {
        cout << "Average leaf: " << avgLeaf << endl;

        // Ќайти путь до среднего листа
        vector<int> path;
        if (tree.getPathTo(avgLeaf, path))
        {
            // ѕуть до среднего листа найден, теперь удалить "деда"
            if (path.size() > 2)
            {
                int grandparent = path[path.size() - 3]; // третий элемент в пути - это "дед"
                cout << "Deleting grandparent node: " << grandparent << endl;
                tree.deleteNode(grandparent); // удал€ем "деда"
            }
        }
    }
    else {
        cout << "No leaves in the tree." << endl;
    }

    tree.print();
    return 0;
}