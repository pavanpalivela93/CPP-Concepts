#include <iostream>
#include <type_traits>

// It is implemented roughly like this internally:
//  template<typename T>
//  struct is_integral : std::false_type {};

// template<>
// struct is_integral<int> : std::true_type {};

// modern c++ way
// When to use what (rule of thumb)
// Use if constexpr → branching logic inside a function
// Use SFINAE → enable/disable entire overloads or APIs
// Use concepts (C++20) → best solution for constraints
//---------------------------------------------------------
// before C++ 14
template <typename T>
typename std::enable_if<std::is_integral_v<T>>::type
print(T value)
{
    std::cout << "T is integral: " << value << std::endl;
}

template <typename T>
typename std::enable_if_t<!std::is_integral_v<T>, void> // both line typenames are same, 2nd one is more simpler
print(T value)
{
    std::cout << "T is not integral:" << value << std::endl;
}

//---------------------------------------------------------
// Cleaner C++14 Version
template <typename T>
std::enable_if_t<std::is_lvalue_reference_v<T>>
printV(T &value)
{
    std::cout << "T is lvalue reference:" << value << std::endl;
}

template <typename T>
std::enable_if_t<std::is_rvalue_reference_v<T>>
printV(T &&value)
{
    std::cout << "T is rvalue reference:" << value << std::endl;
}

//---------------------------------------------------------
// Best modern C++ solution: if constexpr (C++17+)
// This avoids SFINAE entirely and is easier to read
template <typename T>
void printVal(T val)
{
    if constexpr (std::is_integral_v<T>) // constexpr isnt mandatory
        std::cout << "T is integral: " << val << std::endl;
    else
        std::cout << "T is not integral: " << val << std::endl;
}

//---------------------------------------------------------
// C++20 Concept version (best)
template <typename T>
    requires std::integral<T>
void printValue(T val)
{
    std::cout << "T is integral: " << val << std::endl;
}

template <typename T>
    requires(!std::integral<T>)
void printValue(T val)
{
    std::cout << "T is not integral: " << val << std::endl;
}

//---------------------------------------------------------
// Best practical solution (if constexpr, single function)
template <typename T>
void printWay1(T &&value)
{
    using U = std::remove_reference_t<T>;

    if constexpr (std::is_integral_v<U>)
    {
        if constexpr (std::is_lvalue_reference_v<T>)
            std::cout << "integral lvalue: ";
        else
            std::cout << "integral rvalue: ";
    }
    else if constexpr (std::is_floating_point_v<U>)
    {
        if constexpr (std::is_lvalue_reference_v<T>)
            std::cout << "floating lvalue: ";
        else
            std::cout << "floating rvalue: ";
    }
    else
    {
        if constexpr (std::is_lvalue_reference_v<T>)
            std::cout << "non-integral lvalue: ";
        else
            std::cout << "non-integral rvalue: ";
    }

    std::cout << value << '\n';
}

//---------------------------------------------------------
// Correct SFINAE overload set
// Integral lvalue
template <typename T>
std::enable_if_t<std::is_integral_v<T>>
printWay2(T &value)
{
    std::cout << "integral lvalue: " << value << '\n';
}

// Integral rvalue
template <typename T>
std::enable_if_t<std::is_integral_v<T>>
printWay2(T &&value)
{
    std::cout << "integral rvalue: " << value << '\n';
}

// Floating lvalue
template <typename T>
std::enable_if_t<std::is_floating_point_v<T>>
printWay2(T &value)
{
    std::cout << "floating lvalue: " << value << '\n';
}

// Floating rvalue
template <typename T>
std::enable_if_t<std::is_floating_point_v<T>>
printWay2(T &&value)
{
    std::cout << "floating rvalue: " << value << '\n';
}

// Non-integral, non-floating lvalue
template <typename T>
std::enable_if_t<!std::is_integral_v<T> && !std::is_floating_point_v<T>>
printWay2(T &value)
{
    std::cout << "other type lvalue: " << value << '\n';
}

// Non-integral, non-floating rvalue
template <typename T>
std::enable_if_t<!std::is_integral_v<T> && !std::is_floating_point_v<T>>
printWay2(T &&value)
{
    std::cout << "other type rvalue: " << value << '\n';
}

//---------------------------------------------------------
// Best C++20 solution
template <std::integral T>
void printWay3(T &value)
{
    std::cout << "integral lvalue: " << value << '\n';
}

