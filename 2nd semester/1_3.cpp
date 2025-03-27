#include <iostream>
#include <vector>
#include <numeric>
#include <functional>
using namespace std;

int main()
{
    int n;
    cout << "Count: ";
    cin >> n;

    vector<int> v(n + 2);

    if (n > 0) v[0] = 0;
    if (n > 1) v[1] = 1;

    //numeric                                               functional
    partial_sum(v.begin(), v.end() - 2, v.begin() + 2, plus<int>());
    v.erase(v.begin(), v.begin() + 2);

    cout << "Result: ";
    for (int num : v)
        cout << num << " ";

}
