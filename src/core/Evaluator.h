#pragma once

#include "core/ASTNode.h"

#include <string>

using namespace std;

// Evaluator 遍历语法树，并计算最终结果。
class Evaluator {
public:
    double evaluate(const ASTNode* node) const;
    double evaluate(const ASTNode* node, double x) const;

    // 直接计算字符串表达式；第二个版本支持变量 x。
    double evaluateExpression(const string& expression) const;
    double evaluateExpression(const string& expression, double x) const;

private:
    double evaluateNode(const ASTNode* node, bool hasX, double x) const;
    double evaluateFunction(const ASTNode* node, bool hasX, double x) const;
    double factorial(double value) const;
    void requireOneArg(const ASTNode* node, const string& name) const;
    void requireTwoArgs(const ASTNode* node, const string& name) const;
};