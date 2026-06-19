//验证存储模块的可行性 
#include "storage/SettingsManager.h"
#include "storage/HistoryManager.h"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

void testAddRecord()
{
    HistoryManager manager;
    manager.addRecord("1+2", "3");
    manager.addRecord("2*5", "10");

    std::vector<HistoryRecord> records = manager.getRecords();

    assert(records.size() == 2);
    assert(records[0].getExpression() == "1+2");
    assert(records[0].getResult() == "3");
    assert(records[1].getExpression() == "2*5");
    assert(records[1].getResult() == "10");
}

void testRemoveRecord()
{
    HistoryManager manager;
    manager.addRecord("1+2", "3");
    manager.addRecord("2*5", "10");

    manager.removeRecord(0);

    std::vector<HistoryRecord> records = manager.getRecords();

    assert(records.size() == 1);
    assert(records[0].getExpression() == "2*5");
}

void testClearHistory()
{
    HistoryManager manager;
    manager.addRecord("1+2", "3");
    manager.addRecord("2*5", "10");

    manager.clearHistory();

    std::vector<HistoryRecord> records = manager.getRecords();
    assert(records.empty());
}

void testSearchHistory()
{
    HistoryManager manager;
    manager.addRecord("sin(30)", "0.5");
    manager.addRecord("1+2", "3");

    std::vector<HistoryRecord> result = manager.searchHistory("sin");

    assert(result.size() == 1);
    assert(result[0].getExpression() == "sin(30)");
}

void testSaveAndLoad()
{
    HistoryManager manager;
    manager.addRecord("1+2", "3");
    manager.addRecord("sqrt(16)", "4");

    manager.saveToFile("history_test.txt");

    HistoryManager anotherManager;
    anotherManager.loadFromFile("history_test.txt");

    std::vector<HistoryRecord> records = anotherManager.getRecords();

    assert(records.size() == 2);
    assert(records[0].getExpression() == "1+2");
    assert(records[0].getResult() == "3");
    assert(records[1].getExpression() == "sqrt(16)");
    assert(records[1].getResult() == "4");
}

void testSettingsManager()
{
    SettingsManager manager;

    assert(manager.getAngleMode() == "DEG");
    assert(manager.getPrecision() == 6);
    assert(manager.getTheme() == "light");

    manager.setAngleMode("RAD");
    manager.setPrecision(10);
    manager.setTheme("dark");

    manager.saveSettings("settings_test.txt");

    SettingsManager anotherManager;
    anotherManager.loadSettings("settings_test.txt");

    assert(anotherManager.getAngleMode() == "RAD");
    assert(anotherManager.getPrecision() == 10);
    assert(anotherManager.getTheme() == "dark");
}

int main()
{
    testAddRecord();
    testRemoveRecord();
    testClearHistory();
    testSearchHistory();
    testSaveAndLoad();
    testSettingsManager();

    std::cout << "Storage tests passed!" << std::endl;
    return 0;
}