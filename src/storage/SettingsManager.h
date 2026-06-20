#pragma once
#include <string>

// 程序设置管理类，保存角度模式、显示精度和主题。
class SettingsManager
{
public:
    SettingsManager();

    void setAngleMode(const std::string& mode);
    void setPrecision(int value);
    void setTheme(const std::string& style);

    std::string getAngleMode() const;
    int getPrecision() const;
    std::string getTheme() const;

    void saveSettings(const std::string& fileName);
    void loadSettings(const std::string& fileName);

private:
    std::string angleMode;
    int precision;
    std::string theme;
};
