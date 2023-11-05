#include <iostream>
using namespace std;
int main()
{
    uint32_t x = 255;
    uint8_t y = x;
    cout << x << " " << unsigned(y) << (x == y) << endl; 
}