#pragma once
#include <string>
#include <vector>
#include "storage/HistoryRecord.h"

class HistoryManager
{
public:
    HistoryManager();
    void addRecord(const std::string& expression,const std::string& result);
    void removeRecord(int index);
    void clearHistory();
    void saveToFile(const std::string& fileName);
    void loadFromFile(const std::string& fileName);

    std::vector<HistoryRecord> getRecords() const;
    std::vector<HistoryRecord> searchHistory(const std::string& keyword) const;

private:
    std::vector<HistoryRecord> records;

};