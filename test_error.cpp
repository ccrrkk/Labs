#include <iostream>
#include <stdexcept>
#include <cstdlib>  // 引入 exit()

void divide(int numerator, int denominator) {
    if (denominator == 0) {
        throw std::runtime_error("Error: Division by zero");
    }
    std::cout << "Result: " << numerator / denominator << std::endl;
}

int main() {
    try {
        divide(10, 0);
    }
    catch (const std::exception& e) {
        // std::cerr << "Exception caught: " << e.what() << std::endl;
        // std::exit(1);  // 终止程序并返回非零退出状态
    }

    return 0;
}