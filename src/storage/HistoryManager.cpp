#include "storage/HistoryManager.h"
#include "utils/TimeUtil.h"
#include "storage/JsonStorage.h"

HistoryManager::HistoryManager(){}

void HistoryManager::addRecord(const std::string& expression, const std::string& result)
{
    // 新增记录时统一补上当前时间，调用者只需要传入输入和结果。
    std::string time = TimeUtil::getCurrentTime();
    HistoryRecord record(expression, result, time);
    records.push_back(record);
}

void HistoryManager::removeRecord(int index)
{
    if ((index >= 0) && index < (records.size()))
    {
        records.erase(records.begin() + index);
    }
}

void HistoryManager::clearHistory()
{
    records.clear();
}

std::vector<HistoryRecord> HistoryManager::getRecords() const
{
    return records;
}

std::vector<HistoryRecord> HistoryManager::searchHistory(const std::string& key) const
{
    std::vector<HistoryRecord> result;

    // 表达式、结果、时间三项中任意一项包含关键字，就加入搜索结果。
    for (int i = 0; i < records.size(); i++)
    {
        if (records[i].getExpression().find(key) != std::string::npos ||
            records[i].getResult().find(key) != std::string::npos ||
            records[i].getTimestamp().find(key) != std::string::npos)
        {
            result.push_back(records[i]);
        }
    }

    return result;
}

void HistoryManager::saveToFile(const std::string& fileName)
{
    JsonStorage jsonStorage;
    jsonStorage.saveHistory(records, fileName);
}

void HistoryManager::loadFromFile(const std::string& fileName)
{
    JsonStorage jsonStorage;
    records = jsonStorage.loadHistory(fileName);
}
