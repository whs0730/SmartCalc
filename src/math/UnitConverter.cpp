#include "math/UnitConverter.h"
using namespace std;
#include <stdexcept>
//角度转为弧度
double UnitConverter::degreeToRadian(double degree) const {
    const double PI = 3.14159265358979323846;
    return degree * PI / 180;
}
//弧度转为角度
double UnitConverter::radianToDegree(double radian) const {
    const double PI = 3.14159265358979323846;
    return radian * 180 / PI;
}
//任意长度单位转换
double UnitConverter::convertLength(double value,LengthUnit fromUnit,LengthUnit toUnit) const {
    // 先统一换算成米，再从米换算成目标单位。
    double meterValue = lengthToMeter(value, fromUnit);
    return meterToLength(meterValue, toUnit);
}
//任意长度单位转换为米
double UnitConverter::lengthToMeter(double value,LengthUnit unit) const {
    switch (unit) {
    case MILLIMETER:
        return value / 1000;
    case CENTIMETER:
        return value / 100;
    case METER:
        return value;
    case KILOMETER:
        return value * 1000;
    default:
        throw invalid_argument("Unknown length unit.");
    }
}
//米转换为任意长度单位
double UnitConverter::meterToLength(double value,LengthUnit unit) const {
    switch (unit) {
    case MILLIMETER:
        return value * 1000;
    case CENTIMETER:
        return value * 100;
    case METER:
        return value;
    case KILOMETER:
        return value / 1000;
    default:
        throw invalid_argument("Unknown length unit.");
    }
}
//任意温度单位转换
double UnitConverter::convertTemperature(double value,TemperatureUnit fromUnit,TemperatureUnit toUnit) const {
    // 温度统一先换算成摄氏度，便于复用转换公式。
    double celsiusValue = temperatureToCelsius(value, fromUnit);

    if (celsiusValue < -273.15) {
        throw invalid_argument(
            "Temperature cannot be below absolute zero."
        );
    }

    return celsiusToTemperature(celsiusValue, toUnit);
}
//任意温度单位转为摄氏度
double UnitConverter::temperatureToCelsius(double value,TemperatureUnit unit) const {
    switch (unit) {
    case CELSIUS:
        return value;
    case FAHRENHEIT:
        return (value - 32) * 5 / 9;
    case KELVIN:
        return value - 273.15;
    default:
        throw invalid_argument("Unknown temperature unit.");
    }
}
//摄氏度转换为任意温度单位

double UnitConverter::celsiusToTemperature(double value,TemperatureUnit unit) const {
    switch (unit) {
    case CELSIUS:
        return value;
    case FAHRENHEIT:
        return value * 9 / 5 + 32;
    case KELVIN:
        return value + 273.15;
    default:
        throw invalid_argument("Unknown temperature unit.");
    }
}
