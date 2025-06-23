#pragma once
#include <iostream>
#include <stdexcept>
#include <limits>
#include <cctype>
using namespace std;

// Узел для реализации стека
class StackNode {
public:
    int fuelType;      // Тип топлива в бочке
    StackNode* next;   // Указатель на следующий элемент в стеке

    // Конструктор узла
    StackNode(int type) : fuelType(type), next(nullptr) {}
};

// Класс стека на основе связного списка
class Stack {
private:
    StackNode* topNode; 

public:
    // Конструктор: инициализация пустого стека
    Stack() : topNode(nullptr) {}

    // Деструктор: освобождение памяти всех элементов стека
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    // Проверка, пуст ли стек
    bool isEmpty() const {
        return topNode == nullptr;
    }

    // Добавление элемента на вершину стека
    void push(int type) {
        StackNode* newNode = new StackNode(type);
        newNode->next = topNode;
        topNode = newNode;
    }

    // Удаление элемента с вершины стека
    void pop() {
        if (isEmpty()) throw runtime_error("Попытка извлечения из пустого стека");
        StackNode* temp = topNode;
        topNode = topNode->next;
        delete temp;
    }

    // Получение значения верхнего элемента стека
    int top() {
        if (isEmpty()) throw runtime_error("Попытка доступа к вершине пустого стека");
        return topNode->fuelType;
    }
};

