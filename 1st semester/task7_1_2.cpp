#include <iostream>
#include <string>
#include <set>
using namespace std;

int main()
{
    string input;
    cout << "Input string: ";
    getline(cin, input);

    string result;
    set<char> seen; 

    for (char ch : input)
    {
        if (seen.find(ch) == seen.end()) 
        { 
            result += ch;                  
            seen.insert(ch);               
        }
    }

    cout << "Result: " << result;
}