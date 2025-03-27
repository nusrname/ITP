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
    cout << "������� �������� �������:" << endl;
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
    bool* rowsToReplace = new bool[n] {true};
    T* x = new T[m];

    cout << "������� ������ ��� ������: " << endl;
    for (int i = 0; i < m; i++)
    {
        cin >> x[i];
    }
    // ����� ������� �������� � ����� ��� ������
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (int(arr[i][j] / 2.0) != int((arr[i][j] - 1) / 2.0))
            {
                rowsToReplace[i] = false;
                break;
            }
        }
    }

    // ������ �����
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

    cout << "������� ���������� ����� � ��������: ";
    cin >> n >> m;

    // ������ � ������ �������
    cout << "������ � ������ �������:" << endl;
    int** intarr = createarr<int>(n, m);
    inputarr(intarr, n, m);
    replaceRowsWithX(intarr, n, m);
    cout << "������ ����� ���������:" << endl;
    outputarr(intarr, n, m);
    deletearr(intarr, n);

    // ������ � ������������� �������
    cout << "\n������ � ������������� �������:" << endl;
    double** doublearr = createarr<double>(n, m);
    inputarr(doublearr, n, m);
    replaceRowsWithX(doublearr, n, m);
    cout << "������ ����� ���������:" << endl;
    outputarr(doublearr, n, m);
    deletearr(doublearr, n);

    return 0;
}
