#include <iostream>
#include <limits>

using namespace std;

int main() 
{
    unsigned char x = 255;
    unsigned char maska = 1;
    x = x & (~(maska << 4));
    cout << (int) x;
    return 0;
}