#include "core/Parser.h"

#include "core/CalcException.h"
#include "core/Lexer.h"

#include <cctype>

using namespace std;

Parser::Parser()
    : position(0) {
}

ASTNode* Parser::parse(const string& expression) {
    // 先分词，再解析 Token 序列。
    Lexer lexer;
    return parse(lexer.tokenize(expression));
}

ASTNode* Parser::parse(const vector<Token>& inputTokens) {
    tokens = inputTokens;
    position = 0;

    ASTNode* root = parseExpression();

    if (!check(TOKEN_END)) {
        delete root;
        throw ParserException("Unexpected token at end of expression.");
    }

    return root;
}

ASTNode* Parser::parseExpression() {
    // 加法和减法的优先级最低。
    ASTNode* left = parseTerm();

    while (check(TOKEN_OPERATOR)
        && (current().getText() == "+" || current().getText() == "-")) {
        string op = advance().getText();
        ASTNode* right = 0;

        try {
            right = parseTerm();
            left = new ASTNode(AST_BINARY, op, left, right);
        }
        catch (...) {
            delete left;
            delete right;
            throw;
        }
    }

    return left;
}

ASTNode* Parser::parseTerm() {
    // 乘法和除法的优先级高于加法和减法。
    ASTNode* left = parseUnary();

    while (check(TOKEN_OPERATOR)
        && (current().getText() == "*" || current().getText() == "/")) {
        string op = advance().getText();
        ASTNode* right = 0;

        try {
            right = parseUnary();
            left = new ASTNode(AST_BINARY, op, left, right);
        }
        catch (...) {
            delete left;
            delete right;
            throw;
        }
    }

    return left;
}

ASTNode* Parser::parseUnary() {
    // 处理一元正号和负号，例如 -3 或 +5。
    if (check(TOKEN_OPERATOR)
        && (current().getText() == "+" || current().getText() == "-")) {
        string op = advance().getText();
        ASTNode* child = parseUnary();
        return new ASTNode(AST_UNARY, op, child);
    }

    return parsePower();
}

ASTNode* Parser::parsePower() {
    // 乘方是右结合：2^3^2 表示 2^(3^2)。
    ASTNode* left = parsePostfix();

    if (matchOperator("^")) {
        ASTNode* right = 0;

        try {
            right = parseUnary();
            left = new ASTNode(AST_BINARY, "^", left, right);
        }
        catch (...) {
            delete left;
            delete right;
            throw;
        }
    }

    return left;
}

ASTNode* Parser::parsePostfix() {
    // 处理后缀阶乘，例如 5!。
    ASTNode* node = parsePrimary();

    while (matchOperator("!")) {
        node = new ASTNode(AST_UNARY, "!", node);
    }

    return node;
}

ASTNode* Parser::parsePrimary() {
    // 处理数字、常量、变量、函数和括号。
    if (check(TOKEN_NUMBER)) {
        double number = advance().getNumber();
        return new ASTNode(number);
    }

    if (check(TOKEN_IDENTIFIER)) {
        string name = toLower(advance().getText());

        if (name == "pi") {
            return new ASTNode(3.14159265358979323846);
        }

        if (name == "e") {
            return new ASTNode(2.71828182845904523536);
        }

        if (match(TOKEN_LEFT_PAREN)) {
            ASTNode* first = 0;
            ASTNode* second = 0;

            try {
                first = parseExpression();

                if (match(TOKEN_COMMA)) {
                    second = parseExpression();
                }

                expect(TOKEN_RIGHT_PAREN, "Missing right parenthesis after function.");
                return new ASTNode(AST_FUNCTION, name, first, second);
            }
            catch (...) {
                delete first;
                delete second;
                throw;
            }
        }

        return new ASTNode(AST_VARIABLE, name);
    }

    if (match(TOKEN_LEFT_PAREN)) {
        ASTNode* node = parseExpression();

        try {
            expect(TOKEN_RIGHT_PAREN, "Missing right parenthesis.");
        }
        catch (...) {
            delete node;
            throw;
        }

        return node;
    }

    throw ParserException("Expression is incomplete.");
}

bool Parser::check(TokenType type) const {
    if (position < 0 || position >= static_cast<int>(tokens.size())) {
        return type == TOKEN_END;
    }

    return tokens[position].getType() == type;
}

bool Parser::match(TokenType type) {
    if (!check(type)) {
        return false;
    }

    advance();
    return true;
}

bool Parser::matchOperator(const string& op) {
    if (!check(TOKEN_OPERATOR) || current().getText() != op) {
        return false;
    }

    advance();
    return true;
}

Token Parser::advance() {
    if (position < static_cast<int>(tokens.size())) {
        position++;
    }

    return tokens[position - 1];
}

Token Parser::current() const {
    if (position < 0 || position >= static_cast<int>(tokens.size())) {
        return Token(TOKEN_END);
    }

    return tokens[position];
}

void Parser::expect(TokenType type, const string& message) {
    if (!match(type)) {
        throw ParserException(message);
    }
}

string Parser::toLower(const string& text) const {
    string result = text;

    for (int i = 0; i < static_cast<int>(result.size()); i++) {
        unsigned char value = static_cast<unsigned char>(result[i]);
        result[i] = static_cast<char>(tolower(value));
    }

    return result;
}