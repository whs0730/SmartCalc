#pragma once

#include <string>

using namespace std;

// Lexer 拆分出来的最小单位类型。
enum TokenType {
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_OPERATOR,
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_COMMA,
    TOKEN_END
};

// Token 保存数字、名称、运算符、括号、逗号或结束标记。
class Token {
public:
    Token();
    explicit Token(TokenType type);
    Token(TokenType type, const string& text);
    Token(double number, const string& text);

    TokenType getType() const;
    const string& getText() const;
    double getNumber() const;

private:
    TokenType type;
    string text;
    double number;
};