#include <iostream>
#include <string>
#include <windows.h>
#include <iomanip>
using namespace std;

HANDLE outp = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbInfo;

struct tree
{
	char inf;
	tree* right;
	tree* left;
	tree* parent;
};

tree* node(char x)
{
	tree* n = new tree;
	n->inf = x;
	n->left = n->right = NULL;
	n->parent = NULL;
	return n;
}

tree* create_tree(string str)
{ 
	tree* tr = NULL;
	for (unsigned int i = 0; i < str.length(); i++)
	{
		tree* n = node(str[i]);
		if (str[i] == '-' || str[i] == '+')
		{
			tr->parent = n;
			n->left = tr;
			tr = n;
		}
		else if (str[i] == '/' || str[i] == '*')
		{
			if (isdigit(tr->inf))
			{
				tr->parent = n;
				n->left = tr;
				tr = n;
			}
			else
			{
				n->parent = tr;
				n->left = tr->right;
				tr->right->parent = n;
				tr->right = n;
			}
		}
		else
		{
			if (!tr) tr = n;
			else
			{ 
				if (!tr->right)
				{
					n->parent = tr;
					n->left = tr->right;
					tr->right = n;
				}
				else
				{
					tree* x = tr->right;
					while (x->right) x = x->right;
					n->parent = x->parent;
					x->right = n;
				}
			}
		}
	}
	return tr;
}

void preorder(tree* tr) 
{
	if (tr) 
	{
		cout << tr->inf << ' ';
		preorder(tr->left);
		preorder(tr->right);
	}
}

void postorder(tree* tr)
{
	if (tr)
	{
		postorder(tr->left);
		postorder(tr->right);
		cout << tr->inf << ' ';
	}
}

void maxHeight(tree* x, short& max, short depth = 1)
{
	if (depth > max) max = depth;
	if (x->left) maxHeight(x->left, max, depth + 1);
	if (x->right) maxHeight(x->right, max, depth + 1);
}

void printHelper(tree* x, const COORD pos, const short offset)
{
	SetConsoleCursorPosition(outp, pos);
	cout << setw(offset + 1) << x->inf;
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

void print(tree* tr)
{
	if (tr)
	{
		short max = 1;
		maxHeight(tr, max);
		short width = 1 << (max + 1), max_w = 128;
		if (width > max_w) width = max_w;
		while (!isSizeOfConsoleCorrect(width, max)) system("pause");
		for (short i = 0; i < max; ++i) cout << '\n';
		GetConsoleScreenBufferInfo(outp, &csbInfo);
		COORD endPos = csbInfo.dwCursorPosition;
		printHelper(tr, { 0, short(endPos.Y - max) }, width >> 1);
		SetConsoleCursorPosition(outp, endPos);
	}
}

int main()
{
	string str;
	cout << "Input expression: ";
	getline(cin, str);
	string valid = "+-/*0123456789()";
	bool flag = true;
	for (char c: str)
		if (valid.find_first_of(c) == string::npos)
		{
			flag = false;
			break;
		}
	if (!flag) cout << "error";
	else
	{
		tree* tr = create_tree(str);
		print(tr);
		cout << endl;
		cout << "Preorder: ";
		preorder(tr);
		cout << endl;

		cout << "Postorder: ";
		postorder(tr);
		cout << endl;
	}
	return 0;
}