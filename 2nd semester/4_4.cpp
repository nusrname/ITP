#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// Рекурсивная поразрядная сортировка
void msdRadixSort(vector<int>& arr, int left, int right, int digitPlace)
{
    if (left >= right || digitPlace == 0) return;

    vector<vector<int>> buckets(10);

    for (int i = left; i <= right; i++) 
    {
        buckets[abs(arr[i]) / digitPlace % 10].push_back(arr[i]);
    }

    int index = left;
    for (int d = 0; d < 10; d++)
    {
        if (!buckets[d].empty())
        {
            for (int num : buckets[d])
            {
                arr[index++] = num;
            }
            msdRadixSort(arr, index - buckets[d].size(), index - 1, digitPlace / 10);
        }
    }
}

void PreparationForSorting(vector<int>& v)
{
    if (v.empty())return;
    int maxPos = 0, highestPlace = 1;

    for (int num : v)
        maxPos = max(maxPos, num);

    while (maxPos / highestPlace > 0) highestPlace *= 10;

    highestPlace /= 10;

     msdRadixSort(v, 0, v.size() - 1, highestPlace);
}

// Вспомогательная функция для сортировки массива
void radixSort(vector<int>& arr)
{
    vector<int> negative, positive;

    for (int num : arr)
    {
        if (num < 0)
            negative.push_back(-num);  // Сортируем по модулю, но отдельно
        else
            positive.push_back(num);
    }

    PreparationForSorting(negative);
    PreparationForSorting(positive);

    // Инвертируем отрицательные, чтобы вернуть правильный порядок
    for (int& num : negative) num = -num;
    reverse(negative.begin(), negative.end());

    // Объединяем отрицательные и положительные числа
    arr.clear();
    arr.insert(arr.end(), negative.begin(), negative.end());
    arr.insert(arr.end(), positive.begin(), positive.end());
}


int main()
{
    int n, t;
    vector<int> arr;

    cout << "Input count of numbers: ";
    cin >> n;
    cout << "Input numbers: ";
    for (int i = 0; i < n; i++)
    {
        cin >> t;
        arr.push_back(t);
    }

    radixSort(arr);

    cout << "Result: ";
    for (int num : arr) 
        cout << num << " ";
    cout << endl;

    return 0;
}
