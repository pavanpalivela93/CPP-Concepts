#include <iostream>
#include <thread>
#include <algorithm>
#include <mutex>
#include <future>

// 7️⃣ Data Race Problem
// int counter = 0;

// void inc() {
//     counter++;
// }

// Two threads running this → undefined behavior.
// Why?
// Because:
// counter++
// = load
// = increment
// = store
// These are 3 separate instructions.
// If interleaved → corrupted value.
// can be solved with mutex

void print(int x)
{
    std::cout << "value: " << x << "\n";
}

std::mutex m;
int counter = 0;

// way 1 to lock the mutex
// ⚠️ But This Is Dangerous
// Manual lock() / unlock() is error-prone.
// mtx.lock();
// throw something;   // unlock never happens
// mtx.unlock();
void increment()
{
    for (int i = 0; i < 100000; i++)
    {
        m.lock();
        counter++;
        m.unlock();
    }
    std::cout << "counter: " << counter << std::endl;
}

// way 1 to lock the with lock guard
// constructor → locks mutex
// destructor → unlocks mutex
// RAII guarantees:
// Unlock happens automatically
// Exception safe
// No leaks
// No deadlock from forgotten unlock
void increment(int &x)
{
    std::lock_guard<std::mutex> lock(m);
    for (int i = 0; i < 100000; i++)
        counter++;
    std::cout << "counter: " << counter << std::endl;
}

void task()
{
    try
    {
        throw std::runtime_error("error");
    }
    catch (...)
    {
        std::cout << "Handled\n";
    }
}

void getSomething(int value, std::promise<int> promise)
{
    promise.set_value(value * 10);
}

int getint(int value)
{
    return value * 10;
}

int main()
{
    int value = 5;
    // std::thread t1(print, 5);
    // std::thread t2(increment, std::ref(value));
    // if (t1.joinable())
    //     t1.join();
    // if (t2.joinable())
    //     t2.join();
    // std::thread t3 = std::move(t1); // only movable
    // // std::thread t4 = t1; //cannot copy Because only one object should own the thread
    // std::cout << "value: " << value << std::endl;

    std::thread t4(increment, std::ref(value));
    std::thread t5(increment, std::ref(value));
    std::thread t6(increment, std::ref(value));

    t4.join();
    t5.join();
    t6.join();

    // 9️⃣ Using Lambda
    int x = 0;
    std::thread t7([&]()
                   { x++; });
    t7.join();
    std::cout << "x: " << x << std::endl;

    // or

    std::thread t8([](int &x)
                   { x++; }, std::ref(x));
    t8.join();
    std::cout << "x: " << x << std::endl;

    std::cout << std::thread::hardware_concurrency() << std::endl; // Returns number of CPU cores (approx).

    // ✅ 2️⃣ Using std::promise + std::future (Professional Way) to get something back from thread------------------------
    std::promise<int> promise;
    std::future<int> future = promise.get_future();

    std::thread thread(getSomething, 5, std::move(promise));

    int res = future.get(); // waits for value
    thread.join();
    std::cout << res << std::endl;

    // ✅ 3️⃣ Best Modern Way: std::async---------------------------------------------------------
    // Why this is better
    // Automatically creates thread
    // Automatically joins
    // Automatically transfers return value
    // Automatically propagates exceptions
    // Less boilerplate. Safer.
    std::future<int> fut = std::async(std::launch::async, getint, 10);
    int resp = fut.get();
    std::cout << resp << std::endl;
    return 0;
}

// 13️⃣ Best Practices
// ✔ Always join or detach
// ✔ Prefer std::lock_guard over manual lock/unlock
// ✔ Avoid detach unless truly fire-and-forget
// ✔ Keep thread functions exception-safe
// ✔ Use RAII wrappers for thread joining

// 14️⃣ RAII Thread Wrapper (Modern Safe Pattern)
// class JoiningThread {
//     std::thread t;
// public:
//     template<typename... Args>
//     explicit JoiningThread(Args&&... args)
//         : t(std::forward<Args>(args)...) {}

//     ~JoiningThread() {
//         if (t.joinable())
//             t.join();
//     }
// };
// Now thread auto-joins.

// 🛑 Deadlock Example
// std::mutex m1, m2;

// void f1() {
//     std::lock_guard<std::mutex> l1(m1);
//     std::lock_guard<std::mutex> l2(m2);
// }

// void f2() {
//     std::lock_guard<std::mutex> l1(m2);
//     std::lock_guard<std::mutex> l2(m1);
// }
// If:
// T1 locks m1
// T2 locks m2
// Both wait forever.

// solution
//  ✅ Deadlock Solution
//  Use std::scoped_lock:
//  std::scoped_lock lock(m1, m2);
//  It uses deadlock-free locking algorithm internally.