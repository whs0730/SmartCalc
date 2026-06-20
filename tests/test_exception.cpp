#include "core/CalcException.h"
#include "core/Evaluator.h"

#include <cassert>
#include <iostream>

void assertThrows(const std::string& expression) {
    Evaluator evaluator;
    bool hasError = false;

    try {
        evaluator.evaluateExpression(expression);
    }
    catch (const CalcException&) {
        hasError = true;
    }

    assert(hasError);
}

void testLexerAndParserErrors() {
    assertThrows("1 + @");
    assertThrows("(1 + 2");
    assertThrows("1 + * 2");
}

void testEvaluatorErrors() {
    assertThrows("1/0");
    assertThrows("sqrt(-1)");
    assertThrows("ln(0)");
    assertThrows("2.5!");
    assertThrows("unknown(1)");
    assertThrows("x+1");
}

int main() {
    testLexerAndParserErrors();
    testEvaluatorErrors();

    std::cout << "Exception tests passed!" << std::endl;
    return 0;
}