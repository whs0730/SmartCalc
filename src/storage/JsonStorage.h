#pragma once
#include "storage/HistoryRecord.h"
#include <string>
#include <vector>

// 历史记录文件读写类，当前使用简单文本格式保存记录。
class JsonStorage
{
public:
    void saveHistory(const std::vector<HistoryRecord>& records, const std::string& fileName);
    std::vector<HistoryRecord> loadHistory(const std::string& fileName) const;
};
