#include <iostream>

constexpr int compute(int x) {
    return x * x;
}

int main( int argc, char **argv) {
    constexpr int res = compute(5);
    std::cout << "result : " << res << std::endl;
    return 0;
}
