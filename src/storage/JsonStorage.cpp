#include "storage/JsonStorage.h"
#include <fstream>
#include <sstream>

void JsonStorage::saveHistory(const std::vector<HistoryRecord>& records, const std::string& fileName)
{
    std::ofstream outFile(fileName);

    // 每条历史记录占三行，分隔线用于提高文件可读性。
    for (int i = 0; i < records.size(); i++)
    {
        outFile << records[i].getExpression() << '\n';
        outFile << records[i].getResult() << '\n';
        outFile << records[i].getTimestamp() << '\n';
        outFile << "----" << '\n';
    }

    outFile.close();
}

std::vector<HistoryRecord> JsonStorage::loadHistory(const std::string& fileName) const
{
    std::vector<HistoryRecord> records;
    std::ifstream inFile(fileName);

    if (!inFile.is_open())
    {
        return records;
    }

    std::string expression;
    std::string result;
    std::string timestamp;
    std::string line;

    // 读取顺序必须和 saveHistory 中写入顺序一致。
    while (std::getline(inFile, expression))
    {
        std::getline(inFile, result);
        std::getline(inFile, timestamp);
        std::getline(inFile, line);

        HistoryRecord record(expression, result, timestamp);
        records.push_back(record);
    }

    inFile.close();
    return records;
}
