#include "Barge.h"
#include "Stack.h"
#include "Function.h"

//ИКМ по ЯП. Задача 11. Баржа. Работа со списками и своим классом. После всех операций найти максимальное количество бочек


int main() {
    try {
        printInstructions();

        // Ввод основных параметров с проверкой
        int numOperations = safeInputInt(
            "> Введите количество операций (N): ",
            1, 100000
        );

        int numCompartments = safeInputInt(
            "> Введите количество отсеков (K): ",
            1, 100000
        );

        int maxCapacity = safeInputInt(
            "> Введите максимальное количество бочек (P): ",
            1, 100000
        );

        // Создание объекта баржи
        Barge barge(numCompartments, maxCapacity);

        cout << "> Введите " << numOperations << " операций в формате:" << endl;
        cout << "  [Операция] [Номер отсека] [Тип топлива]" << endl;
        cout << "  Пример: + 1 5   (погрузить бочку типа 5 в отсек 1)" << endl;
        cout << "          - 2 10  (разгрузить бочку типа 10 из отсека 2)" << endl;

        // Обработка всех операций
        for (int i = 0; i < numOperations; i++) {
            char op;
            int compartmentNum, fuelType;

            cout << "Операция " << (i + 1) << "/" << numOperations << ": ";
            safeInputOperation(op, compartmentNum, fuelType, numCompartments);

            if (op == '+') {
                barge.load(compartmentNum, fuelType);
                cout << "  -> Погружена бочка: отсек " << compartmentNum
                    << ", тип " << fuelType << endl;
            }
            else if (op == '-') {
                barge.unload(compartmentNum, fuelType);
                cout << "  -> Разгружена бочка: отсек " << compartmentNum
                    << ", тип " << fuelType << endl;
            }
        }

        // Проверка состояния и вывод результата
        if (barge.hasError()) {
            cout << endl << "══════════════════════════════════════════════════" << endl;
            cout << "Результат: Error" << endl;

            // Детализация ошибки
            cout << "Причины возможных ошибок:" << endl;
            cout << "  - Попытка разгрузки из пустого отсека" << endl;
            cout << "  - Несоответствие типа топлива" << endl;
            cout << "  - Некорректный номер отсека" << endl;
            cout << "  - Превышение лимита бочек (" << maxCapacity << ")" << endl;
            cout << "  - Баржа не пуста в конце операций" << endl;
        }
        else {
            cout << endl << "══════════════════════════════════════════════════" << endl;
            cout << "Результат: " << barge.getMaxBarrels() << endl;
            cout << "Максимальное количество бочек: " << barge.getMaxBarrels() << endl;
            cout << "Статус: успешное завершение" << endl;
        }
    }
    // Обработка всех исключений
    catch (const exception& e) {
        cout << endl << "══════════════════════════════════════════════════" << endl;
        cout << "Критическая ошибка: " << e.what() << endl;
        cout << "Программа завершена" << endl;
    }
    return 0;
}