#pragma once
#include <iostream>
#include <stdexcept>
#include <limits>
#include <cctype>
using namespace std;


// Функция проверки корректности номера отсека
bool validateOperation(const Barge& barge, int compartmentNum) {
    return (compartmentNum >= 1 && compartmentNum <= barge.numCompartments);
}

// Функция для безопасного ввода целого числа
int safeInputInt(const string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        cout << prompt;
        if (!(cin >> value)) {
            // Очистка потока при некорректном вводе
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка: введите целое число!" << endl;
            continue;
        }

        // Проверка диапазона
        if (value < minVal || value > maxVal) {
            cout << "Ошибка: значение должно быть от "
                << minVal << " до " << maxVal << "!" << endl;
            continue;
        }
        break;
    }
    return value;
}

// Функция для безопасного ввода операции (ИСПРАВЛЕНА)
void safeInputOperation(char& op, int& compartmentNum, int& fuelType, int maxCompartments) {
    string input;
    while (true) {
        // Ввод операции
        cin >> input;
        if (input.size() != 1 || (input[0] != '+' && input[0] != '-')) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка: операция должна быть '+' или '-'!" << endl;
            cout << "Повторите ввод операции: ";
            continue;
        }
        op = input[0];
        break;
    }

    // Ввод номера отсека
    while (true) {
        if (!(cin >> compartmentNum)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка: номер отсека должен быть числом!" << endl;
            cout << "Повторите ввод номера отсека: ";
            continue;
        }
        if (compartmentNum < 1 || compartmentNum > maxCompartments) {
            cout << "Ошибка: номер отсека должен быть от 1 до "
                << maxCompartments << "!" << endl;
            cout << "Повторите ввод номера отсека: ";
            continue;
        }
        break;
    }

    // Ввод типа топлива
    while (true) {
        if (!(cin >> fuelType)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка: тип топлива должен быть числом!" << endl;
            cout << "Повторите ввод типа топлива: ";
            continue;
        }
        break;
    }
}

// Функция для вывода инструкций
void printInstructions() {
    cout << "╔══════════════════════════════════════════════════════════╗" << endl;
    cout << "║              МОДЕЛИРОВАНИЕ РАБОТЫ БАРЖИ                 ║" << endl;
    cout << "╠══════════════════════════════════════════════════════════╣" << endl;
    cout << "║ Программа моделирует работу баржи с отсеками, где каждая ║" << endl;
    cout << "║ операция - это погрузка или разгрузка бочек с топливом. ║" << endl;
    cout << "║ Отсеки работают по принципу стека (LIFO):               ║" << endl;
    cout << "║  - Можно разгружать только последнюю добавленную бочку  ║" << endl;
    cout << "║                                                        ║" << endl;
    cout << "║ Требования:                                            ║" << endl;
    cout << "║  1. Количество отсеков: 1-100000                       ║" << endl;
    cout << "║  2. Максимальное количество бочек: 1-100000            ║" << endl;
    cout << "║  3. Тип топлива - целое число                          ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════╝" << endl;
}