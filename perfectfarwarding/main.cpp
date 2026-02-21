#include <iostream>

class Widget
{
public:
    template <typename T>
    Widget(T &&arg)
        : value(std::forward<T>(arg)) {}

private:
    std::string value;
};

void process(int &x)
{
    std::cout << "Lvalue\n";
}

void process(int &&x)
{
    std::cout << "Rvalue\n";
}

template <typename T>
void wrapper(T &&arg)
{
    process(std::forward<T>(arg));
}

// internal implementation of std::forward
template <typename T>
T &&forward(std::remove_reference_t<T> &arg)
{
    return static_cast<T &&>(arg);
}

int main()
{
    int x = 10;
    int &lref = x;                      // Lvalue reference
    int &&rref = 20;                    // Rvalue reference
    wrapper(x);                         // Lvalue
    wrapper(20);                        // Rvalue
    wrapper(lref);                      // Lvalue
    wrapper(rref);                      // Rvalue
    wrapper(std::move(rref));           // Rvalue
    wrapper(static_cast<int &&>(rref)); // Rvalue

    std::string s = "hello";
    Widget w1(s); // copy
    Widget w2("world");
}