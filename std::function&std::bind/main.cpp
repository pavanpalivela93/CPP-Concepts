#include <iostream>
#include <functional>

int add(int a, int b)
{
    return a + b;
}

int sum(int a, int b, int c)
{
    std::cout << "a: " << a << ", b: " << b << ", c: " << c << std::endl;
    return a + b + c;
}

struct Math
{
    void print(int x)
    {
        std::cout << "Math::print: " << x << std::endl;
    }
    int operator()(int a, int b)
    {
        return a + b;
    }
};
int main()
{
    // std::function is a type-erased wrapper that can store any callable matching a given signature.
    // It can store:
    // Free functions
    // Lambdas
    // Function pointers
    // Functors (objects with operator())
    // std::bind expressions
    // Member function wrappers

    // syntax : std::function<ReturnType(Args...)> name;

    // storing function
    std::function<int(int, int)> f = add;
    std::cout << add(2, 3) << std::endl;

    // storing lambds
    std::function<int(int, int)> fun = [](int a, int b)
    {
        return a + b;
    };
    std::cout << fun(3, 3) << std::endl;

    // storing functor
    std::function<int(int, int)> mathF = Math();
    std::cout << mathF(3, 4) << std::endl;

    // Store callbacks
    // void execute(std::function<void()> callback) {
    //     callback();
    // }

    // 🔹 Internal Concept: Type Erasure
    // std::function hides the actual callable type at runtime.
    // Internally it stores:
    // Pointer to callable object
    // Small buffer optimization (for small lambdas)
    // Virtual-like call wrapper

    // 🔹 Performance Consideration
    // ⚠ std::function is NOT zero-cost.
    // It adds:
    // Indirection
    // Possible heap allocation
    // Type erasure overhead
    // For high-performance systems:
    // Prefer templates when possible.
    // Avoid in tight loops.

    // 2️⃣ std::bind

    // std::bind creates a callable object by binding arguments to a function.
    // It’s essentially partial function application.

    auto add5 = std::bind(add, 5, std::placeholders::_1);
    std::cout << add5(10) << std::endl;

    // 🔹 Placeholders
    auto sum5 = std::bind(sum, 5, std::placeholders::_2, std::placeholders::_1);
    std::cout << sum5(10, 20) << std::endl;

    // 🔹 Binding Member Functions
    Math m;
    auto bmf = std::bind(&Math::print, &m, std::placeholders::_1);
    bmf(10);

    // 3️⃣ std::bind vs Lambda
    // Instead of:
    auto f = std::bind(add, 5, std::placeholders::_1);
    // write
    auto f = [](int x)
    {
        return add(5, x);
    };
    // Or even:
    auto f = [=](int x)
    {
        return add(5, x);
    };
    // Lambdas are:
    // Clearer
    // Safer
    // More readable
    // Usually faster
    // Compile-time resolved

    // key concepts interview que
    // 🔹 1. std::function can be empty
    //     std::function<void()>
    //         f;

    // if (f)
    // {
    //     f();
    // }
    // Calling empty function throws:
    // std::bad_function_call

    // 🔹 2. Capturing references
    // Be careful:
    // int x = 10;

    // std::function<void()> f = [&]() {
    //     std::cout << x;
    // };
    // If x dies → dangling reference.

    // 🔹 3. std::bind copies by default
    // int x = 10;

    // auto f = std::bind([](int& y){ y++; }, x);
    // This increments COPY.
    // To bind reference:
    // auto f = std::bind([](int& y){ y++; }, std::ref(x));

    // 5️⃣ When Should You Use What?
    // | Use Case         | Recommended        |
    // | ---------------- | ------------------ |
    // | High performance | Templates          |
    // | Callback storage | `std::function`    |
    // | Partial binding  | Lambda (preferred) |
    // | Legacy code      | `std::bind`        |

    return 0;
}

// 7️⃣ Real System Design Example
// Event Dispatcher:

// class EventManager {
//     std::function<void(int)> handler;

// public:
//     void registerHandler(std::function<void(int)> h) {
//         handler = h;
//     }

//     void trigger(int value) {
//         if(handler)
//             handler(value);
//     }
// };

// EventManager mgr;

// mgr.registerHandler([](int x){
//     std::cout << "Value: " << x;
// });

// mgr.trigger(42);

// 8️⃣ Advanced: Replacing std::bind with std::invoke
// Modern generic wrapper:

// template<typename F, typename... Args>
// auto call(F&& f, Args&&... args) {
//     return std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
// }

// This handles:
// Free functions
// Member functions
// Function objects
// Pointers to member data