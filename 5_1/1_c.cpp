#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include <bitset>
using namespace std;

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    unsigned int x = 25; // сохраняется в виде 00000000 00000000 00000000 00011001
    const int n = sizeof(int)*8; // = 32 количество разрядов в числе типа int
    unsigned maska = (1 << n - 1); // 1 в старшем бите 32-разрядной сетки
    cout << "Начальный вид маски: " << bitset<n> (maska) << endl;
    cout << "Результат: ";
    for (int i = 1; i <= n; i++) // 32 раза по количеству разрядов
    {
        cout << ((x & maska) >> (n - i));
        /*побитовое И над числом x и маской, смещение результата на n-i разряда вправо,
        т.е. i-й разряд окажется самым правым в разрядной сетке, остальные биты будут нулевыми,
        а значит просто будет выведено значение i-го бита*/
        maska = maska >> 1; // смещаем 1 на один разряд правее в маске
    }
    cout << endl; // в итоге получаем на выходе двоичную запись исходного числа, в нашем случае числа 25
    system("pause");
    return 0;
}
