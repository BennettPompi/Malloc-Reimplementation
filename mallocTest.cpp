#include <iostream>
#include "malloc.h"
using namespace std;

int main()
{
    int* x =(int*)mmalloc(sizeof(int));
    *x = 5;
    int* y =(int*)mmalloc(sizeof(int));
    *y = 10;
    cout << x << " " << &x << " " << *x << endl;
    cout << y << " " << &y << " " << *y << endl;
    mfree(x);
    mfree(y);
    
    return 0;
}