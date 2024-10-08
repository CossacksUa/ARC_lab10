#include <iostream>

int main() {
    float x = 5.0f;  // Значення x
    float y;         // Переменная для хранения результата
    float CONST1 = 3000.0f; // Константа 3000
    float CONST2 = 2.0f;    // Константа 2
    float CONST3 = 2.5f;    // Константа 2.5
    float CONST4 = 3.6f;    // Константа 3.6
    float CONST5 = 7.5f;    // Константа 7.5

    __asm {
        finit                   // Очищення регістрів сопроцессора

        // Числитель: 3000 - 2x^2 + 2.5x
        fld x                   // Загружаем значение x
        fmul st, st             // x * x = x^2
        fmul CONST2             // 2 * x^2
        fld x                   // Загружаем x
        fmul CONST3             // 2.5 * x
        fsubp st(1), st(0)     // (3000 - 2 * x^2 + 2.5 * x)

        // Сохраняем результат числителя в стеке
        fld CONST1              // Загружаем 3000
        fsubp st(1), st(0)      // 3000 - (2 * x^2 - 2.5 * x)

        // Знаменатель: x^2 + 3.6x - 7.5
        fld x                   // Загружаем x
        fmul st, st             // x * x = x^2
        fld x                   // Загружаем x
        fmul CONST4             // 3.6 * x
        faddp st(1), st(0)      // x^2 + 3.6 * x
        fld CONST5              // Загружаем 7.5
        fsubp st(1), st(0)      // (x^2 + 3.6 * x - 7.5)

        // Деление числителя на знаменатель
        fdivp st(1), st         // (числитель)/(знаменатель)
        fstp y                  // Сохраняем результат в y
    }

    // Вывод результата
    std::cout << "y = " << y << std::endl;

    return 0; // Возвращаем значение 0
}
