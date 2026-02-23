#include <iostream>
#include <initializer_list>

// Conceptually, it is something like:
template <class T>
class initializer_list
{
    const T *data;
    size_t size;
};

class MyArray
{
    int *data;
    size_t size;

public:
    MyArray(std::initializer_list<int> list)
    {
        size = list.size();
        data = new int[size];

        size_t i = 0;
        for (int value : list)
            data[i++] = value;
    }

    void print() const
    {
        for (size_t i = 0; i < size; i++)
            std::cout << data[i] << " ";
    }

    ~MyArray()
    {
        delete[] data;
    }
};

void print(std::initializer_list<int> list)
{
    for (auto v : list)
        std::cout << v << " ";
}

int main()
{
    print({1, 2, 3, 4});
    MyArray arr = {10, 20, 30};
    arr.print();
    return 0;
}

// 5️⃣ Important Rules (Interview Important)
// 🔹 1. Elements are always const
// You cannot modify them:

// void f(std::initializer_list<int> list)
// {
//     // list.begin()[0] = 10; ❌ error
// }
// Because it is const int*.

// 🔹 2. Lifetime is temporary
// This is dangerous:
// std::initializer_list<int> get()
// {
//     return {1,2,3};  // ❌ dangling
// }
// Why?
// Because {1,2,3} temporary array dies after return statement.
// So returning initializer_list by value is dangerous.

// 6️⃣ Constructor Overload Ambiguity (VERY Important)
// This is where many bugs happen.
// Example:

// class Test {
// public:
//     Test(int a, int b) {
//         std::cout << "normal constructor\n";
//     }

//     Test(std::initializer_list<int> list) {
//         std::cout << "initializer_list constructor\n";
//     }
// };

// int main()
// {
//     Test t1(10, 20);   // normal
//     Test t2{10, 20};   // initializer_list !!!
// }

// output:
// normal constructor
// initializer_list constructor

// Brace initialization prefers initializer_list constructor.
// This causes subtle bugs in real systems.

//------------------interview traps--------------------//
// 7️⃣ Real STL Example – std::vector
// std::vector<int> v1(5, 10);   // 5 elements, each 10
// std::vector<int> v2{5, 10};   // elements = 5 and 10
// This is one of the most common C++ interview traps.