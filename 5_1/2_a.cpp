#include <cstdlib>
#include <iostream>
#include <limits>
#include <bitset>
#include <vector>
using namespace std;

int main()
{
    unsigned char bit_array = 0, one_mask = 1; // создание битового массива заполненного нулями и маски вида 00000001
    size_t SIZE;
    while (true) // запрос пользователя ввести количество чисел в последовательности
    {
        cout << "Enter array size between 1 and 8: ";
        if (cin >> SIZE && SIZE >= 1 && SIZE <= 8) break; // проверка введённого пользователем значения
        
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input, try again\n";
    }

    cout << "Enter an array of " << SIZE << " unique numbers between 0 and 7: "; // запрос пользователя ввеси последовательность чисел
    int curr_number;
    for (int i = 0; i < SIZE; i++)
    {
        while (true)
        {
            if (cin >> curr_number && curr_number >= 0 && curr_number <= 7) break; // проверка введённого пользователем значения
            
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid number, try again\n";
        }
        bit_array |= (one_mask << curr_number); // установка соответствующего бита в массиве в единицу
    }

    cout << "Sorted array:"; // проход по всем битам массива и вывод отсортированной последовательности
    for (int i = 0; i < 8; i++)
    {
        if (bit_array & (one_mask << i))
        {
            cout << " " << i;
        }
    }
}

