#include <iostream>
#include <chrono>
#include <thread>
// ⏱️ std::chrono — Modern C++ Time Library (C++11+)
// std::chrono is the type-safe time library introduced in C++11.
// It helps you measure time durations, work with clocks, and manipulate timestamps without manual conversions.
// It is:
// ✅ Strongly typed
// ✅ Zero-overhead abstraction
// ✅ Safer than raw integers for time
// ✅ Designed for high precision

// 🔹 1. Core Concepts of std::chrono
//  There are 3 main building blocks:
//  Clock  →  Time Point  →  Duration

// 1️⃣ Duration
// Represents a time interval.
// std::chrono::seconds
// std::chrono::milliseconds
// std::chrono::microseconds
// std::chrono::nanoseconds

// 2️⃣ Clocks
// A clock gives you the current time point.
// 3 Important clocks:
// Clock	Use Case
// system_clock	Wall-clock time
// steady_clock	Monotonic (best for measuring duration)
// high_resolution_clock	Highest precision available

// 3️⃣ Time Point
// Represents a point in time.
// auto now = std::chrono::system_clock::now();
// You can subtract two time points to get a duration.

int main()
{
    // 1️⃣ Duration
    std::chrono::seconds s(5);
    std::chrono::milliseconds ms(500);

    std::cout << s.count() << std::endl;  // 5
    std::cout << ms.count() << std::endl; // 500

    // 3️⃣ Time Point
    auto now = std::chrono::system_clock::now();

    // 🔹 2. Measuring Execution Time
    auto start = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); // duration_cast avoids silent precision loss.
    std::cout << "Time taken:" << duration << std::endl;

    // Why steady_clock?
    // Because it:
    // Never goes backward
    // Is not affected by system time changes
    // Best for benchmarking

    // 🔹 4. Custom Duration Types
    using Minutes = std::chrono::duration<int, std::ratio<60>>;
    Minutes m(2); // 2 minutes

    // Template parameters:
    // duration<Rep, Period>
    // Rep    = storage type (int, long long)
    // Period = ratio (1 = seconds, 1/1000 = milliseconds)

    auto current = std::chrono::system_clock::now();
    std::time_t time_now = std::chrono::system_clock::to_time_t(current);
    std::cout << std::ctime(&time_now);

    // 🔹 6. C++20 Improvements (Very Important)
    // C++20 made std::chrono much more powerful.
    // Now you can do:

    using namespace std::chrono;

    auto today = floor<days>(system_clock::now());
    year_month_day ymd = today;

    std::cout << int(ymd.year()) << "-"
              << unsigned(ymd.month()) << "-"
              << unsigned(ymd.day());

    // std::chrono::days
    // std::chrono::months
    // std::chrono::years
    // std::chrono::hh_mm_ss
    // Time zone support

    // 🔹 7. Sleep & Timers
    // std::this_thread::sleep_for(std::chrono::seconds(3));
    // std::this_thread::sleep_until(time_point);

    // 🔹 8. Why std::chrono Is Designed This Way
    // Older C-style time:
    // long t = 5000; // milliseconds? seconds? microseconds?
    // Problem:
    // No type safety
    // Easy to mix units
    // Hard to maintain
    // Chrono prevents:
    // seconds + milliseconds  // automatically converted safely
    // 🔹 9. Performance Perspective (Important for Interviews)
    // Zero runtime overhead
    // Compile-time unit checking
    // Strong type guarantees
    // Ideal for performance-critical code
    return 0;
}