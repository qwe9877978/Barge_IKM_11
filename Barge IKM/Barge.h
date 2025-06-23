#pragma once
#include <iostream>
#include <stdexcept>
#include <limits>
#include <cctype>
using namespace std;


// Класс для моделирования баржи
class Barge {
private:
    int numCompartments;      // Количество отсеков (K)
    int maxBarrels;           // Максимальное допустимое количество бочек (P)
    long long currentBarrels; // Текущее количество бочек на барже
    long long maxBarrelsEver; // Максимальное количество бочек за все время
    Stack** compartments;     // Массив стеков для отсеков
    bool errorOccurred;       // Флаг возникновения ошибки

    // Объявление дружественной функции для валидации операций c использованием friend
    friend bool validateOperation(const Barge& barge, int compartmentNum);

public:
    // Конструктор баржи
    Barge(int compartmentsCount, int maxCapacity) :
        numCompartments(compartmentsCount),
        maxBarrels(maxCapacity),
        currentBarrels(0),
        maxBarrelsEver(0),
        compartments(nullptr),
        errorOccurred(false)
    {
        try {
            compartments = new Stack * [numCompartments + 1];

            for (int i = 0; i <= numCompartments; i++) {
                compartments[i] = nullptr;
            }

            for (int i = 1; i <= numCompartments; i++) {
                compartments[i] = new Stack();
            }
        }
        catch (const bad_alloc& e) {
            errorOccurred = true;
            cleanup();
            throw runtime_error("Ошибка выделения памяти");
        }
    }

    // Деструктор: освобождение ресурсов
    ~Barge() {
        cleanup();
    }

    // Очистка ресурсов баржи
    void cleanup() {
        if (compartments) {
            for (int i = 1; i <= numCompartments; i++) {
                if (compartments[i]) {
                    delete compartments[i];
                }
            }
            delete[] compartments;
            compartments = nullptr;
        }
    }

    // Обработка операции погрузки бочки
    void load(int compartmentNum, int fuelType) {
        if (errorOccurred) return;

        if (!validateOperation(*this, compartmentNum)) {
            errorOccurred = true;
            return;
        }

        currentBarrels++;

        if (currentBarrels > maxBarrels) {
            errorOccurred = true;
            return;
        }

        try {
            compartments[compartmentNum]->push(fuelType);

            if (currentBarrels > maxBarrelsEver) {
                maxBarrelsEver = currentBarrels;
            }
        }
        catch (...) {
            errorOccurred = true;
        }
    }

    // Обработка операции разгрузки бочки
    void unload(int compartmentNum, int expectedFuelType) {
        if (errorOccurred) return;

        if (!validateOperation(*this, compartmentNum)) {
            errorOccurred = true;
            return;
        }

        try {
            if (compartments[compartmentNum]->isEmpty()) {
                errorOccurred = true;
                return;
            }

            int actualFuelType = compartments[compartmentNum]->top();
            if (actualFuelType != expectedFuelType) {
                errorOccurred = true;
                return;
            }

            compartments[compartmentNum]->pop();
            currentBarrels--;
        }
        catch (...) {
            errorOccurred = true;
        }
    }

    // Проверка наличия ошибок в работе баржи
    bool hasError() const {
        return errorOccurred || (currentBarrels != 0);
    }

    // Получение максимального количества бочек
    long long getMaxBarrels() const {
        return maxBarrelsEver;
    }
};

