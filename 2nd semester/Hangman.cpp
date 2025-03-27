#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

vector<string> words = 
{
    "computer", "programming", "algorithm", "development", "technology",
    "universe", "explanation", "mathematics", "subscription", "engineering",
    "observation", "civilization", "measurement", "perspective", "inspiration"
};

// ������� ��� ������ �������� ��������� ����
void displayGame(const string& word, const string& answer, int remainingAttempts, bool Type) 
{
    // ���������� ���������� ����� � ���������������
    for (char c : word) 
    {
        if (answer.find(c) != string::npos)
            cout << c << " ";
        else
            cout << "_ ";
    }
    cout << "\n\n";
    if(!Type) cout << "���������� �������: " << remainingAttempts << endl;

    // ������� �������
    cout << "���������� �����: ";
    for (char c = 'a'; c <= 'z'; c++) 
    {
        if (answer.find(c) == string::npos) 
        {
            cout << c << " ";
        }
    }
    cout << "\n\n";
}

// ������� ��� ��������� ��������
void drawHangman(int attemptsLeft) 
{
    if (attemptsLeft == 6) cout << "  _______\n |       |\n |\n |\n |\n |\n_|_\n";
    if (attemptsLeft == 5) cout << "  _______\n |       |\n |       O\n |\n |\n |\n_|_\n";
    if (attemptsLeft == 4) cout << "  _______\n |       |\n |       O\n |       |\n |\n |\n_|_\n";
    if (attemptsLeft == 3) cout << "  _______\n |       |\n |       O\n |      /|\\\n |\n |\n_|_\n";
    if (attemptsLeft == 2) cout << "  _______\n |       |\n |       O\n |      /|\\\n |      /\n |\n_|_\n";
    if (attemptsLeft == 1) cout << "  _______\n |       |\n |       O\n |      /|\\\n |      / \\\n |\n_|_\n";
    if (attemptsLeft == 0) cout << "  _______\n |       |\n |       O\n |      /|\\\n |      / \\\n |  GAME OVER\n_|_\n";
}

int main() 
{
    setlocale(LC_ALL, "rus");
    srand(time(0)); 

    string word = words[rand() % words.size()];
    string answer = "";  // ������ ��� ��������� ����
    int remainingAttempts = 6;  // ������������ ���������� ������� ��� ��������� ��������

    int gameType;
    cout << "�������� ��� ����:\n1 - � ������������ �� �����\n2 - � ���������� ��������\n������� �����: ";
    cin >> gameType;
    cin.ignore();
    --gameType;

    while (remainingAttempts > 0) 
    {
        displayGame(word, answer, remainingAttempts, gameType);

        char choice;
        cout << "������� ����� (��� '0' ��� ����� ������ �����): ";
        cin >> choice;
        cin.ignore();

        if (choice == '0') 
        {
            string fullWord;
            cout << "������� �����: ";
            cin >> fullWord;

            for (char& c : fullWord)
                c = tolower(c);

            if (fullWord == word)
            {
                cout << "�� �����! �� ������� �����!" << endl;
                break;
            }

            else
            {
                cout << "�����������! ���� ���������." << endl;
                break;
            }
        }
        else 
        {
            char letter = tolower(choice);

            if (answer.find(letter) != string::npos) 
            {
                cout << "�� ��� ������� ��� �����." << endl;
            }
            else
            {
                answer += letter;

                // ���������, ���� ����� ���� � �����
                if (word.find(letter) == string::npos) 
                {
                    cout << "���� ����� � ����� ���." << endl;
                    remainingAttempts--;
                    if(gameType) drawHangman(remainingAttempts);
                }
                else
                {
                    cout << "���������! ����� '" << letter << "' ���� � �����." << endl;
                }
            }
        }

        // �������� �� ������ (���� ��� ����� �������)
        bool wordGuessed = true;
        for (char c : word) {
            if (answer.find(c) == string::npos) {
                wordGuessed = false;
                break;
            }
        }

        if (wordGuessed)
        {
            cout << "����������! �� ������� �����: " << word << "!" << endl;
            break;
        }
    }

    if (remainingAttempts == 0)
        cout << "���� ���������! �� ���������. ���������� ����� ����: " << word << "." << endl;
}
