#include <iostream>
constinit int globalCounter = 0;
consteval int safe_div(int a, int b)
{
    if (b == 0)
        throw "Division by zero";
    return a / b;
}

consteval int add(int a, int b)
{
    return a + b;
}

constexpr int sub(int a, int b)
{
    return a - b;
}

template <int N>
consteval int get()
{
    return N * 2;
}

consteval int foo(int x) { return x; }

consteval int bar(int x)
{
    return foo(x);
}

int main()
{
    int a = 9;
    const int x = 5;
    const int y = 10;
    constexpr int result = sub(3, 4);
    constexpr int val = add(x, y);
    int res1 = add(5, 4); // This is valid because 'add' is a consteval function and evaluated at compile time
    int res = sub(a, 4);  // This is valid because 'sub' is a constexpr function but evaluated at run time
    // int res = add(a, 4); // This will cause a compile-time error because 'a' is not a constant expression

    constexpr int b = safe_div(10, 2); // OK
    // constexpr int y = safe_div(10, 0); // ❌ compile-time error

    // Static Initialization Order Fiasco
    //  file1.cpp
    //  int x = getValue();

    // file2.cpp
    // int y = x;
    // constinit int b = add(3, 4); //error because constinit variables cannot be initialized with consteval functions, can only be initialized as Global/static variable
    constexpr int c = get<5>(); // ✔ This is valid because 'get' is a consteval function and evaluated at compile time

    return 0;
}