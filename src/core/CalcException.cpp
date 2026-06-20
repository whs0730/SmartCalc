#include "core/CalcException.h"

using namespace std;

CalcException::CalcException(const string& message)
    : runtime_error(message) {
}

// 下面几个异常类型只区分出错阶段，错误信息仍交给基类保存。
LexerException::LexerException(const string& message)
    : CalcException(message) {
}

ParserException::ParserException(const string& message)
    : CalcException(message) {
}

EvaluatorException::EvaluatorException(const string& message)
    : CalcException(message) {
}
