#pragma once

#include <string>

using namespace std;

// 抽象语法树节点的类型。
enum ASTNodeType {
    AST_NUMBER,
    AST_VARIABLE,
    AST_UNARY,
    AST_BINARY,
    AST_FUNCTION
};

// ASTNode 用树结构保存表达式，例如 1 + 2 * 3。
class ASTNode {
public:
    explicit ASTNode(double number);
    ASTNode(ASTNodeType type, const string& text);
    ASTNode(ASTNodeType type, const string& text, ASTNode* left);
    ASTNode(ASTNodeType type, const string& text, ASTNode* left, ASTNode* right);
    ~ASTNode();

    ASTNodeType getType() const;
    double getNumber() const;
    const string& getText() const;
    ASTNode* getLeft() const;
    ASTNode* getRight() const;

private:
    // 当前节点负责释放左右子节点，所以禁止复制，避免重复 delete。
    ASTNode(const ASTNode&);
    ASTNode& operator=(const ASTNode&);

    ASTNodeType type;
    double number;
    string text;
    ASTNode* left;
    ASTNode* right;
};