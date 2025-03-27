#include <iostream>
using namespace std;

void tree(int n, int startCount)
{
    if (n > startCount + 1) 
    {
        return;
    }
    for (int i = 0; i <= n; i++)
    {
		for (int j = 0; j <= 2 * (startCount - i + 1); j++)
		{
			cout << ' ';
		}
        for (int k = 0; k <= (2 * i - 2); k++)
        {
            cout << "* ";
        }
        i != n ? cout << endl : cout << "";
    }
    tree(++n, startCount);
}

int main()
{
    int n;
    cout << "Input n: ";
    cin >> n;

    tree(2, n);
}