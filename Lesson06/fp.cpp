//
// Created by khanh on 4/24/2023.
//
#include <iostream>

int adder(int a, int b) {
    return a + b;
}
int adder(int a, int b, int c) {
    return a + b;
}

typedef int (IntCallback)(int a, int b);
typedef int (IntCallback2)(int a, int b, int c);

int exec_callback(IntCallback* func, int a, int b) {
    return func(a, b);
}
int exec_callback(IntCallback2* func, int a, int b, int c) {
    return func(a, b, c);
}

int main(int argc, char* argv[]) {
    std::cout << exec_callback(adder, 1, 2, 3) << std::endl;
}