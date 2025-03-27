//Are you ok? Yes, I do! I'm just like you. What about you? I don't know.

#include <iostream>
#include <string>
#include <set>
using namespace std;

set<string> fragmentation(string text)
{
	set<string> words;
	string buf = "";

	for (int i = 0; i < text.length(); i++)
	{
		if (text[i] != ' ' && text[i] != ',') 
			buf += tolower(text[i]);
		else
		{
			words.insert(buf);
			buf = "";
		}
	}
	words.insert(buf);

	return words;
}


int main()
{
	string text, sentence = "";
	set<string> q_sent, other_sent, buf;
	cout << "Your text: ";
	getline(cin, text);
	cout << endl;

	for (int i = 0; i < text.size(); i++)
	{
		if (text[i] != '!' && text[i] != '.' && text[i] != '?')
			sentence += text[i];
		else 
		{
			buf = fragmentation(sentence);
			if (text[i] == '?')
				q_sent.insert(buf.begin(), buf.end());
			else
				other_sent.insert(buf.begin(), buf.end());
			sentence = "";
		}
	}
	
	for (auto el : other_sent) 
		if (q_sent.find(el) == q_sent.end())
			cout << el << endl;
}
