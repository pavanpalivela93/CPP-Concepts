#include <iostream>

template<typename... Args>
int multiply_and_add(Args... args)
{
    return (... * args) + (args * ...);
}

template<typename... Args>
int multiply(Args... args)
{
    return (10 * ... * args);
}

template<typename... Args>
int add(Args... args)
{
    return (args + ... + 120);
}

template<typename... Args>
int add1(Args... args)
{
    return (args + ...);
}

template<typename... Args>
int add2(Args... args)
{
    return ( ... + args);
}


int main()
{
    int result = multiply_and_add(1, 2, 3, 4, 5);
    std::cout << "multiply_and_add Result: " << result << std::endl;
    int result2 = multiply(1, 2, 3, 4, 5);
    std::cout << "Multiply Result: " << result2 << std::endl;
    int result3 = add(1, 2, 3, 4, 5);
    std::cout << "Add Result: " << result3 << std::endl;
    int result4 = add1(1, 2, 3, 4, 5);
    std::cout << "Add1 Result: " << result4 << std::endl;
    int result5 = add2(1, 2, 3, 4, 5);
    std::cout << "Add2 Result: " << result5 << std::endl;
    return 0;
}