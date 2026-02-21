#include <iostream>
#include <tuple>

template <typename... Args>
void sizeOfArgs(Args... args)
{
    std::cout << std::endl;
    std::cout << "Number of arguments: " << sizeof...(args) << std::endl;
    std::cout << "Number of Arguments: " << sizeof...(Args) << std::endl;
    std::cout << std::endl;
}

template <typename... Args>
void print(Args &&...args)
{
    auto tup = std::make_tuple(std::forward<Args>(args)...);

    // for (auto &arg : tup)
    // {
    //     std::cout << "Argument: " << arg << std::endl;
    //     // printType(arg);
    // }
    // (printType(std::get<Is>(tup)), ...);
    std::cout << std::get<0>(tup) << '\n';
    std::cout << std::get<1>(tup) << '\n';
    std::cout << std::get<2>(tup) << '\n';
    std::cout << std::get<3>(tup) << '\n';
    std::cout << std::get<4>(tup) << '\n';
}

template <typename T>
void printType(const T &val)
{
    std::cout << "val: " << val << std::endl;
    std::cout << "Type: " << typeid(T).name() << std::endl;
}

template <typename... Args>
void printArgs(Args &&...args)
{
    std::cout << "Arguments: ";
    ((std::cout << args << " "), ...); // Fold expression to print all arguments
    std::cout << std::endl;

    std::cout << "Arguments: ";
    (std::cout << ... << args); // Another fold expression to print all arguments without spaces
    std::cout << std::endl;

    (printType(std::forward<Args>(args)), ...); // Fold expression to call printType for each argument
    std::cout << std::endl;
}

int main()
{
    sizeOfArgs(1.23, 9, "Hello", true);
    printArgs(1.23, 9, "Hello", true);
    print(1.2, 19, "Hellooooo", true, 3.14l);
    return 0;
}