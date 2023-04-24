//
// Created by khanh on 4/24/2023.
//
#include <iostream>

void printSomething(float data) {
    std::cout << data << std::endl;
}

void printSomething(int data) {
    std::cout << data << std::endl;
}

int main() {
    void (*func) (float) = printSomething; // Auto-casted to the correct address that matches the types
    void (*addr) (int) = &printSomething;
    func(2.0);
    (*func)(2.0);

    addr(2.0);
    (*addr)(2.0);

    std::cout << ((void *)func == (void *)addr) << std::endl;
}