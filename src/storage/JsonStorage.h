#pragma once
#include "storage/HistoryRecord.h"
#include <string>
#include <vector>

class JsonStorage
{
public:
    void saveHistory(const std::vector<HistoryRecord>& records, const std::string& fileName);
    std::vector<HistoryRecord> loadHistory(const std::string& fileName) const;
};