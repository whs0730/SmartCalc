#include "core/Evaluator.h"

#include <cassert>
#include <cmath>
#include <iostream>

bool isClose(double a, double b) {
    return std::abs(a - b) < 0.000001;
}

void testBasicOperators() {
    Evaluator evaluator;

    assert(isClose(evaluator.evaluateExpression("1+2*3"), 7));
    assert(isClose(evaluator.evaluateExpression("(1+2)*3"), 9));
    assert(isClose(evaluator.evaluateExpression("10/2-3"), 2));
    assert(isClose(evaluator.evaluateExpression("2^3^2"), 512));
    assert(isClose(evaluator.evaluateExpression("-2^2"), -4));
    assert(isClose(evaluator.evaluateExpression("2*-3"), -6));
}

void testFunctions() {
    Evaluator evaluator;

    assert(isClose(evaluator.evaluateExpression("sqrt(16)"), 4));
    assert(isClose(evaluator.evaluateExpression("squa(5)"), 25));
    assert(isClose(evaluator.evaluateExpression("pow(2,3)"), 8));
    assert(isClose(evaluator.evaluateExpression("log(100)"), 2));
    assert(isClose(evaluator.evaluateExpression("log(8,2)"), 3));
    assert(isClose(evaluator.evaluateExpression("ln(e)"), 1));
    assert(isClose(evaluator.evaluateExpression("sin(pi/2)"), 1));
    assert(isClose(evaluator.evaluateExpression("5!"), 120));
    assert(isClose(evaluator.evaluateExpression("fact(4)+1"), 25));
}

void testVariable() {
    Evaluator evaluator;

    assert(isClose(evaluator.evaluateExpression("x^2+2*x+1", 3), 16));
    assert(isClose(evaluator.evaluateExpression("sin(x)", 0), 0));
}

int main() {
    testBasicOperators();
    testFunctions();
    testVariable();

    std::cout << "Expression tests passed!" << std::endl;
    return 0;
}