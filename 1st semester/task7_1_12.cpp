#include <iostream>
#include <string>
#include <list>
#include <windows.h>
using namespace std;

bool isalnumRus(char t)
{
    return (isalnum(t) || ('А' <= t && t <= 'я' || t == 'ё' || t == 'Ё'));
}

list<string> split(string text)
{
    list<string> v;
    string buf = "";
    char t;
    int len = text.length();

    for (int i = 0; i < len; i++)
    {
        t = text[i];
        if (isalnumRus(t))
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

list<string> Delete(list<string> text, string word)
{
    bool fl;
    for (string& el : text)
    {
        fl = 1;
        for (char c : word)
        {
            fl &= (el.find(c) < 50);
        }
        if (fl)
        {
            el = "!1!sign";
        }
    }

    return text;
}

int main()
{
    SetConsoleCP(1251);
    setlocale(LC_ALL, "rus");

    string text, word;
    cout << "Введите предложение: ";
    getline(cin, text);
    cout << "Введите слово: ";
    getline(cin, word);

    cout << "Измененное предложение: ";
    for (string el : Delete(split(text), word))
    {
        if(el != "!1!sign") cout << el;
    }

    return 0;
}
