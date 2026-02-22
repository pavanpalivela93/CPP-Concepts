#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>

// [capture](parameters) -> return_type {
//     body
// };

// [int x = 10] (int y) mutable -> int { return x + y; }

// | Part           | Meaning                                       |
// | -------------- | --------------------------------------------- |
// | `[capture]`    | What variables from outer scope to capture    |
// | `(parameters)` | Function parameters                           |
// | `mutable`      | Allows modification of captured-by-value vars |
// | `-> int`       | Explicit return type                          |
// | `{}`           | Function body                                 |

// How Compiler Implements Lambda (Deep Internal Model)
//      int x = 10;
//      auto f = [x](int y)
//      { return x + y; };
// Compiler generates something like:
// class __Lambda {
//     int x;
// public:
//     __Lambda(int x_) : x(x_) {}
//     int operator()(int y) const {
//         return x + y;
//     }
// };
// So lambda is:
//      Just a class
//      With operator()
//      Possibly templated
//      Possibly constexpr
//      Possibly mutable

//  below is equalant to old style functor for add
struct Add
{
    int operator()(int a, int b) const
    {
        return a + b;
    }
};

auto add = [](int a, int b) -> int
{
    return a + b;
};

void process(int &x)
{
    std::cout << "Lvalue overload called with value: " << x << std::endl;
}

void process(int &&x)
{
    std::cout << "Rvalue overload called with value: " << x << std::endl;
}

auto f()
{
    int x = 10;
    return [&]()
    {
        return x;
    }; // ❌ dangling reference
}

auto g()
{
    int x = 20;
    return [=]()
    {
        return x;
    };
}

