#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
	map<string, int> m;
	string t;
	int n;

	ifstream in("Test.txt");

	while (in >> t)
		m[t]++;

	vector<pair<string, int>> vec(m.begin(), m.end());

	sort(vec.begin(), vec.end(), 
		[](const pair<string, int>& a, const pair<string, int>& b) 
		{
			return a.second > b.second;
		});

	cout << "Count: ";
	cin >> n;
	for (pair<string, int> el : vec)
	{
		if (!n) break;
		cout << el.first << ' ' << el.second << endl;
		n--;
	}

	in.close();
}