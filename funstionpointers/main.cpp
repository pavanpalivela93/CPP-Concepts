#include <iostream>

using uFprt1 = int (*)(int, int, int);
using uFprt2 = int (*)(int);
using uFprt3 = int (*)(int, int);

class Math
{
public:
    using mathDivPtrType = int (Math::*)(int, int);
    static int add(int a, int b)
    {
        return a + b;
    }

    int add(int a, int b, int c)
    {
        return a + b + c;
    }

    int sub(int a, int b, int c)
    {
        return a - b - c;
    }

    int sub(int a, int b)
    {
        return a - b;
    }

    int divide(int a, int b)
    {
        return Math::div(a, b); // This is how you can call a private member function from a public member function of the same class
    }

    int getDiv(int a, int b)
    {
        return (this->*mathDivPtr)(a, b); // This is how you can call a private member function using a member function pointer
    }

    mathDivPtrType getMathDivPtr()
    {
        return &Math::div; // This is how you can return a member function pointer to a private member function
    }

private:
    int (Math::*mathDivPtr)(int, int) = &Math::div; // This is how you can declare a member function pointer to a private member function
    int div(int a, int b)
    {
        return a / b;
    }
};

int add(int a, int b)
{
    return a + b;
}

int sub(int a, int b)
{
    return a - b;
}

int sub(int a, int b, int c)
{
    return a - b - c;
}

int mathOperation(int a, int b, int c, int (*fptr1)(int, int), uFprt1 fptr2)
{
    return (a * b * c) + fptr1(a, b) + fptr2(a, b, c);
}

int returnVal(int a)
{
    return a;
}

int returnVal2(int a, int b, int (*fptr)(int))
{
    return a + b + fptr(a) + fptr(b);
}

int muiltiplyAdd(int a, int b, int (*fptr1)(int, int, uFprt2))
{
    int (*fptr)(int) = returnVal;
    return a * b + fptr1(a, b, fptr);
}

