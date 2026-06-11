#include "math/ScientificFunction.h"
using namespace std;
#include <cmath>
#include <stdexcept>
//正弦函数
double ScientificFunction::sine(double radian) const {
    return sin(radian);
}
//余弦函数
double ScientificFunction::cosine(double radian) const {
    return cos(radian);
}
//正切函数
double ScientificFunction::tangent(double radian) const {
    // cos(x) 接近 0 时，tan(x) 没有有限值。
    if (abs(std::cos(radian)) < 0.000000000001) {
        throw invalid_argument("Tangent is undefined at this angle.");
    }

    return tan(radian);
}
//e自然对数
double ScientificFunction::naturalLog(double number) const {
    if (number <= 0) {
        throw invalid_argument("Logarithm requires a positive number.");
    }

    return log(number);
}
//自定义对数（真数，底数）
double ScientificFunction::logarithm(double number, double base) const {
    if (number <= 0 || base <= 0 || base == 1) {
        throw invalid_argument("Logarithm number or base is invalid.");
    }

    // 换底公式：log_base(number) = ln(number) / ln(base)。
    return log(number) / log(base);
}
//开根号
double ScientificFunction::squareRoot(double number) const {
    if (number < 0) {
        throw invalid_argument(
            "Square root requires a non-negative number."
        );
    }

    return  sqrt(number);
}
//求次幂
double ScientificFunction::power(double base, int exponent) const {
    if (base == 0 && exponent < 0) {
        throw invalid_argument(
            "Zero cannot have a negative exponent."
        );
    }

    double result = 1;
    int count = exponent;

    if (count < 0) {
        count = -count;
    }

    // 用循环计算整数次幂
    for (int i = 0; i < count; i++) {
        result *= base;
    }

    if (exponent < 0) {
        result = 1 / result;
    }

    return result;
}//求阶乘（最多到20）
long long ScientificFunction::factorial(int number) const {
    if (number < 0) {
        throw invalid_argument(
            "Factorial requires a non-negative integer."
        );
    }

    // long long 最大只能安全保存到 20!。
    if (number > 20) {
        throw out_of_range("Factorial result is too large.");
    }

    long long result = 1;

    for (int i = 2; i <= number; i++) {
        result *= i;
    }

    return result;
}
