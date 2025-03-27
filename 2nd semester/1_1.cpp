#include <iostream>
#include <vector>
using namespace std;

int main()
{
	vector<int> lst = { 1, 1, 10, 4, 2, 45, 8, 19, 9, 1 };
	
	int min = 100000000;

	for (int i = 0; i < lst.size(); i++)
	{
		if (lst[i] < min)min = lst[i];
	}
	for (int i = 0; i < lst.size(); i++)
	{
		if (lst[i] == min) lst[i] = 0;
		cout << lst[i] << ' ';
	}
}