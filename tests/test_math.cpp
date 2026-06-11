#include "math/ComplexNumber.h"
#include "math/FunctionSampler.h"
#include "math/ScientificFunction.h"
#include "math/UnitConverter.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

bool isClose(double a, double b) {
    return abs(a - b) < 0.000001;
}

double square(double x) {
    return x * x;
}

void testComplexNumber() {
    ComplexNumber a(3, 4);
    ComplexNumber b(1, -2);

    ComplexNumber sum = a.add(b);
    assert(isClose(sum.getReal(), 4));
    assert(isClose(sum.getImaginary(), 2));

    ComplexNumber product = a.multiply(b);
    assert(isClose(product.getReal(), 11));
    assert(isClose(product.getImaginary(), -2));

    ComplexNumber quotient = a.divide(b);
    assert(isClose(quotient.getReal(), -1));
    assert(isClose(quotient.getImaginary(), 2));
    assert(isClose(a.modulus(), 5));

    bool hasError = false;

    try {
        a.divide(ComplexNumber(0, 0));
    }
    catch (invalid_argument&) {
        hasError = true;
    }

    assert(hasError);
}

void testScientificFunction() {
    ScientificFunction function;
    const double PI = 3.14159265358979323846;

    assert(isClose(function.sine(PI / 2), 1));
    assert(isClose(function.cosine(0), 1));
    assert(isClose(function.logarithm(100, 10), 2));
    assert(isClose(function.squareRoot(81), 9));
    assert(isClose(function.power(2, -3), 0.125));
    assert(function.factorial(5) == 120);

    bool hasError = false;

    try {
        function.squareRoot(-1);
    }
    catch (invalid_argument&) {
        hasError = true;
    }

    assert(hasError);
}

void testFunctionSampler() {
    FunctionSampler sampler;
    vector<SamplePoint> points = sampler.sample(0, 2, 3, square);

    assert(points.size() == 3);
    assert(isClose(points[0].x, 0));
    assert(isClose(points[1].x, 1));
    assert(isClose(points[1].y, 1));
    assert(isClose(points[2].x, 2));
    assert(isClose(points[2].y, 4));

    bool hasError = false;

    try {
        sampler.sample(0, 2, 1, square);
    }
    catch (invalid_argument&) {
        hasError = true;
    }

    assert(hasError);
}

void testUnitConverter() {
    UnitConverter converter;
    const double PI = 3.14159265358979323846;

    assert(isClose(converter.degreeToRadian(180), PI));
    assert(isClose(converter.radianToDegree(PI / 2), 90));
    assert(isClose(
        converter.convertLength(
            1,
            UnitConverter::KILOMETER,
            UnitConverter::METER
        ),
        1000
    ));
    assert(isClose(
        converter.convertTemperature(
            0,
            UnitConverter::CELSIUS,
            UnitConverter::FAHRENHEIT
        ),
        32
    ));

    bool hasError = false;

    try {
        converter.convertTemperature(-1,UnitConverter::KELVIN,UnitConverter::CELSIUS);
    }
    catch (invalid_argument&) {
        hasError = true;
    }

    assert(hasError);
}

int main() {
    testComplexNumber();
    testScientificFunction();
    testFunctionSampler();
    testUnitConverter();

    cout << "Math tests passed!" << endl;
    return 0;
}
