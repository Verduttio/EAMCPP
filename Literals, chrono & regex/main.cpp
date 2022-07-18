#include <iostream>
#include <chrono>

long fibonacci(unsigned n){
    if (n < 2) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

int main() {

  // time();

    using namespace std::chrono;
    auto p1 = steady_clock::now();

    auto s1 = system_clock::now();

    auto h1 = high_resolution_clock::now();

    fibonacci(37);

    auto p2 = steady_clock::now();
    auto s2 = system_clock::now();
    auto h2 = high_resolution_clock::now();

    auto printDuration = [](auto p1, auto p2) {
        duration<double> diff = p2 - p1;
        std::cout << diff.count() << std::endl;
        std::cout << duration_cast<nanoseconds>(diff).count() << std::endl;
    };
    printDuration(p1,p2);
    printDuration(s1,s2);
    printDuration(h1,h2);
    return 0;
}
