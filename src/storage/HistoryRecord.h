#pragma once
#include <string>

class HistoryRecord 
{
public:
    HistoryRecord();
    HistoryRecord( const std::string& expression,const std::string& result,const std::string& timestamp);

    const std::string& getExpression() const;
    const std::string& getResult() const;
    const std::string& getTimestamp() const;

    void setExpression(const std::string& expression);
    void setResult(const std::string& result);
    void setTimestamp(const std::string& timestamp);

private:
    std::string expression;
    std::string result;
    std::string timestamp;
};
