#pragma once

#include "core/Token.h"

#include <string>
#include <vector>

using namespace std;

// Lexer 负责把用户输入的表达式字符串拆成 Token 序列。
class Lexer {
public:
    vector<Token> tokenize(const string& expression) const;

private:
    bool isIdentifierStart(char ch) const;
    bool isIdentifierPart(char ch) const;
};