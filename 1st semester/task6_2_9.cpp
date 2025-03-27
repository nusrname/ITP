#include <iostream>
#include <limits>
using namespace std;

template <typename T>
T** createarr(int n, int m) 
{
    T** arr = new T * [n];
    for (int i = 0; i < n; ++i) 
    {
        arr[i] = new T[m];
    }
    return arr;
}

template <typename T>
void deletearr(T** arr, int n)
{
    for (int i = 0; i < n; ++i) 
    {
        delete[] arr[i];
    }
    delete[] arr;
}

template <typename T>
void inputarr(T** arr, int n, int m) 
{
    cout << "Введите элементы массива:" << endl;
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < m; ++j) 
        {
            cin >> arr[i][j];
        }
    }
}

template <typename T>
void outputarr(T** arr, int n, int m) 
{
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < m; ++j) 
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

template <typename T>
void replaceRowsWithX(T** arr, int n, int m) 
{
    T minElement = numeric_limits<T>::max();
    bool* rowsToReplace = new bool[n] {false};
    T* x = new T[m];

    cout << "Введите строку для замены: " << endl;
    for (int i = 0; i < m; i++)
    {
        cin >> x[i];
    }
    // Поиск минимального элемента и строк для замены
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (arr[i][j] < minElement) 
            {
                minElement = arr[i][j];
            }
        }
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (arr[i][j] == minElement) 
            {
                rowsToReplace[i] = true;
                break;
            }
        }
    }

    // Замена строк
    for (int i = 0; i < n; ++i) 
    {
        if (rowsToReplace[i]) 
        {
            for (int j = 0; j < m; ++j) 
            {
                arr[i][j] = x[j];
            }
        }
    }
    delete[] x;
    delete[] rowsToReplace;
}

int main() 
{
    setlocale(LC_ALL, "rus");
    int n, m;

    cout << "Введите количество строк и столбцов: ";
    cin >> n >> m;

    // Работа с целыми числами
    cout << "Работа с целыми числами:" << endl;
    int** intarr = createarr<int>(n, m);
    inputarr(intarr, n, m);
    replaceRowsWithX(intarr, n, m);
    cout << "Массив после обработки:" << endl;
    outputarr(intarr, n, m);
    deletearr(intarr, n);

    // Работа с вещественными числами
    cout << "\nРабота с вещественными числами:" << endl;
    double** doublearr = createarr<double>(n, m);
    inputarr(doublearr, n, m);
    replaceRowsWithX(doublearr, n, m);
    cout << "Массив после обработки:" << endl;
    outputarr(doublearr, n, m);
    deletearr(doublearr, n);

    // Работа с символами
    cout << "\nРабота с символами:" << endl;
    char** chararr = createarr<char>(n, m);
    inputarr(chararr, n, m);
    replaceRowsWithX(chararr, n, m);
    cout << "Массив после обработки:" << endl;
    outputarr(chararr, n, m);
    deletearr(chararr, n);

    return 0;
}
