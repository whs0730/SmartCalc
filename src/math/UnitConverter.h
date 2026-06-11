#pragma once
//单位转换模块
// 单位转换类：提供角度、长度和温度之间的常用转换。
class UnitConverter {
public:
    //长度单位枚举
    enum LengthUnit {
        MILLIMETER,
        CENTIMETER,
        METER,
        KILOMETER
    };
    //温度单位枚举
    enum TemperatureUnit {
        CELSIUS,
        FAHRENHEIT,
        KELVIN
    };

    double degreeToRadian(double degree) const;//角度转为弧度
    double radianToDegree(double radian) const;//弧度转为角度
    //任意长度单位转换
    double convertLength(
        double value,
        LengthUnit fromUnit,
        LengthUnit toUnit
    ) const;
    //任意温度单位转换
    double convertTemperature(
        double value,
        TemperatureUnit fromUnit,
        TemperatureUnit toUnit
    ) const;

private:
    double lengthToMeter(double value, LengthUnit unit) const;//任意长度单位转换为米
    double meterToLength(double value, LengthUnit unit) const;//米转换为任意长度单位
    //任意温度单位转为摄氏度
    double temperatureToCelsius(
        double value,
        TemperatureUnit unit
    ) const;
    //摄氏度转换为任意温度单位
    double celsiusToTemperature(
        double value,
        TemperatureUnit unit
    ) const;
};
