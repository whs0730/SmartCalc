#include "core/Token.h"

using namespace std;

Token::Token()
    : type(TOKEN_END), text(""), number(0) {
}

Token::Token(TokenType type)
    : type(type), text(""), number(0) {
}

Token::Token(TokenType type, const string& text)
    : type(type), text(text), number(0) {
}

Token::Token(double number, const string& text)
    : type(TOKEN_NUMBER), text(text), number(number) {
}

TokenType Token::getType() const {
    return type;
}

const string& Token::getText() const {
    return text;
}

double Token::getNumber() const {
    return number;
}