int main()
{
    int (*fptr)(int, int);
    fptr = add;
    int res = fptr(5, 10);
    std::cout << "The result of addition is: " << res << std::endl;

    uFprt1 ufptr = sub;
    res = ufptr(10, 5, 2);
    std::cout << "The result of subtraction is: " << res << std::endl;

    res = mathOperation(2, 3, 4, fptr, ufptr);
    std::cout << "The result of mathOperation is: " << res << std::endl;

    int (*fptrReturnVal)(int) = returnVal;
    int (*fptrReturnVal2)(int, int, int (*)(int)) = returnVal2;
    res = muiltiplyAdd(2, 3, fptrReturnVal2);
    std::cout << "The result of muiltiplyAdd is: " << res << std::endl;

    /////// add

    uFprt3 mathAdd = Math::add;
    res = mathAdd(1, 2);
    std::cout << "The result of Math::add is: " << res << std::endl;
    // uFprt3 uFptr1 = Math::sub; // This will cause a compilation error because Math::sub is not static and cannot be assigned to a function pointer of type uFprt3
    // int (*mathfAddPtr)(int, int) = Math::add; // This is valid because Math::add is static and can be assigned to a function pointer of type int (*)(int, int)
    // int (*mathfSubPtr)(int, int) = Math::sub; // This will cause a compilation error because Math::sub is not static and cannot be assigned to a function pointer of type int (*)(int, int)

    /////// sub

    int (Math::*mathfSubPtr)(int, int) = &Math::sub; // This is valid because Math::sub is a non-static member function and can be assigned to a member function pointer of type int (Math::*)(int, int)
    res = (Math().*mathfSubPtr)(10, 5);              // This is how you call a member function pointer it needs an object as this is not a normal function pointer
    std::cout << "The result of Math::sub is: " << res << std::endl;

    Math mathObj;
    res = (mathObj.*mathfSubPtr)(10, 5); // This is another way to call a member function pointer using an object and paranthesis around mathObj.*mathfSubPtr is must be used to avoid ambiguity with operator precedence
    std::cout << "The result of Math::sub is: " << res << std::endl;

    //////// div
    //  int (Math::*mathDivPtr)(int, int) = &Math::div; // This is not valid because Math::div is a private member function and cannot be accessed outside the class. To access it, you would need to make it public or provide a public member function that calls it.

    // Math::divide
    int (Math::*dividePtr)(int, int) = &Math::divide; // This is valid because Math::divide is a public member function and can be assigned to a member function pointer of type int (Math::*)(int, int)
    res = (mathObj.*dividePtr)(10, 5);                // This is how you can call a private member function using a public member function that calls it
    std::cout << "The result of Math::divide is: " << res << std::endl;

    // Math::getDiv
    int (Math::*getDivPtr)(int, int) = &Math::getDiv; // This is valid because Math::getDiv is a public member function and can be assigned to a member function pointer of type int (Math::*)(int, int)
    res = (mathObj.*getDivPtr)(10, 5);                // This is how you can call a private member function using a public member function that calls it using a member function pointer
    std::cout << "The result of Math::getDiv is: " << res << std::endl;

    // Math::getMathDivPtr
    int (Math::*dividePtr2)(int, int) = mathObj.getMathDivPtr(); // This is valid because Math::getMathDivPtr is a public member function that returns a member function pointer to a private member function, and can be assigned to a member function pointer of type int (Math::*)(int, int)
    res = (mathObj.*dividePtr2)(10, 5);                          // This is how you can call a private member function using a member function pointer that is returned by a public member function
    std::cout << "The result of Math::getMathDivPtr2 is: " << res << std::endl;
    // Or
    Math::mathDivPtrType dividePtr3 = mathObj.getMathDivPtr(); // This is valid because Math::getMathDivPtr is a public member function that returns a member function pointer to a private member function, and can be assigned to a member function pointer of type int (Math::*)(int, int)
    res = (mathObj.*dividePtr3)(10, 5);                        // This is how you can call a private member function using a member function pointer that is returned by a public member function
    std::cout << "The result of Math::getMathDivPtr3 is: " << res << std::endl;

    // double level for Math::getMathDivPtr
    using GetMathDivPtrType = Math::mathDivPtrType (Math::*)();      // This is how you can declare a member function pointer to a member function that returns a member function pointer
    GetMathDivPtrType getMathDivPtrPtr = &Math::getMathDivPtr;       // This is how you can assign a member function pointer to a member function that returns a member
    Math::mathDivPtrType mathDivPtr = (mathObj.*getMathDivPtrPtr)(); // This is how you can call a member function pointer that returns a member function pointer
    res = (mathObj.*mathDivPtr)(10, 5);                              // This is how you can call a private member function using a member function pointer that is returned by a member function pointer
    std::cout << "The result of Math::getMathDivPtrPtr is: " << res << std::endl;

    ////////
    // array of function pointers
    int (*operations1[])(int, int) = {add, sub}; // This is how you can declare and initialize an array of function pointers to non-static member functions. Note that you cannot use Math::add and Math::sub here because they are not static member functions, and you cannot assign them to a function pointer of type uFprt3. Instead, you can use the global add and sub functions that we defined earlier.
    std::cout << "The result of operations1[0](1,2) is: " << operations1[0](1, 2) << std::endl;
    std::cout << "The result of operations1[1](10,5) is: " << operations1[1](10, 5) << std::endl;

    uFprt3 operations2[] = {
        add,
        sub}; // This is how you can declare and initialize an array of function pointers to non-static member functions. Note that you cannot use Math::add and Math::sub here because they are not static member functions, and you cannot assign them to a function pointer of type uFprt3. Instead, you can use the global add and sub functions that we defined earlier.
    std::cout << "The result of operations2[0](1,2) is: " << operations2[0](1, 2) << std::endl;
    std::cout << "The result of operations2[1](10,5) is: " << operations2[1](10, 5) << std::endl;

    // array of member function pointers
    int (Math::*mathOperations1[])(int, int, int) = {&Math::add, &Math::sub}; // This is how you can declare and initialize an array of member function pointers to non-static member functions. Note that you cannot use Math::add and Math::sub here because they are not static member functions, and you cannot assign them to a member function pointer of type int (Math::*)(int, int). Instead, you can use the global add and sub functions that we defined earlier.
    std::cout << "The result of (mathObj.*mathOperations1[0])(1,2,3) is: " << (mathObj.*mathOperations1[0])(1, 2, 3) << std::endl;
    std::cout << "The result of (mathObj.*mathOperations1[1])(10,5,2) is: " << (mathObj.*mathOperations1[1])(10, 5, 2) << std::endl;

    using MathOperations = int (Math::*)(int, int, int);         // This is how you can declare a type alias for a member function pointer to a non-static member function that takes three int parameters and returns an int
    MathOperations mathOperations2[] = {&Math::add, &Math::sub}; // This is how you can declare and initialize an array of member function pointers to non-static member functions using a type alias. Note that you cannot use Math::add and Math::sub here because they are not static member functions, and you cannot assign them to a member function pointer of type MathOperations. Instead, you can use the global add and sub functions that we defined earlier.
    std::cout << "The result of (mathObj.*mathOperations2[0])(1,2,3) is: " << (mathObj.*mathOperations2[0])(1, 2, 3) << std::endl;
    std::cout << "The result of (mathObj.*mathOperations2[1])(10,5,2) is: " << (mathObj.*mathOperations2[1])(10, 5, 2) << std::endl;

    return 0;
}