#include "storage/HistoryRecord.h"

HistoryRecord::HistoryRecord()
    : expression(""), result(""), timestamp("") {}

HistoryRecord::HistoryRecord(const std::string& expression,const std::string& result,const std::string& timestamp): 
expression(expression), result(result), timestamp(timestamp) {}

const std::string& HistoryRecord::getExpression() const
{
    return expression;
}

const std::string& HistoryRecord::getResult() const 
{
    return result;
}

const std::string& HistoryRecord::getTimestamp() const 
{
    return timestamp;
}

void HistoryRecord::setExpression(const std::string& expression) 
{
    this->expression = expression;
}

void HistoryRecord::setResult(const std::string& result) 
{
    this->result = result;
}

void HistoryRecord::setTimestamp(const std::string& time) 
{
    this->timestamp = time;
}
