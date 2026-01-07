// [file name]: bruting.cpp
#include <iostream>
#include <string>
#include <chrono>
#include <windows.h>

using namespace std;

const string ALL_CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+[]{}|;:,.<>?/";

// Генерация следующей комбинации (как счетчик)
string nextAttempt(string current, const string& charSet) 
{
    int i = current.length() - 1;
    
    while (i >= 0) 
    {
        size_t pos = charSet.find(current[i]);
        if (pos == charSet.length() - 1) 
        {
            current[i] = charSet[0];
            i--;
        } 
        else 
        {
            current[i] = charSet[pos + 1];
            return current;
        }
    }
    
    return charSet[0] + current;
}

// Брутфорс атака (учебная)
void bruteForceAttack(const string& password, const string& charSet) 
{
    auto startTime = chrono::high_resolution_clock::now();
    
    string attempt = "";
    if (!password.empty()) 
    {
        attempt = string(1, charSet[0]);
    }
    
    int attempts = 0;
    
    // Настройка вывода
    int displayEvery = 1000;
    cout << "Показывать каждую попытку? (1 - да, 0 - нет): ";
    int showAll;
    cin >> showAll;
    
    if (!showAll) 
    {
        cout << "Показывать каждую N-ную попытку. Введи N: ";
        cin >> displayEvery;
    }
    
    cout << "Начинаем перебор:" << endl;
    
    while (attempt != password) 
    {
        attempts++;
        
        if (showAll || attempts % displayEvery == 0) 
        {
            cout << "Попытка #" << attempts << ": " << attempt << endl;
        }
        
        // Ограничение для демо
        if (attempts > 10000000) 
        {
            cout << "Слишком много попыток. Пароль сложный." << endl;
            return;
        }
        
        attempt = nextAttempt(attempt, charSet);
    }
    
    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
    
    cout << "Найден пароль: " << attempt << endl;
    cout << "Попыток: " << attempts << endl;
    cout << "Время: " << duration << " мс" << endl;
    
    // Оценка сложности
    if (duration < 1000) 
    {
        cout << "Пароль слабый!" << endl;
    } 
    else 
    {
        cout << "Пароль нормальный." << endl;
    }
}

int main() 
{
    SetConsoleOutputCP(CP_UTF8);
    
    string password;
    cout << "Введи пароль для теста: ";
    cin >> password;
    
    cout << "Выбери набор символов:" << endl;
    cout << "1. Только цифры" << endl;
    cout << "2. Буквы и цифры (маленькие)" << endl;
    cout << "3. Буквы и цифры (все)" << endl;
    cout << "4. Все символы" << endl;
    
    int choice;
    cin >> choice;
    
    string charSet;
    switch (choice) 
    {
        case 1:
            charSet = "0123456789";
            break;
        case 2:
            charSet = "abcdefghijklmnopqrstuvwxyz0123456789";
            break;
        case 3:
            charSet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
            break;
        case 4:
            charSet = ALL_CHARS;
            break;
        default:
            cout << "Неправильный выбор, используем цифры." << endl;
            charSet = "0123456789";
    }
    
    bruteForceAttack(password, charSet);
    
    return 0;
}