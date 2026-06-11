#include "math/ComplexNumber.h"
using namespace std;
#include <cmath>
#include <stdexcept>
//构造函数
ComplexNumber::ComplexNumber(double realPart, double imaginaryPart) {
    real = realPart;
    imaginary = imaginaryPart;
}
//获取实部
double ComplexNumber::getReal() const {
    return real;
}
//获取虚部
double ComplexNumber::getImaginary() const {
    return imaginary;
}
//设置实部
void ComplexNumber::setReal(double realPart) {
    real = realPart;
}
//设置虚部
void ComplexNumber::setImaginary(double imaginaryPart) {
    imaginary = imaginaryPart;
}
//复数加法
// (a + bi) + (c + di) = (a + c) + (b + d)i
ComplexNumber ComplexNumber::add(ComplexNumber number) const {
    return ComplexNumber(real + number.real,imaginary + number.imaginary);
}
//复数减法
// (a + bi) - (c + di) = (a - c) + (b - d)i
ComplexNumber ComplexNumber::sub(ComplexNumber number) const {
    return ComplexNumber(real - number.real,imaginary - number.imaginary);
}
//复数乘法
// (a + bi)(c + di) = (ac - bd) + (ad + bc)i
ComplexNumber ComplexNumber::multiply(ComplexNumber number) const {
    double resultReal =
        real * number.real - imaginary * number.imaginary;
    double resultImaginary =
        real * number.imaginary + imaginary * number.real;

    return ComplexNumber(resultReal, resultImaginary);
}
//复数除法并且化简
// 分子和分母同时乘以除数的共轭复数。
ComplexNumber ComplexNumber::divide(ComplexNumber number) const {
    double denominator =number.real * number.real+ number.imaginary * number.imaginary;

    if (denominator == 0) {
        throw invalid_argument("Cannot divide by zero complex number.");
    }

    double resultReal =
        (real * number.real + imaginary * number.imaginary)/ denominator;
    double resultImaginary =(imaginary * number.real - real * number.imaginary)/ denominator;

    return ComplexNumber(resultReal, resultImaginary);
}
//求模长
double ComplexNumber::modulus() const {
    return sqrt(real * real + imaginary * imaginary);
}
//求共轭复数
ComplexNumber ComplexNumber::conjugate() const {
    return ComplexNumber(real, -imaginary);
}
