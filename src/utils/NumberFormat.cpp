#include "utils/NumberFormat.h"

#include <cmath>
#include <iomanip>
#include <sstream>

using namespace std;

string NumberFormat::formatDouble(double value, int precision) {
    // 特殊值单独处理，避免输出结果因编译器不同而不统一。
    if (isnan(value)) {
        return "nan";
    }

    if (isinf(value)) {
        return value > 0 ? "inf" : "-inf";
    }

    return removeTrailingZeros(formatFixed(value, precision));
}

string NumberFormat::formatFixed(double value, int precision) {
    precision = normalizePrecision(precision);

    ostringstream output;
    output << fixed << setprecision(precision) << value;
    return output.str();
}

string NumberFormat::formatScientific(double value, int precision) {
    precision = normalizePrecision(precision);

    ostringstream output;
    output << scientific << setprecision(precision) << value;
    return output.str();
}

string NumberFormat::formatPercent(double value, int precision) {
    return formatDouble(value * 100, precision) + "%";
}

string NumberFormat::removeTrailingZeros(const string& text) {
    string result = text;
    int dot = static_cast<int>(result.find('.'));

    if (dot == static_cast<int>(string::npos)) {
        return result;
    }

    // 去掉小数末尾多余的 0，再去掉可能剩下的小数点。
    while (!result.empty() && result[result.size() - 1] == '0') {
        result.erase(result.size() - 1);
    }

    if (!result.empty() && result[result.size() - 1] == '.') {
        result.erase(result.size() - 1);
    }

    if (result == "-0") {
        result = "0";
    }

    return result;
}

double NumberFormat::roundTo(double value, int precision) {
    precision = normalizePrecision(precision);
    double scale = pow(10.0, precision);
    return round(value * scale) / scale;
}

bool NumberFormat::isClose(double a, double b, double epsilon) {
    if (epsilon < 0) {
        epsilon = -epsilon;
    }

    return abs(a - b) <= epsilon;
}

int NumberFormat::normalizePrecision(int precision) {
    if (precision < 0) {
        return 0;
    }

    if (precision > 15) {
        return 15;
    }

    return precision;
}
