#include "core/ASTNode.h"

using namespace std;

ASTNode::ASTNode(double number)
    : type(AST_NUMBER), number(number), text(""), left(0), right(0) {
}

ASTNode::ASTNode(ASTNodeType type, const string& text)
    : type(type), number(0), text(text), left(0), right(0) {
}

ASTNode::ASTNode(ASTNodeType type, const string& text, ASTNode* left)
    : type(type), number(0), text(text), left(left), right(0) {
}

ASTNode::ASTNode(ASTNodeType type, const string& text, ASTNode* left, ASTNode* right)
    : type(type), number(0), text(text), left(left), right(right) {
}

ASTNode::~ASTNode() {
    // 语法树由父节点管理子节点，释放根节点时递归释放整棵树。
    delete left;
    delete right;
}

ASTNodeType ASTNode::getType() const {
    return type;
}

double ASTNode::getNumber() const {
    return number;
}

const string& ASTNode::getText() const {
    return text;
}

ASTNode* ASTNode::getLeft() const {
    return left;
}

ASTNode* ASTNode::getRight() const {
    return right;
}
