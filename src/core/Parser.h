#pragma once

#include "core/ASTNode.h"
#include "core/Token.h"

#include <string>
#include <vector>

using namespace std;

// Parser 负责检查语法，并把 Token 序列转换成语法树。
class Parser {
public:
    Parser();

    ASTNode* parse(const string& expression);
    ASTNode* parse(const vector<Token>& inputTokens);

private:
    // 按照运算符优先级从低到高解析。
    ASTNode* parseExpression();
    ASTNode* parseTerm();
    ASTNode* parseUnary();
    ASTNode* parsePower();
    ASTNode* parsePostfix();
    ASTNode* parsePrimary();

    bool check(TokenType type) const;
    bool match(TokenType type);
    bool matchOperator(const string& op);
    Token advance();
    Token current() const;
    void expect(TokenType type, const string& message);
    string toLower(const string& text) const;

    vector<Token> tokens;
    int position;
};