#pragma once

#include <stdexcept>
#include <string>

using namespace std;

// 计算器 core 模块的异常基类，方便外层统一捕获。
class CalcException : public runtime_error {
public:
    explicit CalcException(const string& message);
};

// 分词阶段的错误，例如出现无法识别的字符。
class LexerException : public CalcException {
public:
    explicit LexerException(const string& message);
};

// 语法分析阶段的错误，例如括号不匹配。
class ParserException : public CalcException {
public:
    explicit ParserException(const string& message);
};

// 求值阶段的错误，例如除零或函数参数非法。
class EvaluatorException : public CalcException {
public:
    explicit EvaluatorException(const string& message);
};