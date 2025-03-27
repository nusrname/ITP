#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;

bool isAlnum(char ch)
{
	return isalnum(ch) || (ch >= 'À' && ch <= 'ÿ') || (ch == '¸' || ch == '¨');
}

vector<string> split(string text)
{
	vector<string> v;
	string current;
	char c;

	for (int i = 0; i < text.length(); i++)
	{
		c = text.at(i);
		if (isAlnum(c))
			current += c;
		else
		{
			if (!current.empty())
			{
				v.push_back(current);
				current.clear();

			}
			v.push_back(string(1, c));
		}
	}

	if (!current.empty()) 
	{
		v.push_back(current);
	}

	

	return v;
}

void Find(vector<string> v, int& min, int& max)
{
	min = max = -1;
	int maxLen = 0, minLen = 1000000000;
	int len;
	string el;

	for (int i = 0; i < v.size(); i++)
	{
		el = v[i];
		if (!el.empty() && isAlnum(el[0])) 
		{
			len = el.length();
			if (len < minLen) 
			{
				min = i;
				minLen = len;
			}
			if (len > maxLen)
			{
				max = i;
				maxLen = len;
			}
		}
	}
}

string Swap(string text) 
{
	vector<string> v = split(text);
	int max, min;
	Find(v, min, max);

	if (min != -1 && max != -1 && max != min) 
		swap(v[min], v[max]);

	string res = "";

	for (string el : v)
		res += el;

	return res;
}

int main()
{
	SetConsoleCP(1251);
	setlocale(LC_ALL, "ru");
	string text;
	cout << "Input text: ";
	getline(cin, text);
	cout << Swap(text);
}
