#pragma once
//科学计算函数模块
// 科学计算类：封装三角函数、对数、开方、乘方和阶乘。
class ScientificFunction {
public:
    double sine(double radian) const;
    double cosine(double radian) const;
    double tangent(double radian) const;

    double naturalLog(double number) const;
    double logarithm(double number, double base) const;
    double squareRoot(double number) const;
    double power(double base, int exponent) const;
    long long factorial(int number) const;
};
