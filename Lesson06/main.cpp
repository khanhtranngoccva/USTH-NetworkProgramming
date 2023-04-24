//
// Created by khanh on 4/24/2023.
//
#include <cmath>
#include <iostream>

typedef double (OneVariableFunction)(double);
typedef double (DerivativeAtPointFunction)(double, double);

double simpson13(OneVariableFunction* func, double start, double end) {
    double startResult = func(start);
    double midpointResult = func((start + end) / 2);
    double endResult = func(end);
    return (end - start) / 6 * (startResult + 4 * midpointResult + endResult);
};

double runge_kutta(DerivativeAtPointFunction* derivativeAtPointFunction, double startX, double startY, double endX, double accuracy) {
    double x = startX, y = startY, stepSize = (endX - startX) / accuracy;
    std::cout << stepSize << std::endl;
    for (int i = 0; i < accuracy; i++) {
        double k1 = derivativeAtPointFunction(x, y);
        double k2 = derivativeAtPointFunction(x + stepSize / 2, y + stepSize * k1 / 2);
        double k3 = derivativeAtPointFunction(x + stepSize / 2, y + stepSize * k2 / 2);
        double k4 = derivativeAtPointFunction(x + stepSize, y + stepSize * k3);
        y += stepSize * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        x += stepSize;
    }
    return y;
};

double quadratic(double x) {
    return pow(x, 2);
}

double exampleDerivative(double x, double y) {
    return x * y;
}

int main(int argc, char* argv[]) {
    std::cout << simpson13(&quadratic, 1, 3) << std::endl;
    std::cout << runge_kutta(&exampleDerivative, 0, 1, 3, 10) << std::endl;
}