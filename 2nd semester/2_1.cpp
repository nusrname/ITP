#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() 
{
	int n;
	string t;
	set<int> s1, s2;
	vector<string> v;

	cout << "Count: ";
	cin >> n;
	cout << "Elements: ";
	for (int i = 0; i < n; i++)
	{
		cin >> t;
		cin.ignore();
		v.push_back(t);
	}
	cout << endl;
	
	for (string num: v)
	{
		for (char c : num) 
		{
			if (num.size() == 2)s2.insert(int(c - 48));
			else s1.insert(int(c - 48));
		}
	}


	cout << "Result: ";
	for (int n: s1)
	{
		if (s2.find(n) == s2.end())cout << n << ' ';
	}
}