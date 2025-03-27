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

// Функция для вывода текущего состояния игры
void displayGame(const string& word, const string& answer, int remainingAttempts, bool Type) 
{
    // Показываем загаданное слово с подчеркиваниями
    for (char c : word) 
    {
        if (answer.find(c) != string::npos)
            cout << c << " ";
        else
            cout << "_ ";
    }
    cout << "\n\n";
    if(!Type) cout << "Оставшиеся попытки: " << remainingAttempts << endl;

    // Выводим алфавит
    cout << "Оставшиеся буквы: ";
    for (char c = 'a'; c <= 'z'; c++) 
    {
        if (answer.find(c) == string::npos) 
        {
            cout << c << " ";
        }
    }
    cout << "\n\n";
}

// Функция для рисования виселицы
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
    string answer = "";  // Строка для угаданных букв
    int remainingAttempts = 6;  // Максимальное количество попыток для рисования виселицы

    int gameType;
    cout << "Выберите тип игры:\n1 - С ограничением по ходам\n2 - С рисованием виселицы\nВведите номер: ";
    cin >> gameType;
    cin.ignore();
    --gameType;

    while (remainingAttempts > 0) 
    {
        displayGame(word, answer, remainingAttempts, gameType);

        char choice;
        cout << "Введите букву (или '0' для ввода целого слова): ";
        cin >> choice;
        cin.ignore();

        if (choice == '0') 
        {
            string fullWord;
            cout << "Введите слово: ";
            cin >> fullWord;

            for (char& c : fullWord)
                c = tolower(c);

            if (fullWord == word)
            {
                cout << "Всё верно! Вы угадали слово!" << endl;
                break;
            }

            else
            {
                cout << "Неправильно! Игра закончена." << endl;
                break;
            }
        }
        else 
        {
            char letter = tolower(choice);

            if (answer.find(letter) != string::npos) 
            {
                cout << "Вы уже вводили эту букву." << endl;
            }
            else
            {
                answer += letter;

                // Проверяем, если буква есть в слове
                if (word.find(letter) == string::npos) 
                {
                    cout << "Этой буквы в слове нет." << endl;
                    remainingAttempts--;
                    if(gameType) drawHangman(remainingAttempts);
                }
                else
                {
                    cout << "Правильно! Буква '" << letter << "' есть в слове." << endl;
                }
            }
        }

        // Проверка на победу (если все буквы угаданы)
        bool wordGuessed = true;
        for (char c : word) {
            if (answer.find(c) == string::npos) {
                wordGuessed = false;
                break;
            }
        }

        if (wordGuessed)
        {
            cout << "Поздравляю! Вы угадали слово: " << word << "!" << endl;
            break;
        }
    }

    if (remainingAttempts == 0)
        cout << "Игра завершена! Вы проиграли. Загаданное слово было: " << word << "." << endl;
}
