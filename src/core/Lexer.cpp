#include "core/Lexer.h"

#include "core/CalcException.h"

#include <cctype>
#include <string>

using namespace std;

bool Lexer::isIdentifierStart(char ch) const {
    unsigned char value = static_cast<unsigned char>(ch);
    return isalpha(value) || ch == '_';
}

bool Lexer::isIdentifierPart(char ch) const {
    unsigned char value = static_cast<unsigned char>(ch);
    return isalnum(value) || ch == '_';
}

vector<Token> Lexer::tokenize(const string& expression) const {
    // 从左到右扫描字符串，把内容拆成 Token。
    vector<Token> tokens;
    int i = 0;
    int length = static_cast<int>(expression.size());

    while (i < length) {
        char ch = expression[i];
        unsigned char value = static_cast<unsigned char>(ch);

        if (isspace(value)) {
            i++;
            continue;
        }

        if (i + 2 <= length && expression.compare(i, 2, "\xC3\x97") == 0) {
            tokens.push_back(Token(TOKEN_OPERATOR, "*"));
            i += 2;
            continue;
        }

        if (i + 2 <= length && expression.compare(i, 2, "\xC3\xB7") == 0) {
            tokens.push_back(Token(TOKEN_OPERATOR, "/"));
            i += 2;
            continue;
        }

        if (i + 3 <= length && expression.compare(i, 3, "\xE2\x88\x9A") == 0) {
            tokens.push_back(Token(TOKEN_IDENTIFIER, "sqrt"));
            i += 3;
            continue;
        }

        // 识别数字，例如 3、3.14 和 1e-3。
        if (isdigit(value) || ch == '.') {
            int start = i;
            bool hasDigit = false;
            bool hasDot = false;

            while (i < length) {
                char current = expression[i];
                unsigned char currentValue = static_cast<unsigned char>(current);

                if (isdigit(currentValue)) {
                    hasDigit = true;
                    i++;
                }
                else if (current == '.' && !hasDot) {
                    hasDot = true;
                    i++;
                }
                else {
                    break;
                }
            }

            if (!hasDigit) {
                throw LexerException("Number is invalid.");
            }

            if (i < length && (expression[i] == 'e' || expression[i] == 'E')) {
                int expStart = i;
                i++;

                if (i < length && (expression[i] == '+' || expression[i] == '-')) {
                    i++;
                }

                bool hasExpDigit = false;
                while (i < length) {
                    unsigned char currentValue = static_cast<unsigned char>(expression[i]);
                    if (!isdigit(currentValue)) {
                        break;
                    }
                    hasExpDigit = true;
                    i++;
                }

                if (!hasExpDigit) {
                    i = expStart;
                }
            }

            string text = expression.substr(start, i - start);
            tokens.push_back(Token(stod(text), text));
            continue;
        }

        // 识别名称，例如 sin、cos、pi 和 x。
        if (isIdentifierStart(ch)) {
            int start = i;
            i++;
            while (i < length && isIdentifierPart(expression[i])) {
                i++;
            }

            tokens.push_back(Token(TOKEN_IDENTIFIER, expression.substr(start, i - start)));
            continue;
        }

        if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '!') {
            tokens.push_back(Token(TOKEN_OPERATOR, string(1, ch)));
            i++;
            continue;
        }

        if (ch == '(') {
            tokens.push_back(Token(TOKEN_LEFT_PAREN, "("));
            i++;
            continue;
        }

        if (ch == ')') {
            tokens.push_back(Token(TOKEN_RIGHT_PAREN, ")"));
            i++;
            continue;
        }

        if (ch == ',') {
            tokens.push_back(Token(TOKEN_COMMA, ","));
            i++;
            continue;
        }

        throw LexerException("Unknown character in expression.");
    }

    // 结尾 Token 用来帮助 Parser 判断表达式是否已经解析完。
    tokens.push_back(Token(TOKEN_END));
    return tokens;
}