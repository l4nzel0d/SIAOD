#include <iostream>
#include <limits>
#include <bitset>

using namespace std;

int main() 
{
    const int size = sizeof(unsigned char) * 8; 
    int input;
    while (true)
    {
        cout << "Provide a number between 0 and 255: ";
        if (cin >> input && input >= 0 && input <= 255) break;
        
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input, try again\n";
    }

    unsigned char x = static_cast<unsigned char>(input);
    cout << "Binary representation: " << bitset<size>(x);
    unsigned char maska = 1; // маска вида 00000001
    x = x & (~(maska << 4));
    cout << "\nResult with 5th bit set to 0: " << (int) x;
    cout << "\nBinary representation: " << bitset<size>(x);
    
    return 0;
}