#include <iostream>

// constexpr can also be used with functions
constexpr int square(int n)
{
    return n * n;
}

int main()
{
    constexpr int x = 10;    // x is a compile-time constant
    constexpr int y = x * 2; // y is also a compile-time constant

    constexpr int z = square(5); // z is a compile-time constant, evaluated at compile time
    int w = square(5);           // w is a runtime variable, evaluated at runtime
    int u = square(x);           // u is a runtime variable, evaluated at runtime

    int a = 5;
    int b = square(a); // b is a runtime variable, evaluated at runtime

    std::cout << "Square of 5: " << square(5) << std::endl; // runtime evaluation of square function

    // The following line would cause a compilation error because z is not a compile-time constant
    // int z = square(x); // Error: z must be initialized with a compile-time constant expression
    // constexpr int test = square(a);
}