#include "storage/JsonStorage.h"
#include <fstream>
#include <sstream>

void JsonStorage::saveHistory(const std::vector<HistoryRecord>& records, const std::string& fileName)
{
    std::ofstream outFile(fileName);

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
