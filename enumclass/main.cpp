#include<iostream>

int main() {
    enum class Color { Red, Green, Blue };
    Color c = Color::Red;
    int colorValue = static_cast<int>(c); // Accessing the underlying integer value of the enum class
    std::cout << "Color value: " << colorValue << std::endl;

    // Accessing enum class values
    if (c == Color::Red) {
        std::cout << "Color is Red" << std::endl;
    } else if (c == Color::Green) {
        std::cout << "Color is Green" << std::endl;
    } else if (c == Color::Blue) {
        std::cout << "Color is Blue" << std::endl;
    }

    // Enum class values are strongly typed and scoped
    // The following line would cause a compilation error
    // int colorValue = c; // Error: cannot convert 'Color' to 'int'
}
