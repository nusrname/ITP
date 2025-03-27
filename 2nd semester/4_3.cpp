#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

void read(vector<vector<int>>& matrix)
{
    ifstream inputFile("Test.txt");

    if (!inputFile)
    {
        cerr << "Error opening input file!" << endl;
        exit(1);
    }

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            inputFile >> matrix[i][j];

    inputFile.close();
}

void print(vector<vector<int>>& matrix)
{
    ofstream outputFile("sorted.txt");

    if (!outputFile)
    {
        cerr << "Error opening output file!" << endl;
        exit(1);
    }

    for (const auto& row : matrix)
    {
        for (int num : row)
        {
            outputFile << num << '\t';
        }
        outputFile << endl;
    }

    outputFile.close();
}

void oddEvenSort(vector<int>& arr)
{
    bool sorted = false;
    while (!sorted) 
    {
        sorted = true;

        // Четные индексы
        for (int i = 0; i < arr.size() - 1; i += 2)
        {
            if (arr[i] < arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                sorted = false;
            }
        }
        // Нечетные индексы
        for (int i = 1; i < arr.size() - 1; i += 2)
        {
            if (arr[i] < arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                sorted = false;
            }
        }
    }
}

vector<vector<int>> getDiagonals(vector<vector<int>>& matrix, int n)
{
    vector<vector<int>> diagonals(2 * n - 1);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            diagonals[i - j + n - 1].push_back(matrix[i][j]);

    return diagonals;
}

void setDiagonals(vector<vector<int>>& matrix, vector<vector<int>>& diagonals, int n) 
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = diagonals[i - j + n - 1].back();
            diagonals[i - j + n - 1].pop_back();
        }
    }
}

int main()
{
    vector<vector<int>> matrix(10, vector<int>(10));
    read(matrix);

    vector<vector<int>> diagonals = getDiagonals(matrix, 10);
    for (auto& diag : diagonals) oddEvenSort(diag);
    setDiagonals(matrix, diagonals, 10);

    print(matrix);
    cout << "Sorted matrix saved to sorted.txt" << endl;
    return 0;
}