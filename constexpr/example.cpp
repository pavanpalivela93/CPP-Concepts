#include <iostream>
constexpr int fib(int n)
{
    if (n <= 1)
        return n;

    return fib(n - 1) + fib(n - 2);
}

constexpr int add(int a, int b)
{
    return a + b;
}

int main()
{
    const int n = 11;
    constexpr int i = fib(n);
    constexpr int j = add(3, 5);
    std::cout << i << " " << j;

    return 0;
}