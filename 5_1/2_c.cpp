#include <cstdlib>
#include <iostream>
#include <limits>
#include <bitset>
#include <vector>
using namespace std;

int main()
{
    const size_t SIZE = 64;
    vector<int> numbers(SIZE); // создание вектора целочисленных чисел
    int max_num = -1;

    cout << "Enter an array of " << SIZE << " numbers: "; // запрос пользователя ввести последовательность из 64 чисел
    for (auto &el: numbers)
    {
        cin >> el; // сохранение введённого числа в вектор
        if (el > max_num) max_num = el; // обновление значения максимального введённого числа 
    }

    size_t bytes_size = (max_num / 8) + 1; // подсчёт необходимого количества байтов для последующих операций
    unsigned char bytes[bytes_size]; // создание массива из байтов
    for (int i = 0; i < bytes_size; i++) 
    {
        bytes[i] = 0; // установка каждого байта в нулевое значение (а соответственно и обнуление всех битов)
    }

    for (auto &el: numbers) // проход по вектору введённых чисел
    {
        bytes[el / 8] |= (1 << (el%8)); // установка нужного бита нужного бита в 1 в соотвествии с числом из вектора
    }

    cout << "\nBit array (Left byte has the most significant bit): "; // вывод массива байтов в двоичном виде
    for (int i = 0; i < bytes_size; i++)
    {
        cout << bitset<8>(bytes[bytes_size - 1 - i]) << " ";
    }

    cout << "\n\nSorted array: ";
    unsigned char mask;
    for (int i = 0; i < bytes_size; i++) // проход по всем байтам из массива
    {
        mask = 1; // создание маски вида 00000001
        for (int j = 0; j < 8; j++) // проход по всем битам байта
        {
            if (bytes[i] & mask) // если текущий бит установлен в единицу
            {
                cout << i*8 + j << " "; // вывод соответствующего числа
            }
            mask <<= 1; // сдвиг единицы в маске на одну позицию влево
        }
    }
}
