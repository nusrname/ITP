#include <iostream>
using namespace std;


int main() {
    setlocale(LC_ALL, "rus");
    int n;
    cout << "¬ведите степень многочлена n: ";
    cin >> n;
    n++;

    int * P =  new int[n + 1];
    int* deriv = new int[n];
    int* result = new int[2 * (n - 1)] {};

    cout << "¬ведите коэффициенты многочлена P(x) (от старшей степени к младшей): ";
    for (int i = 0; i < n; ++i) 
    {
        cin >> P[i];
    }

    //производна€
    for (int i = 0; i < n; ++i) 
    {
        deriv[i] = P[i] * i;
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j) 
        {
            result[i + j - 1] += P[i] * deriv[j];
        }
    }

    cout << "ћногочлен P(x) * P'(x): ";
    for (int i = 0; i < 2 * (n - 1); i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;

    delete[] P;
    delete[] deriv;
    delete[] result;

    return 0;
}
