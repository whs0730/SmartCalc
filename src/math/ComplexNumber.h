#pragma once
//复数模块
// 复数类：保存实部和虚部，并提供常用的复数计算。
class ComplexNumber {
private:
    double real;
    double imaginary;

public:
    ComplexNumber(double realPart = 0, double imaginaryPart = 0);

    double getReal() const;
    double getImaginary() const;
    void setReal(double realPart);
    void setImaginary(double imaginaryPart);

    ComplexNumber add(ComplexNumber number) const;//加法
    ComplexNumber sub(ComplexNumber number) const;//减法
    ComplexNumber multiply(ComplexNumber number) const;//乘法
    ComplexNumber divide(ComplexNumber number) const;//触发

    double modulus() const;//求模
    ComplexNumber conjugate() const;//求共轭
};
