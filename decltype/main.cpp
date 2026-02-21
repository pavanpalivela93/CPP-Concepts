#include <iostream>
#include <type_traits>

template<typename T>
std::string checkType(T var) {
    if (std::is_reference_v<T>) {
        return "reference";
    } else {
        return "non-reference";
    }
}

int main(){
    int x = 10;
    int& ref = x; // ref is a reference to x

    auto y = x; // y is of type int
    auto& z = x; // z is of type int&, a reference to x
    auto w = ref; // w is of type int, a copy of x
    
    decltype(x) a = x; // z is of type int, same as
    decltype((y)) b = y; // w is of type int&, same as y

    std::cout << "x is type of: " << checkType<decltype(x)>(x) << std::endl;
    std::cout << "ref is type of: " << checkType<decltype(ref)>(ref) << std::endl;
    std::cout << "y is type of: " << checkType<decltype(y)>(y) << std::endl;
    std::cout << "z is type of: " << checkType<decltype(z)>(z) << std::endl;
    std::cout << "w is type of: " << checkType<decltype(w)>(w) << std::endl;
    std::cout << "a is type of: " << checkType<decltype(a)>(a) << std::endl;
    std::cout << "b is type of: " << checkType<decltype(b)>(b) << std::endl;
}