template <std::integral T>
void printWay3(T &&value)
{
    std::cout << "integral rvalue: " << value << '\n';
}

template <std::floating_point T>
void printWay3(T &value)
{
    std::cout << "floating lvalue: " << value << '\n';
}

template <std::floating_point T>
void printWay3(T &&value)
{
    std::cout << "floating rvalue: " << value << '\n';
}
//---------------------------------------------------------
// use of constexpr
template <typename T>
void foo(T value)
{
    if constexpr (std::is_integral_v<T>)
    {
        std::cout << value + 1 << std::endl;
    }
    else if constexpr (std::is_floating_point_v<T>)
    {
        std::cout << value + 1.9 << std::endl;
    }
    else
    {
        std::cout << value.size() << std::endl; // only valid for containers
    }
}

template <typename T>
void foo1(T value)
{
    if (std::is_integral_v<T>)
    {
        std::cout << value + 1 << std::endl;
    }
    else if (std::is_floating_point_v<T>)
    {
        std::cout << value + 1.9 << std::endl;
    }
    else
    {
        std::cout << value.size() << std::endl; // only valid for containers
    }
}

//---------------------------------------------------------

int main()
{
    std::cout << std::is_integral<int>::value << "\n"; // 1     C++ 14
    // or
    std::cout << std::is_integral_v<int> << "\n";          // 1     C++17
    std::cout << std::is_integral<double>::value << "\n";  // 0     C++ 14
    std::cout << std::is_floating_point_v<double> << "\n"; // 1     C++17

    int x = 30;
    float y = 30.9;
    std::string str = "world";

    print(10);
    print(10.5);

    std::cout << std::endl;

    printVal(10);
    printVal(10.5);

    std::cout << std::endl;

    printValue(10);
    printValue(10.5);

    std::cout << std::endl;

    printWay1(10);
    printWay1(10.5);
    printWay1(x);
    printWay1(y);
    printWay1("hello");

    std::cout << std::endl;

    printWay2(11);
    printWay2(11.5);
    printWay2(x);
    printWay2(y);
    printWay2("hellooo");
    printWay2(std::string("helloooooooo"));
    printWay2(str);

    std::cout << std::endl;

    std::vector<int> v = {1, 2, 3, 4, 5};
    foo(10);
    foo(v);
    // foo1(10);
    // foo1(v);

    std::cout << std::endl;

    return 0;
}

// Type Classification Traits
//  | Trait                         | Meaning              |
//  | ----------------------------- | -------------------- |
//  | `std::is_integral<T>`         | Is integer type      |
//  | `std::is_floating_point<T>`   | Is float             |
//  | `std::is_arithmetic<T>`       | Integral OR floating |
//  | `std::is_pointer<T>`          | Is pointer           |
//  | `std::is_reference<T>`        | Is reference         |
//  | `std::is_lvalue_reference<T>` | Lvalue ref           |
//  | `std::is_rvalue_reference<T>` | Rvalue ref           |
//  | `std::is_array<T>`            | Is array             |
//  | `std::is_enum<T>`             | Is enum              |
//  | `std::is_class<T>`            | Is class             |
//  | `std::is_function<T>`         | Is function          |
//  | `std::is_same<T, U>`          | Same type?           |

// Type Transformation Traits
//  | Trait                      | What it does         |
//  | -------------------------- | -------------------- |
//  | `std::remove_const<T>`     | Removes const        |
//  | `std::remove_reference<T>` | Removes &            |
//  | `std::remove_pointer<T>`   | Removes *            |
//  | `std::decay<T>`            | Applies decay rules  |
//  | `std::add_const<T>`        | Adds const           |
//  | `std::add_pointer<T>`      | Adds *               |
//  | `std::make_signed<T>`      | Converts to signed   |
//  | `std::make_unsigned<T>`    | Converts to unsigned |

// Relationship Traits
//  | Trait                               | Meaning               |
//  | ----------------------------------- | --------------------- |
//  | `std::is_base_of<Base, Derived>`    | Inheritance check     |
//  | `std::is_convertible<T, U>`         | Convertible?          |
//  | `std::is_constructible<T, Args...>` | Can construct?        |
//  | `std::is_trivially_copyable<T>`     | Trivial copy?         |
//  | `std::is_move_constructible<T>`     | Has move constructor? |
//  | `std::is_copy_constructible<T>`     | Has copy constructor? |
