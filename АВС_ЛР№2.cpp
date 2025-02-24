#include <iostream>
#include <bitset>
#include <string>
#include <windows.h>
#include <cstdio> // Для sprintf_s

using namespace std;

string convert16BitToIEEE754(const string& binary) {
    if (binary.length() != 16) {
        cerr << "Ошибка: число должно содержать 16 бит!" << endl;
        return "";
    }

    // Разбираем биты
    int sign = binary[0] - '0';  // Знак (0 - положительное, 1 - отрицательное)
    int exponent = stoi(binary.substr(1, 5), nullptr, 2);  // Порядок (5 бит)
    int mantissa = stoi(binary.substr(6), nullptr, 2); // Мантисса (10 бит)

    // Преобразуем порядок в 8-битное представление IEEE 754 (сдвигаем на +127)
    int ieeeExponent = exponent == 0 ? 0 : (exponent - 15 + 127);

    // Формируем 32-битное число IEEE 754
    unsigned int ieee754 = (sign << 31) | (ieeeExponent << 23) | (mantissa << 13);

    // Преобразуем в шестнадцатеричную строку (безопасная версия sprintf)
    char hexStr[9];
    sprintf_s(hexStr, sizeof(hexStr), "%08X", ieee754);

    return string(hexStr);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string binaryInput;
    cout << "Введите 16-битное число (в двоичном формате): ";
    cin >> binaryInput;

    string ieee754Hex = convert16BitToIEEE754(binaryInput);
    if (!ieee754Hex.empty()) {
        cout << "Число в формате IEEE 754 (HEX): " << ieee754Hex << endl;
    }

    return 0;
}
