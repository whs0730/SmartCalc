#pragma once

#include <string>

using namespace std;

// 数字格式化工具类，统一控制结果显示形式。
class NumberFormat {
public:
    static string formatDouble(double value, int precision = 6);
    static string formatFixed(double value, int precision = 6);
    static string formatScientific(double value, int precision = 6);
    static string formatPercent(double value, int precision = 2);

    static string removeTrailingZeros(const string& text);
    static double roundTo(double value, int precision);
    static bool isClose(double a, double b, double epsilon = 0.000001);

private:
    // 限制精度范围，避免输出过长或精度参数非法。
    static int normalizePrecision(int precision);
};
