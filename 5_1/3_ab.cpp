#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

int main()
{
    vector<unsigned char> bytes;
    size_t byte_size = sizeof(unsigned char) * 8;
    string input_file_name;
    cout << "Enter input file name: ";
    cin >> input_file_name;
    auto start_time = chrono::high_resolution_clock::now(); // начало отсчёта времени выполнения
    ifstream input_file(input_file_name);
    if (input_file.is_open()) // проверка успешного открытия файла для считывания
    {
        int num;
        while (input_file >> num) // считывается каждое число из файла
        {
            // если текущего количества байтов в векторе не хватает чтобы отметить число, добавить ещё один байт
            while (num  >= (bytes.size() * byte_size)) 
            {
                bytes.push_back(0);
            }
            bytes[num / byte_size] |= (1 << (num % byte_size)); // установка соответствующего бита в единицу
        } 
        input_file.close(); // закрываем файл
    }
    else 
    {
        cerr << "Error reading input file";
        return 1;
    }

    unsigned char mask;
    ofstream output_file("output.txt"); 
    if (output_file.is_open()) // проверка успешного создания и открытия выходного файла
    {
        for (int i = 0; i < bytes.size(); i++) // проход по всем байтам
        {
            mask = 1; // создание маски вида 00000001
            for (int j = 0; j < byte_size; j++) // проход по всем битам
            {
                if (bytes[i] & mask) // если текущий бит установлен в 1
                {
                    output_file << i*byte_size + j << "\n"; // выписывание соответствующего числа
                }
                mask <<= 1;
            }
        }
        output_file.close(); // сохраняем и закрываем файл
    }
    else
    {
        cerr << "Error creating output file";
        return -1;
    }
    auto end_time = chrono::high_resolution_clock::now(); // конец времени отсчёта выполнения
    auto time_delta = chrono::duration_cast<chrono::milliseconds>(end_time - start_time); // подсчёт времени выполнения
    cout << "Completion time in milliseconds: " << time_delta.count(); // вывод времени выполнения
    cout << "\nRAM utilization in bits: " << bytes.size() * byte_size; // вывод затраченного количества ОЗУ
};