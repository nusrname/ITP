// Дано дерево. Удалить нечетные элементы.
#include <iostream>
#include <windows.h>
#include <iomanip>
using namespace std;

// Получение дескриптора консоли
HANDLE outp = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbInfo;

class AVLTree
{
	struct Node
	{
		int data, height;
		Node* left, * right;
		Node(int k) : data(k), height(1), left(nullptr), right(nullptr) {}
	};

	Node* root = nullptr;

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

	int height(Node* p) { return p ? p->height : 0; }

	int balanceFactor(Node* p) { return height(p->right) - height(p->left); }

	// Коррекция высоты узла
	void fixHeight(Node* p)
	{
		int hl = height(p->left);
		int hr = height(p->right);
		p->height = (hl > hr ? hl : hr) + 1;
	}

	Node* rotateRight(Node* p)
	{
		Node* q = p->left;
		p->left = q->right;
		q->right = p;
		fixHeight(p);
		fixHeight(q);
		return q;
	}

	Node* rotateLeft(Node* p)
	{
		Node* q = p->right;
		p->right = q->left;
		q->left = p;
		fixHeight(p);
		fixHeight(q);
		return q;
	}

	// Балансировка узла
	Node* balance(Node* p)
	{
		fixHeight(p);
		if (balanceFactor(p) == 2)
		{
			if (balanceFactor(p->right) < 0)
				p->right = rotateRight(p->right);
			return rotateLeft(p);
		}
		if (balanceFactor(p) == -2)
		{
			if (balanceFactor(p->left) > 0)
				p->left = rotateLeft(p->left);
			return rotateRight(p);
		}
		return p;
	}

	Node* insert(Node* p, int k)
	{
		if (!p) return new Node(k);
		if (k < p->data)
			p->left = insert(p->left, k);
		else
			p->right = insert(p->right, k);
		return balance(p);
	}

	Node* findMin(Node* p) { return p->left ? findMin(p->left) : p; }

	Node* removeMin(Node* p)
	{
		if (!p->left) return p->right;
		p->left = removeMin(p->left);
		return balance(p);
	}

	Node* remove(Node* p, int k)
	{
		if (!p) return nullptr;
		if (k < p->data)
			p->left = remove(p->left, k);
		else if (k > p->data)
			p->right = remove(p->right, k);
		else 
		{
			Node* q = p->left;
			Node* r = p->right;
			delete p;
			if (!r) return q;
			Node* min = findMin(r);
			min->right = removeMin(r);
			min->left = q;
			return balance(min);
		}
		return balance(p);
	}

	void removeOdd(Node*& p)
	{
		if (!p) return;
		removeOdd(p->left);
		removeOdd(p->right);
		if (p->data % 2 != 0)
			p = remove(p, p->data);
	}

public:

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

	void insert(int k) { root = insert(root, k); }

	void removeOdd() { removeOdd(root); }

};

int main()
{
	AVLTree tree;
	int n, value;
	cout << "Input count of elements: ";
	cin >> n;
	cout << "Input elements: ";
	for (int i = 0; i < n; ++i)
	{
		cin >> value;
		tree.insert(value);
	}

	tree.print();

	tree.removeOdd();

	cout << "After deleting: " << endl;
	tree.print();
	cout << endl;


	return 0;
}