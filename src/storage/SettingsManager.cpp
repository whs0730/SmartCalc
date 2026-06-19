#include "SettingsManager.h"
#include <fstream>

SettingsManager::SettingsManager()
{
    angleMode = "DEG";
    precision = 6;
    theme = "light";
}

void SettingsManager::setAngleMode(const std::string& mode)
{
    angleMode = mode;
}

void SettingsManager::setPrecision(int value)
{
    precision = value;
}

void SettingsManager::setTheme(const std::string& style)
{
    theme = style;
}

std::string SettingsManager::getAngleMode() const
{
    return angleMode;
}

int SettingsManager::getPrecision() const
{
    return precision;
}

std::string SettingsManager::getTheme() const
{
    return theme;
}

void SettingsManager::saveSettings(const std::string& fileName)
{
    std::ofstream fout(fileName);

    fout << angleMode << '\n';
    fout << precision << '\n';
    fout << theme << '\n';

    fout.close();
}

void SettingsManager::loadSettings(const std::string& fileName)
{
    std::ifstream fin(fileName);

    if (!fin.is_open())
    {
        return;
    }

    fin >> angleMode;
    fin >> precision;
    fin >> theme;

    fin.close();
}