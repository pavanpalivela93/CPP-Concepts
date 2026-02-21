#include <iostream>
#include <vector>
#include <map>
// #include <views>

// {
//     auto&& __range = getVector();   // IMPORTANT
//     auto __begin = std::begin(__range);
//     auto __end   = std::end(__range);

//     for (; __begin != __end; ++__begin) {
//         auto& x = *__begin;
//         std::cout << x << " ";
//     }
// }

class MyRange
{
    int data[3] = {10, 20, 30};

public:
    int *begin() { return data; }
    int *end() { return data + 3; }
};

void printVector(const std::vector<int> &vec)
{
    for (auto &element : vec)
    {
        std::cout << element << " ";
    }
}

std::vector<int> getVector()
{
    return {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
}

int main()
{
    std::vector<int> vec{1, 2, 3, 4, 5};
    // std::vector<int> vec1 = {1, 2, 3, 4, 5};
    std::map<std::string, int> myMap = {{"one", 1}, {"two", 2}, {"three", 3}};

    // Using range-based for loop to iterate over the vector
    for (auto &element : vec)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // Using range-based for loop to iterate over the vector
    for (auto element : vec)
    {
        element += 2; // Modifying the element in the vector
    }
    printVector(vec); // This will print the modified vector
    std::cout << std::endl;

    // Using range-based for loop to iterate over the vector
    for (auto &element : vec)
    {
        element += 2; // Modifying the element in the vector
    }
    printVector(vec); // This will print the modified vector
    std::cout << std::endl;

    // Using range-based for loop to iterate over the vector
    // for (const auto &element : vec)
    // {
    //     element += 2; // Modifying the element in the vector is not allowed since it's a const reference
    // }
    // printVector(vec); // This will print the modified vector
    // std::cout << std::endl;

    MyRange myRange;
    for (auto &element : myRange)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    for (auto &pair : myMap)
    {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    std::cout << std::endl;
    for (auto [key, value] : myMap)
    {
        std::cout << key << ": " << value << std::endl;
    }
    std::cout << std::endl;

    for (auto &x : getVector())
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    auto vec1 = getVector();
    for (auto &x : vec1)
    { // Now iterating over a named object, not a temporary
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // this fails because getVector() returns a temporary object, and the range-based for loop cannot bind a non-const reference to a temporary. To fix this, we can either store the result of getVector() in a named variable or use a const reference in the loop.
    //  for (auto &x : getVector() | std::views::filter([](int n) { return n % 2 == 0; }))
    //  {
    //      std::cout << x << " ";
    //  }
    std::cout << std::endl;
    return 0;
}