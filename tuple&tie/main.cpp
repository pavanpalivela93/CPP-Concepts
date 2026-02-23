#include <iostream>
#include <tuple>
#include <string>
#include <algorithm>

// Function returning multiple values
std::tuple<int, double, bool> evaluateStudent(int math, int physics, int chemistry)
{
    int total = math + physics + chemistry;
    double average = total / 3.0;
    bool passed = (math >= 35 && physics >= 35 && chemistry >= 35);

    return std::make_tuple(total, average, passed);
}

int main()
{
    int math = 80, physics = 70, chemistry = 60;

    // 1️⃣ Direct tuple storage
    std::tuple<int, double, bool> result =
        evaluateStudent(math, physics, chemistry);

    std::cout << "Using std::get:\n";
    std::cout << "Total: " << std::get<0>(result) << std::endl;
    std::cout << "Average: " << std::get<1>(result) << std::endl;
    std::cout << "Passed: " << std::get<2>(result) << std::endl;

    std::cout << "\n------------------\n";

    // 2️⃣ Using std::tie (unpacking)
    int total;
    double average;
    bool passed;

    std::tie(total, average, passed) =
        evaluateStudent(math, physics, chemistry);

    std::cout << "Using std::tie:\n";
    std::cout << "Total: " << total << std::endl;
    std::cout << "Average: " << average << std::endl;
    std::cout << "Passed: " << passed << std::endl;

    std::cout << "\n------------------\n";

    // 3️⃣ Using structured bindings (C++17)
    auto [t, avg, passStatus] =
        evaluateStudent(math, physics, chemistry);

    std::cout << "Using structured bindings:\n";
    std::cout << "Total: " << t << std::endl;
    std::cout << "Average: " << avg << std::endl;
    std::cout << "Passed: " << passStatus << std::endl;

    std::cout << "\n------------------\n";

    // 4️⃣ Ignoring values using std::ignore
    int onlyTotal;
    std::tie(onlyTotal, std::ignore, std::ignore) =
        evaluateStudent(math, physics, chemistry);

    std::cout << "Using std::ignore:\n";
    std::cout << "Only Total: " << onlyTotal << std::endl;

    std::cout << "\n------------------\n";

    // 5️⃣ Tuple comparison
    auto student1 = evaluateStudent(80, 70, 60);
    auto student2 = evaluateStudent(90, 50, 60);

    if (student1 > student2)
        std::cout << "Student1 performed better (lexicographical compare)\n";
    else
        std::cout << "Student2 performed better\n";

    return 0;
}