#include <iostream>
#include <vector>
#include <type_traits>

void printVector(const std::vector<int> &vec)
{
    for (auto &element : vec)
    {
        std::cout << element << " ";
    }
}

class Buffer
{
    int *data;
    size_t size;

public:
    Buffer() = delete; // Default constructor is deleted to prevent uninitialized buffer
    Buffer(size_t s) : size(s), data(new int[s]) {}
    ~Buffer() { delete[] data; }

    // Move constructor
    Buffer(Buffer &&buffer) noexcept : data(buffer.data), size(buffer.size)
    {
        std::cout << "Move constructor called" << std::endl;
        buffer.data = nullptr; // Prevent double deletion
        buffer.size = 0;
    }

    // move assignment operator
    Buffer &operator=(Buffer &&buffer) noexcept
    {
        std::cout << "Move assignment operator called" << std::endl;
        if (this != &buffer)
        {
            delete[] data;
            data = buffer.data;
            size = buffer.size;
            buffer.data = nullptr; // Prevent double deletion
            buffer.size = 0;
        }
        return *this;
    }

    // Copy constructor and copy assignment operator are deleted to prevent copying
    // Buffer(const Buffer &) = delete;
    // Buffer &operator=(const Buffer &) = delete;

    // copy constructor
    Buffer(const Buffer &buffer) : size(buffer.size), data(new int[buffer.size])
    {
        std::cout << "Copy constructor called" << std::endl;
        std::copy(buffer.data, buffer.data + buffer.size, data);
    }

    // copy assignment operator
    Buffer &operator=(const Buffer &buffer)
    {
        std::cout << "Copy assignment operator called" << std::endl;
        if (this != &buffer)
        {
            delete[] data;
            size = buffer.size;
            data = new int[buffer.size];
            std::copy(buffer.data, buffer.data + buffer.size, data);
        }
        return *this;
    }
};

// template <typename T>
// std::string checkType(T &&var)
// {
//     if (std::is_lvalue_reference_v<T>)
//     {
//         return "lvalue reference";
//     }
//     else if (std::is_rvalue_reference_v<T>)
//     {
//         return "rvalue reference";
//     }
//     else
//     {
//         return "non-reference";
//     }
// }

template <typename T>
std::string checkExpr(T &&)
{
    using ExprType = decltype((std::declval<T &&>()));
    if constexpr (std::is_lvalue_reference_v<ExprType>)
        return "lvalue reference";
    else if constexpr (std::is_rvalue_reference_v<ExprType>)
        return "rvalue reference";
    else
        return "non-reference";
}

int main()
{
    int x = 10;
    int &&r = x + 5; // r is an rvalue reference to the temporary result of x + 5

    std::cout << "Value of r: " << r << std::endl; // Output: Value of r: 15

    r += 5;                                                           // Modifying the value through the rvalue reference
    std::cout << "Value of r after modification: " << r << std::endl; // Output: Value of r after modification: 20
    std::cout << std::endl;

    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = v1; // deep copy

    std::vector<int> v3 = std::move(v2);                        // moves the contents of v2 to v3, leaving v2 in a valid but unspecified state
    std::vector<int> v4 = static_cast<std::vector<int> &&>(v3); // also moves the contents of v3 to v4

    printVector(v1);
    std::cout << std::endl;
    std::cout << "v1 is type of: " << checkExpr(v1) << std::endl;
    std::cout << std::endl;

    printVector(v2);
    std::cout << std::endl;
    std::cout << "std::move(v1) is type of: " << checkExpr(std::move(v1)) << std::endl;
    std::cout << std::endl;

    std::cout << "20 is type of: " << checkExpr(20) << std::endl;
    std::cout << std::endl;
    std::cout << "static_cast<std::vector<int> &&>(v1) is type of: " << checkExpr(static_cast<std::vector<int> &&>(v1)) << std::endl;

    Buffer buffer(10);
    Buffer movedBuffer = std::move(buffer); // Move constructor is called
    Buffer anotherMovedBuffer(20);
    anotherMovedBuffer = std::move(movedBuffer); // Move assignment operator is called

    Buffer copiedBuffer = anotherMovedBuffer; // Copy constructor is called
    Buffer anotherCopiedBuffer(30);
    anotherCopiedBuffer = copiedBuffer; // Copy assignment operator is called
    return 0;
}