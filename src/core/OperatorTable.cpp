#include "core/OperatorTable.h"

using namespace std;

bool OperatorTable::isBinaryOperator(const string& op) const {
    return op == "+" || op == "-" || op == "*" || op == "/" || op == "^";
}

bool OperatorTable::isUnaryOperator(const string& op) const {
    return op == "+" || op == "-" || op == "!";
}

int OperatorTable::precedence(const string& op) const {
    // 数值越大，运算符优先级越高。
    if (op == "+" || op == "-") {
        return 1;
    }

    if (op == "*" || op == "/") {
        return 2;
    }

    if (op == "^") {
        return 3;
    }

    if (op == "!") {
        return 4;
    }

    return 0;
}

bool OperatorTable::isRightAssociative(const string& op) const {
    // 乘方右结合，所以 2^3^2 按 2^(3^2) 计算。
    return op == "^";
}
