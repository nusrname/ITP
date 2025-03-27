#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

void combSort(vector<int>& arr, bool descending = false) 
{
    int gap = arr.size();
    bool swapped = true;

    while (gap > 1 || swapped)
    {
        gap = max(1, int(gap * 1.247));
        swapped = false;

        for (int i = 0; i + gap < arr.size(); i++) 
        {
            if ((descending && arr[i] < arr[i + gap]) || (!descending && arr[i] > arr[i + gap])) 
            {
                swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

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

int main()
{
    vector<vector<int>> matrix(10, vector<int>(10));
    read(matrix);

    for (int j = 0; j < 10; j++)
    {
        vector<int> column;
        for (int i = 0; i < 10; i++)
            column.push_back(matrix[i][j]);

        combSort(column, j % 3 == 2);

        for (int i = 0; i < 10; i++)
            matrix[i][j] = column[i];
    }

    print(matrix);

    cout << "Sorted matrix saved to sorted.txt" << endl;
    return 0;
}