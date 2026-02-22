#include <iostream>
#include <vector>
#include <map>
//-----------------------------------------------
// function template
template <typename T>
void print(T value)
{
    std::cout << "function template value of type:" << typeid(value).name() << ", is:" << value << std::endl;
}

template <>
void print<int>(int value)
{
    std::cout << "function template specialized for int value of type:" << typeid(value).name() << ", is:" << value << std::endl;
}
// ⚠ Important:
// Function template specialization works
// But overloading is often better than specialization
// In modern C++, prefer:
// void func(int value) { }   // overload instead
// Because overload resolution is more flexible than specialization.

// Note: Partial specialization only allowed for class templates not functions templates

//-----------------------------------------------\
// class template
template <typename T, int N>
class PrinterClass
{
    int x;
    const int y;
    T arr[N];
    std::vector<T> v;

public:
    PrinterClass(int _x, int _y) : x(_x), y(_y), v(N)
    {
        std::cout << "x:" << this->x << ", y:" << this->y
                  << ", arr size:" << sizeof(arr) << ", arr type:" << typeid(arr).name()
                  << ", vector size:" << this->v.size() << std::endl;
    }
};

//-----------------------------------------------
// struct templates

// we can define the specalized template first and then the sepcalized template work as compiler should know for what template this specialization belongs to
// A specialization must be declared after the primary template declaration.
//  else error: explicit specialization of non-template 'Printer'
//  yet, it does not know:
//  What Printer is
//  Whether it is a template
//  What its parameters are
//  Whether it can be specialized
//  So it cannot legally specialize something that doesn’t exist yet.

// we can define the specialized template first and then the primary by decalring primary template as below
template <typename T, int x>
struct Printer; // forward declaration

// Because now the compiler knows:
// Printer is a template
// It has one type parameter
// So specialization is valid.

// Why C++ Is Designed This Way
// Templates are compiled in two phases:
// Template declaration phase
// Template instantiation phase
// A specialization is attached to an existing template entity.

// //similar to
// class A;
// class A {};   // definition later
// You can’t define something that hasn’t been declared.

// Primary template = blueprint
// Specialization = customized version of that blueprint

//-------------------> Primary Template
template <typename T, int x = 0>
struct Printer
{
    static void print(const T &value)
    {
        std::cout << "Generic: " << value << std::endl;
    }
};

// Full Specialization for int
template <>
struct Printer<int>
{
    static void print(const int &value)
    {
        std::cout << "Integer specialization: " << value << std::endl;
    }
};

//-------------------> Partial Template Specialization

// pointer specialization
template <typename T>
struct TypeInfo
{
    static constexpr const char *name = "primary"; // works in c++14, works in c++17 and later
    constexpr static const char *name1 = "primary1";
    // static const char *name = "primary";           // fails in c++14, fails in c++17 and later because Not integral means int, Not constexpr, Not inline
    static const int a = 10;
    static constexpr const double b = 10;
    inline static const char *name2 = "primary2";
    static inline const char *name3 = "primary3";
    const inline static char *name4 = "primary4";
    const static inline char *name5 = "primary5";
};

template <typename T>
struct TypeInfo<T *>
{
    static constexpr const char *name = "Pointer";
};

//-----------------------------------------------
// Two Template Parameters
template <typename T, typename U>
struct Pair
{
    static constexpr const char *pairName = "Generic pair";
};

template <typename T>
struct Pair<T, T>
{
    static constexpr const char *pairName = "same type pair";
};

//-----------------------------------------------
// partial specilization continution
template <typename T> // for all types
class Logger
{
public:
    // static std::ostream &log()
    // {
    //     return std::cout << "Generic logger" << std::endl;
    // }
    static void log()
    {
        std::cout << "Logger Generic logger" << std::endl;
    }
};

template <typename T> // for all pointer types
class Logger<T *>
{
public:
    static void log()
    {
        std::cout << "Logger pointer logger" << std::endl;
    }
};

template <> // for all pointer types
class Logger<int>
{
public:
    static void log()
    {
        std::cout << "Logger int specific logger" << std::endl;
    }
};

template <typename T> // for all reference types
struct Logger<T &>    // mixing class and static for partial specialization
{
    static void log()
    {
        std::cout << "Logger lvalue reference logger" << std::endl;
    }
};

template <typename T> // for all reference types
struct Logger<T &&>   // mixing class and static for partial specialization
{
    static void log()
    {
        std::cout << "Logger rvalue reference logger" << std::endl;
    }
};

//-----------------------------------------------
// Partial Specialization with std::enable_if Pattern
template <typename T, typename = void>
struct has_size : std::false_type
{
    static void size()
    {
        std::cout << "size not found" << std::endl;
    }
};

template <typename T>
struct has_size<T, std::void_t<decltype(std::declval<T>().size())>> : std::true_type
{
    static void size()
    {
        std::cout << "size found" << std::endl;
    }
};

