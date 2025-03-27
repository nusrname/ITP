//45 1 10 4 2 45 8 19 9 1
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	vector<int> v;
	int n;
	cout << "Count of elements:";
	cin >> n;

	cout << "Elements:\t";
	for (int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		v.push_back(x);
	}

	vector<int> first = v;
	auto max_elem = *max_element(first.begin(), first.end());
	first.erase(remove(first.begin(), first.end(), max_elem), first.end());

	vector<int> second = v;

	auto min_elem = *min_element(second.begin(), second.end());
	for_each(second.begin(), second.end(), 
		[min_elem](int& x)
		{
			if (x % 2 == 0)
				x = min_elem;
		});

	sort(second.begin(), second.end());

	second.erase(unique(second.begin(), second.end()), second.end());

	cout << "First:\t\t";
	for (int x : first)
		cout << x << " ";
	cout << endl;

	cout << "Second:\t\t";
	for (int x : second)
		cout << x << " ";
}