int main()
{
    int a = 10;
    int b = 20;

    // Using the lambda function directly
    std::cout << "The result of add(2,3) is: "
              << add(2, 3) << std::endl;

    // Using the functor
    Add add_functor;
    std::cout << "The result of add_functor(2,3) is: "
              << add_functor(2, 3) << std::endl;

    // Lambda with parameters
    auto lambda_with_parameters = [](int a, int b)
    {
        return a + b;
    };
    std::cout << "The result of lambda_with_parameters(2,3) is: "
              << lambda_with_parameters(2, 3) << std::endl;

    // Lambda with default capture by value
    auto lambda_with_default_capture_by_value = [=](int c, int d) -> int
    {
        // a = 100; // Error not allowed to modify 'a' and 'b' since they are captured by value
        // b = 200;
        return a + b + c + d;
    };
    std::cout << "The result of lambda_with_default_capture_by_value(1,2) is: "
              << lambda_with_default_capture_by_value(1, 2) << std::endl;

    auto lambda_with_default_capture_by_ref = [&](int c, int d) -> int
    {
        a = 100; // Allowed to modify 'a' and 'b' since they are captured by reference
        b = 200;
        return a + b + c + d;
    };
    std::cout << "The result of lambda_with_default_capture_by_ref(1,2) is: "
              << lambda_with_default_capture_by_ref(1, 2) << std::endl;

    // Lambda with capture by value
    auto lambda_with_capture_by_value = [a, b]() -> int
    {
        // a = 100; // Error not allowed to modify 'a' and 'b' since they are captured by value
        // b = 200;
        return a + b;
    };
    std::cout << "The result of lambda_with_capture_by_value() is: "
              << lambda_with_capture_by_value() << std::endl;

    // Lambda with capture by reference
    auto lambda_with_capture_by_ref = [&a, &b](int c, int d) -> int
    {
        a = 100; // Allowed to modify 'a' and 'b' since they are captured by reference
        b = 200;
        return a + b + c + d;
    };
    std::cout << "The result of lambda_with_capture_by_ref(1,2) is: "
              << lambda_with_capture_by_ref(1, 2) << std::endl;

    // Lambda with mutable capture by value
    auto lambda_with_mutable_capture_by_value = [a, b](int c, int d) mutable -> int
    {
        a = 100; // Allowed to modify 'a' and 'b' since mutable allows modification of captured-by-value variables
        b = 200;
        return a + b + c + d;
    };
    std::cout << "The result of lambda_with_mutable_capture_by_value(1,2) is: "
              << lambda_with_mutable_capture_by_value(1, 2) << std::endl;

    // Lambda with capture by value and default capture
    auto lambda_with_capture_by_value_and_default_capture = [a, b, c = 30](int d) -> int
    {
        return a + b + c + d;
    };
    std::cout << "The result of lambda_with_capture_by_value_and_default_capture(1) is: "
              << lambda_with_capture_by_value_and_default_capture(1) << std::endl;

    // Lambda with capture by value and default capture and mutable
    auto lambda_with_capture_by_value_and_default_capture_and_mutable = [a, b, c = 30](int d) mutable -> int
    {
        c = 40; // Allowed to modify 'c' since it is captured by value and mutable is specified
        return a + b + c + d;
    };
    std::cout << "The result of lambda_with_capture_by_value_and_default_capture_and_mutable(1) is: "
              << lambda_with_capture_by_value_and_default_capture_and_mutable(1) << std::endl;

    // Lambda with capture by reference and default capture
    auto lambda_with_capture_by_ref_and_default_capture = [&a, &b, c = 30](int d) -> int
    {
        a = 100; // Allowed to modify 'a' and 'b' since they are captured by reference
        b = 200;
        // c = 40; // not allowed to modify 'c' since it is captured by value and mutable is not specified
        return a + b + c + d;
    };
    std::cout << "The result of lambda_with_capture_by_ref_and_default_capture(1) is: "
              << lambda_with_capture_by_ref_and_default_capture(1) << std::endl;

    auto lambda_with_capture_by_ref_and_default_capture_and_mutable = [&a, &b, c = 30](int d) mutable -> int
    {
        a = 100; // Allowed to modify 'a' and 'b' since they are captured by reference
        b = 200;
        c = 40; // Allowed to modify 'c' since it is captured by value and mutable is specified
        return a + b + c + d;
    };
    std::cout << "The result of lambda_with_capture_by_ref_and_default_capture_and_mutable(1) is: "
              << lambda_with_capture_by_ref_and_default_capture_and_mutable(1) << std::endl;

    auto lambda_with_capture_by_ref_and_value = [&a, b](int c)
    {
        a = 100; // allowed
        // b = 200; //not allowed
        return a + b + c;
    };
    std::cout << "The result of lambda_with_capture_by_ref_and_value(1) is: "
              << lambda_with_capture_by_ref_and_value(1) << std::endl;

    // lambda with init capture
    auto lambda_with_init_capture = [x = 10 + a, y = 20 + b](int z) -> int
    {
        return x + y + z;
    };
    std::cout << "The result of lambda_with_init_capture(1) is: "
              << lambda_with_init_capture(1) << std::endl;

    // renaming capture val
    int p = 100;
    auto lambda_renaming_capture_val = [temp = p]() mutable
    {
        temp = 500;
    };
    // std::cout << "The result of lambda_renaming_capture is: " << temp << std::endl; //Error temp undefined outside lambda
    lambda_renaming_capture_val();
    std::cout << "The result of lambda_renaming_capture is: " << p << std::endl; // result doesnt change as cpature by value

    // renaming capture ref
    auto lambda_renaming_capture_ref = [&temp = p]()
    {
        temp = 500;
    };
    // std::cout << "The result of lambda_renaming_capture is: " << temp << std::endl; //Error temp undefined outside lambda
    lambda_renaming_capture_ref();
    std::cout << "The result of lambda_renaming_capture is: " << p << std::endl; // result changes as cpature by reference

    //////////

    // Generic lambda
    // compliler tures below into template function
    // template<typename T, typename U>
    // auto operator()(T a, U b) const;
    auto generic_lambda = [](auto x, auto y)
    {
        return x + y;
    };
    std::cout << "The result of generic_lambda(2,3) is: "
              << generic_lambda(2, 3) << std::endl;
    std::cout << "The result of generic_lambda(2.5,3.5) is: "
              << generic_lambda(2.5, 3.6) << std::endl;

    // lambdas as template parameters
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::for_each(v.begin(), v.end(), [](int x)
                  { std::cout << x << " "; });

    std::cout << std::endl;
    std::for_each(v.begin(), v.end(), [](int x)
                  {
        if(x % 2 == 0)
        {
            std::cout << x << " is even" << std::endl;
        }
        else
        {
            std::cout << x << " is odd" << std::endl;
        } });

    // Lambda Conversion to Function Pointer
    auto lambda_no_capture = [](int x, int y) -> int
    {
        return x + y;
    };
    int (*fptr)(int, int) = lambda_no_capture; // Allowed since lambda_no_capture does not capture any variables
    std::cout << "The result of fptr(2,3) is: "
              << fptr(2, 3) << std::endl;

    // auto lambda_with_capture = [a](int x) -> int { return a + x; };
    // int (*fptr2)(int) = lambda_with_capture; // Error not allowed since lambda_with_capture captures variable 'a'

    // Lambda with Rvalue reference capture
    auto lambda_with_rvalue_ref_capture = [](auto &&x)
    {
        std::cout << "The value of x is: " << x << std::endl;
    };
    lambda_with_rvalue_ref_capture(10);
    lambda_with_rvalue_ref_capture("Hello");

    // Lambda with Rvalue reference capture with std::move
    int value = 100;
    auto lambda_with_rvalue_ref_capture_and_move = [x = std::move(value)]()
    {
        std::cout << "The value of x is: " << x << std::endl;
    };
    lambda_with_rvalue_ref_capture_and_move();
    std::cout << "The value of value is: " << value << std::endl; // value is moved and becomes empty

    // lambda_with_rvalue_ref_capture_and_forwarding
    auto lambda_with_rvalue_ref_capture_and_forwarding = [](auto &&x)
    {
        process(std::forward<decltype(x)>(x));
    };
    lambda_with_rvalue_ref_capture_and_forwarding(10);
    lambda_with_rvalue_ref_capture_and_forwarding(value);

    // Lambdas and Lifetime Issues
    // auto ref = f();
    // auto res = ref();
    // std::cout << "The value of ref res is: " << res << std::endl;
    // auto val = g();
    // res = val();
    // std::cout << "The value of ref res is: " << res << std::endl;

    // Immediately Invoked Lambda
    int x = []()
    {
        return 42;
    }();
    //     Used for:
    //          Complex initialization
    //          Const initialization
    //          Compile-time computation

    // Lambda in Concurrency
    std::thread thread1([]()
                        { std::cout << "Hello\n"; });
    // Or capturing:
    std::thread thread2([value = std::move(p)]()
                        {
                            // safe ownership transfer
                        });
    thread1.join();
    thread2.join();

    // constexpr Lambdas (C++17+)
    constexpr auto add = [](int a, int b)
    {
        return a + b;
    };
    constexpr int result = add(10, 20);

    // Lambdas in STL Algorithms (Most Common Use)
    std::sort(v.begin(), v.end(), [](int a, int b)
              { return a < b; });
    std::for_each(v.begin(), v.end(), [](int x)
                  { std::cout << x << std::endl; });

    ////////////
    // Advanced: Recursive Lambda
    // C++14 workaround
    auto fact1 = [](auto self, int n) -> int
    {
        if (n <= 1)
            return 1;
        return n * self(self, n - 1);
    };
    std::cout << fact1(fact1, 5) << std::endl;

    // C++20 better solution:
    auto fact2 = [](int n, auto &&self) -> int
    {
        if (n <= 1)
            return 1;
        return n * self(n - 1, self);
    };
    std::cout << fact2(5, fact2) << std::endl;
    return 0;
}