//-----------------------------------------------
// Function Templates Cannot Be Partially Specialized
template <typename T>
void func(T value)
{
    std::cout << "Generic function template value: " << value << std::endl;
};

// template <typename T>
// void func<T *>(T *); // ❌ Not allowed, function template partial specialization is not allowed

template <typename T>
void function(T *value)
{
    std::cout << "Generic pointer function template value: " << value << std::endl;
}

template <typename T>
void function(T &value)
{
    std::cout << "Generic reference function template lvalue: " << value << std::endl;
}

template <typename T>
void function(T &&value)
{
    std::cout << "Generic function template rvalue: " << value << std::endl;
}

template <typename T>
void function(const T *value)
{
    std::cout << "Generic pointer function template with const value: " << value << std::endl;
}
//-----------------------------------------------
// Real-World Pattern: Enable Only for Specific Types
template <typename T, typename Enable = void>
struct Serializer
{
    static void serialize(const T &)
    {
        std::cout << "Generic serializer\n";
    }
};

template <typename T>
struct Serializer<T, std::enable_if_t<std::is_integral_v<T>>>
{
    static void serialize(const T &)
    {
        std::cout << "Integral serializer\n";
    }
};
//-----------------------------------------------
int main()
{
    // function template
    print(5);
    print(10.5f);
    print(std::string("Hello"));

    // class templates
    // PrinterClass<int, 5> printer; //if there is no overload constructor -> error: the default constructor of "PrinterClass<int, 5>" cannot be referenced -- it is a deleted function because class hase a const member function which needs to be instansiated while constructing and needs to be in the initializer list
    PrinterClass<int, 5> printer1(10, 5);
    PrinterClass<double, 10> printer2(20, 15);

    // Primary Template
    Printer<double>::print(10.5); // Looks for specialization of Printer<double>, If not found → uses primary template

    // Full Specialization for int
    Printer<int>::print(10); // Finds exact specialization Uses that instead of generic

    // pointer specialization
    std::cout << "pointer specialization type info: " << TypeInfo<int>::name << std::endl;
    std::cout << "pointer specialization type info: " << TypeInfo<int *>::name << std::endl;
    std::cout << "pointer specialization type info: " << TypeInfo<double *>::name << std::endl;
    std::cout << "pointer specialization type info: " << TypeInfo<double>::name1 << std::endl;
    std::cout << "pointer specialization type info: " << TypeInfo<double>::name2 << std::endl;
    std::cout << "pointer specialization type info: " << TypeInfo<double>::name3 << std::endl;
    std::cout << "pointer specialization type info: " << TypeInfo<double>::name4 << std::endl;
    std::cout << "pointer specialization type info: " << TypeInfo<double>::name5 << std::endl;

    // Two Template Parameters
    std::cout << "Two Template Parameters type info: " << Pair<int, double>::pairName << std::endl;
    std::cout << "Two Template Parameters type info: " << Pair<int, int>::pairName << std::endl;

    // partial specilization continution
    // Generic
    Logger<int>::log();
    Logger<double>::log();

    // partial pointer specifier
    Logger<int *>::log();
    Logger<double *>::log();

    // Full Specialization for int
    Logger<int>::log();

    // partial lvalue reference specifier
    Logger<int &>::log();
    Logger<double &>::log();

    // partial rvalue reference specifier
    Logger<int &&>::log();
    Logger<double &&>::log();

    // Partial Specialization with std::enable_if Pattern
    has_size<int>::size();
    has_size<int *>::size();
    has_size<std::vector<int>>::size();
    has_size<std::map<int, int>>::size();

    // Function Templates Cannot Be Partially Specialized
    int a = 10;
    int *b = &a;
    int &c = a;
    int *const d = &a;
    const int *e = &a;
    function(a); // this calls reference template instead of normal one why
    // because
    //  Overload resolution rule (CRITICAL)
    //  If both are viable, the compiler prefers the overload that requires fewer conversions.
    //  Comparison:
    //  Overload	Conversion
    //  T value	copy int → int
    //  T& value	bind lvalue directly
    //  📌 Binding an lvalue reference is a better match than copying
    //  ✅ Therefore:
    //  T&  >  T
    //  That’s why the reference overload wins.
    function(10);
    function(b);
    function(c);
    function(d); // Generic pointer function template value: 0x16b2b6b28
    function(e); // Generic pointer function template with const value: 0x16b2b6b28

    // Why not vice-versa?
    // Because C++ never removes const from the pointee, but it does ignore const on the pointer itself when passed by value.
    // Key Rule (Interview-level)
    // Top-level const is ignored in parameter passing,
    // but low-level const (pointee const) is preserved.

    // int* const d   ---> int*        (top-level const ignored)
    // const int* e  ---> const int*  (low-level const preserved)

    // Real-World Pattern: Enable Only for Specific Types
    Serializer<int>::serialize(a);
    Serializer<double>::serialize(a);
    return 0;
}