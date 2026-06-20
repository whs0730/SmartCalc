#pragma once

#include <string>

using namespace std;

// 保存 core 模块使用的基本运算符信息。
class OperatorTable {
public:
    bool isBinaryOperator(const string& op) const;
    bool isUnaryOperator(const string& op) const;
    int precedence(const string& op) const;
    bool isRightAssociative(const string& op) const;
};