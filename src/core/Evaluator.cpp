#include "core/Evaluator.h"

#include "core/CalcException.h"
#include "core/Parser.h"

#include <cmath>

using namespace std;

namespace {
    const double EPS = 0.000000000001;
}

double Evaluator::evaluate(const ASTNode* node) const {
    return evaluateNode(node, false, 0);
}

double Evaluator::evaluate(const ASTNode* node, double x) const {
    return evaluateNode(node, true, x);
}

double Evaluator::evaluateExpression(const string& expression) const {
    // 对外提供的便捷接口：字符串表达式 -> 语法树 -> 计算结果。
    Parser parser;
    ASTNode* root = parser.parse(expression);

    try {
        double result = evaluate(root);
        delete root;
        return result;
    }
    catch (...) {
        delete root;
        throw;
    }
}

double Evaluator::evaluateExpression(const string& expression, double x) const {
    // 带变量 x 的版本，后续函数绘图采样时可以复用。
    Parser parser;
    ASTNode* root = parser.parse(expression);

    try {
        double result = evaluate(root, x);
        delete root;
        return result;
    }
    catch (...) {
        delete root;
        throw;
    }
}

double Evaluator::evaluateNode(const ASTNode* node, bool hasX, double x) const {
    // 按节点类型递归计算当前节点和它的子节点。
    if (node == 0) {
        throw EvaluatorException("Expression node is empty.");
    }

    if (node->getType() == AST_NUMBER) {
        return node->getNumber();
    }

    if (node->getType() == AST_VARIABLE) {
        if (hasX && node->getText() == "x") {
            return x;
        }

        throw EvaluatorException("Unknown variable: " + node->getText());
    }

    if (node->getType() == AST_UNARY) {
        double value = evaluateNode(node->getLeft(), hasX, x);
        string op = node->getText();

        if (op == "+") {
            return value;
        }

        if (op == "-") {
            return -value;
        }

        if (op == "!") {
            return factorial(value);
        }

        throw EvaluatorException("Unknown unary operator: " + op);
    }

    if (node->getType() == AST_BINARY) {
        double left = evaluateNode(node->getLeft(), hasX, x);
        double right = evaluateNode(node->getRight(), hasX, x);
        string op = node->getText();

        if (op == "+") {
            return left + right;
        }

        if (op == "-") {
            return left - right;
        }

        if (op == "*") {
            return left * right;
        }

        if (op == "/") {
            if (abs(right) < EPS) {
                throw EvaluatorException("Division by zero.");
            }
            return left / right;
        }

        if (op == "^") {
            double result = pow(left, right);
            if (!isfinite(result)) {
                throw EvaluatorException("Power result is invalid.");
            }
            return result;
        }

        throw EvaluatorException("Unknown binary operator: " + op);
    }

    if (node->getType() == AST_FUNCTION) {
        return evaluateFunction(node, hasX, x);
    }

    throw EvaluatorException("Unknown expression node.");
}

double Evaluator::evaluateFunction(const ASTNode* node, bool hasX, double x) const {
    // 函数节点用 left 保存第一个参数，用 right 保存第二个参数。
    string name = node->getText();
    double first = evaluateNode(node->getLeft(), hasX, x);
    bool hasSecond = node->getRight() != 0;
    double second = 0;

    if (hasSecond) {
        second = evaluateNode(node->getRight(), hasX, x);
    }

    if (name == "sin") {
        requireOneArg(node, name);
        return sin(first);
    }

    if (name == "cos") {
        requireOneArg(node, name);
        return cos(first);
    }

    if (name == "tan") {
        requireOneArg(node, name);
        if (abs(cos(first)) < EPS) {
            throw EvaluatorException("Tangent is undefined.");
        }
        return tan(first);
    }

    if (name == "ln") {
        requireOneArg(node, name);
        if (first <= 0) {
            throw EvaluatorException("ln requires a positive number.");
        }
        return log(first);
    }

    if (name == "log") {
        if (first <= 0) {
            throw EvaluatorException("log requires a positive number.");
        }

        if (!hasSecond) {
            return log10(first);
        }

        if (second <= 0 || abs(second - 1) < EPS) {
            throw EvaluatorException("log base is invalid.");
        }

        return log(first) / log(second);
    }

    if (name == "sqrt") {
        requireOneArg(node, name);
        if (first < 0) {
            throw EvaluatorException("sqrt requires a non-negative number.");
        }
        return sqrt(first);
    }

    if (name == "abs") {
        requireOneArg(node, name);
        return abs(first);
    }

    if (name == "exp") {
        requireOneArg(node, name);
        return exp(first);
    }

    if (name == "squa") {
        requireOneArg(node, name);
        return first * first;
    }

    if (name == "pow") {
        requireTwoArgs(node, name);
        double result = pow(first, second);
        if (!isfinite(result)) {
            throw EvaluatorException("pow result is invalid.");
        }
        return result;
    }

    if (name == "fact") {
        requireOneArg(node, name);
        return factorial(first);
    }

    throw EvaluatorException("Unknown function: " + name);
}

double Evaluator::factorial(double value) const {
    // 阶乘限制在 0 到 20 之间，避免 long long 溢出。
    double rounded = round(value);

    if (abs(value - rounded) > 0.000000001) {
        throw EvaluatorException("Factorial requires an integer.");
    }

    if (rounded < 0) {
        throw EvaluatorException("Factorial requires a non-negative integer.");
    }

    if (rounded > 20) {
        throw EvaluatorException("Factorial result is too large.");
    }

    long long result = 1;
    int number = static_cast<int>(rounded);

    for (int i = 2; i <= number; i++) {
        result *= i;
    }

    return static_cast<double>(result);
}

void Evaluator::requireOneArg(const ASTNode* node, const string& name) const {
    if (node->getLeft() == 0 || node->getRight() != 0) {
        throw EvaluatorException(name + " requires one argument.");
    }
}

void Evaluator::requireTwoArgs(const ASTNode* node, const string& name) const {
    if (node->getLeft() == 0 || node->getRight() == 0) {
        throw EvaluatorException(name + " requires two arguments.");
    }
}