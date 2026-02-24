#include <iostream>
#include "matrix.h"
int main()
{
    Matrix m = {{1, 2, 3}, {4, 5, 6}};
    m.print();
    Matrix m1 = m;
    m1 = m;
    return 0;
}