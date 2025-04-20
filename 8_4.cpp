#include <iostream>
#include <windows.h>
#include <iomanip>
#define RED true
#define BLACK false
using namespace std;

HANDLE outp = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbInfo;

class Tree
{
	struct Node
	{
		int key;
		bool color;
		Node* left, * right, * parent;

		Node(int key) : key(key), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
	};

	Node* root;
	Node* NIL; // Специальный NIL-узел (используется вместо nullptr)

	void maxHeight(Node* x, short& max, short depth = 1)
	{
		if (depth > max) max = depth;
		if (x->left != NIL) maxHeight(x->left, max, depth + 1);
		if (x->right != NIL) maxHeight(x->right, max, depth + 1);
	}

	void printHelper(Node* x, const COORD pos, const short offset)
	{
		SetConsoleTextAttribute(outp, x->color == RED ? 12 : 8); // Установка цвета узла
		SetConsoleCursorPosition(outp, pos);
		cout << setw(offset + 1) << x->key;
		if (x->left != NIL) printHelper(x->left, { pos.X, short(pos.Y + 1) }, offset >> 1);
		if (x->right != NIL) printHelper(x->right, { short(pos.X + offset), short(pos.Y + 1) }, offset >> 1);
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

	// Левый поворот вокруг узла x
	void leftRotate(Node* x)
	{
		Node* y = x->right;
		x->right = y->left;
		if (y->left != NIL)
			y->left->parent = x;
		y->parent = x->parent;
		if (x->parent == nullptr)
			root = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
		y->left = x;
		x->parent = y;
	}

	// Правый поворот вокруг узла x
	void rightRotate(Node* x)
	{
		Node* y = x->left;
		x->left = y->right;
		if (y->right != NIL)
			y->right->parent = x;
		y->parent = x->parent;
		if (x->parent == nullptr)
			root = y;
		else if (x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;
		y->right = x;
		x->parent = y;
	}

	// Восстановление свойств дерева после вставки
	void insertFixup(Node* z)
	{
		while (z->parent->color == RED)
		{
			if (z->parent == z->parent->parent->left)
			{
				Node* y = z->parent->parent->right;
				if (y->color == RED) // Случай 1: дядя красный
				{
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				else
				{
					if (z == z->parent->right) // Случай 2: z — правый потомок
					{
						z = z->parent;
						leftRotate(z);
					}
					// Случай 3: z — левый потомок
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					rightRotate(z->parent->parent);
				}
			}
			else
			{
				Node* y = z->parent->parent->left;
				if (y->color == RED)
				{
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				}
				else
				{
					if (z == z->parent->left)
					{
						z = z->parent;
						rightRotate(z);
					}
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					leftRotate(z->parent->parent);
				}
			}
		}
		root->color = BLACK;
	}

	// Замена одного поддерева другим
	void transplant(Node* u, Node* v)
	{
		if (u->parent == nullptr)
			root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		v->parent = u->parent;
	}

	// Возвращает узел с минимальным значением в поддереве
	Node* minimum(Node* node)
	{
		while (node->left != NIL)
			node = node->left;
		return node;
	}

	// Восстановление свойств после удаления узла
	void deleteFixup(Node* x)
	{
		while (x != root && x->color == BLACK)
		{
			if (x == x->parent->left)
			{
				Node* w = x->parent->right;
				if (w->color == RED)
				{
					w->color = BLACK;
					x->parent->color = RED;
					leftRotate(x->parent);
					w = x->parent->right;
				}
				if (w->left->color == BLACK && w->right->color == BLACK)
				{
					w->color = RED;
					x = x->parent;
				}
				else
				{
					if (w->right->color == BLACK)
					{
						w->left->color = BLACK;
						w->color = RED;
						rightRotate(w);
						w = x->parent->right;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->right->color = BLACK;
					leftRotate(x->parent);
					x = root;
				}
			}
			else
			{
				Node* w = x->parent->left;
				if (w->color == RED)
				{
					w->color = BLACK;
					x->parent->color = RED;
					rightRotate(x->parent);
					w = x->parent->left;
				}
				if (w->right->color == BLACK && w->left->color == BLACK)
				{
					w->color = RED;
					x = x->parent;
				}
				else
				{
					if (w->left->color == BLACK)
					{
						w->right->color = BLACK;
						w->color = RED;
						leftRotate(w);
						w = x->parent->left;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->left->color = BLACK;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = BLACK;
	}

	// Удаление узла из дерева
	void deleteNode(Node* z)
	{
		Node* y = z;
		Node* x;
		bool yOriginalColor = y->color;
		if (z->left == NIL)
		{
			x = z->right;
			transplant(z, z->right);
		}
		else if (z->right == NIL)
		{
			x = z->left;
			transplant(z, z->left);
		}
		else {
			y = minimum(z->right);
			yOriginalColor = y->color;
			x = y->right;
			if (y->parent == z)
				x->parent = y;
			else {
				transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z;
		if (yOriginalColor == BLACK)
			deleteFixup(x);
	}

	// Вычисляет сумму ключей листьев дерева
	int sumLeaves(Node* node)
	{
		if (node == NIL) return 0;
		if (node->left == NIL && node->right == NIL)
			return node->key;
		return sumLeaves(node->left) + sumLeaves(node->right);
	}

	// Поиск узла по ключу
	Node* search(Node* node, int key)
	{
		if (node == NIL || key == node->key)
			return node;
		if (key < node->key)
			return search(node->left, key);
		else
			return search(node->right, key);
	}

public:
	Tree()
	{
		NIL = new Node(0);
		NIL->color = BLACK;
		NIL->left = NIL->right = NIL->parent = NIL;
		root = NIL;
	}

	// Вставка ключа в дерево
	void insert(int key)
	{
		if (search(root, key) != NIL)
			return;

		Node* z = new Node(key);
		z->left = z->right = z->parent = NIL;
		Node* y = NIL;
		Node* x = root;

		while (x != NIL)
		{
			y = x;
			if (z->key < x->key)
				x = x->left;
			else
				x = x->right;
		}
		z->parent = y;
		if (y == NIL)
			root = z;
		else if (z->key < y->key)
			y->left = z;
		else
			y->right = z;
		z->left = z->right = NIL;
		z->color = RED;
		insertFixup(z);
	}

	// Удаление ключа
	void remove(int key)
	{
		Node* z = search(root, key);
		if (z != NIL)
			deleteNode(z);
	}

	int getSum() { return sumLeaves(root); }

	// Печать дерева в консоли
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
			SetConsoleTextAttribute(outp, 7);
		}
	}
};

int main()
{
	Tree tree;
	int value, cnt;
	cout << "Input count of elements: ";
	cin >> cnt;

	cout << "Elements: ";
	for (int i = 0; i < cnt; i++)
	{
		cin >> value;
		tree.insert(value);
	}

	tree.print();

	cout << "Sum of leaves: " << tree.getSum() << endl;

	return 0;
}
