#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

void countingSort(vector<int>& row)
{
    int minVal = *min_element(row.begin(), row.end());
    int maxVal = *max_element(row.begin(), row.end());
    int range = maxVal - minVal + 1;

    vector<int> count(range, 0);

    for (int num : row) 
        count[num - minVal]++;

    int index = 0;
    for (int i = 0; i < range; i++)
    {
        while (count[i] > 0)
        {
            row[index++] = i + minVal;
            count[i]--;
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
    
    vector<int> temp;
    for (auto& row : matrix) 
    {
        for (int el : row)
            temp.push_back(el);
    }

    countingSort(temp);

    for (int i = 0; i < 100; i++) 
    {
        matrix[i / 10][i % 10] = temp[i];
    }
        
   
    print(matrix);

    cout << "Sorted matrix saved to sorted.txt" << endl;
    return 0;
}
