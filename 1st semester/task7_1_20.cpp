#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <windows.h>
using namespace std;

list<string> split(string text)
{
	list<string> v;
	string buf = "";
	char t;
	int len = text.length();

	for (int i = 0; i < len; i++)
	{
		t = text[i];
		if (isalnum(t))
			buf += t;
		else
		{
			if (!buf.empty())
			{
				v.push_back(buf);
				buf.clear();
			}
			v.push_back(string(1, t));
		}
	}

	if (!buf.empty())
	{
		v.push_back(buf);
	}

	return v;
}

bool check(list<string> text)
{
	bool flag = 1;
	for (string el : text)
	{
		if (isdigit(el[0]))
			flag &= "18" <= el && el <= "21";
	}
	return flag;
}

int main()
{
	SetConsoleCP(1251);
	setlocale(LC_ALL, "rus");

	ifstream in("TV.txt");
	ofstream out("Result.txt");
	string str;

	try
	{
		if (!out.is_open())
			throw("doesn't open");
		while (getline(in, str))
		{
			if(check(split(str)))
				out << str << endl;
		}
	}
	catch (const exception& ex)
	{
		cout << ex.what() << endl;
	}

	in.close();
	out.close();

}

/*Input
Time 19 - 21
News1 15 - 16
Field of Wonders 20 - 21
News2 20 - 22
films 15 - 18
talk - show 17 - 23
17 18 News
18 19 Movie
19 20 Series
20 21 Documentary
21 22 Late News
15 16 Morning Show
18 20 Evening Concert
*/


/*output
Time 19-21
Field of Wonders 20-21
18 19 Movie
19 20 Series
20 21 Documentary
18 20 Evening Concert
*/