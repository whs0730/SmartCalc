#include "BasicCalcPage.h"

#include "core/Evaluator.h"

#include <QtWidgets>
#include <stdexcept>

BasicCalcWidget::BasicCalcWidget(QWidget *parent)
    : QWidget(parent), display(nullptr), isNewNumber(true) {
    setup();
}

void BasicCalcWidget::setup() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    display = new QLineEdit(this);
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setFont(QFont("Arial", 24));
    display->setText("0");
    mainLayout->addWidget(display);

    QHBoxLayout *funcRow = new QHBoxLayout();
    QStringList funcs = {"sin", "cos", "tan", "ln", "log", "sqrt", "x^2", "x^n", "n!"};
    for (const QString &text : funcs) {
        QPushButton *btn = new QPushButton(text, this);
        btn->setProperty("func", text);
        connect(btn, &QPushButton::clicked, this, &BasicCalcWidget::onScientificFunctionClicked);
        funcRow->addWidget(btn);
    }
    mainLayout->addLayout(funcRow);

    QGridLayout *grid = new QGridLayout();
    QStringList buttons = {
        "C", "DEL", "(", ")",
        "7", "8", "9", "*",
        "4", "5", "6", "-",
        "1", "2", "3", "+",
        "0", ".", "=", "/"};

    int row = 0;
    int col = 0;
    for (const QString &text : buttons) {
        QPushButton *btn = new QPushButton(text, this);
        btn->setMinimumHeight(50);
        btn->setFont(QFont("Arial", 16));

        if (text == "=") {
            btn->setStyleSheet("background-color: #4CAF50; color: white;");
            connect(btn, &QPushButton::clicked, this, &BasicCalcWidget::onEqualsClicked);
        }
        else if (text == "C") {
            connect(btn, &QPushButton::clicked, this, &BasicCalcWidget::onClearClicked);
        }
        else if (text == "DEL") {
            connect(btn, &QPushButton::clicked, this, &BasicCalcWidget::onBackspaceClicked);
        }
        else if (text == "+" || text == "-" || text == "*" || text == "/") {
            btn->setProperty("op", text);
            connect(btn, &QPushButton::clicked, this, &BasicCalcWidget::onOperatorClicked);
        }
        else {
            connect(btn, &QPushButton::clicked, this, &BasicCalcWidget::onDigitClicked);
        }

        grid->addWidget(btn, row, col);
        col++;
        if (col > 3) {
            col = 0;
            row++;
        }
    }

    mainLayout->addLayout(grid);
}

void BasicCalcWidget::setExpression(const QString &input) {
    expression = input;
    display->setText(expression.isEmpty() ? "0" : expression);
    isNewNumber = expression.isEmpty();
}

QString BasicCalcWidget::buildExpression() const {
    return expression.trimmed();
}

void BasicCalcWidget::onDigitClicked() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) {
        return;
    }

    QString text = btn->text();
    if (isNewNumber) {
        expression.clear();
        isNewNumber = false;
    }

    expression += text;
    display->setText(expression);
}

void BasicCalcWidget::onOperatorClicked() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) {
        return;
    }

    QString op = btn->property("op").toString();
    if (expression.isEmpty()) {
        if (op == "-") {
            expression = "-";
        }
        display->setText(expression.isEmpty() ? "0" : expression);
        return;
    }

    expression += op;
    display->setText(expression);
    isNewNumber = false;
}

void BasicCalcWidget::onEqualsClicked() {
    evaluateExpression();
}

void BasicCalcWidget::onClearClicked() {
    expression.clear();
    display->setText("0");
    isNewNumber = true;
}

void BasicCalcWidget::onBackspaceClicked() {
    if (!expression.isEmpty()) {
        expression.chop(1);
    }

    display->setText(expression.isEmpty() ? "0" : expression);
    isNewNumber = expression.isEmpty();
}

void BasicCalcWidget::onScientificFunctionClicked() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) {
        return;
    }

    QString func = btn->property("func").toString();
    if (isNewNumber) {
        expression.clear();
        isNewNumber = false;
    }

    if (func == "x^2") {
        expression += "^2";
    }
    else if (func == "x^n") {
        expression += "^";
    }
    else if (func == "n!") {
        expression += "!";
    }
    else {
        expression += func + "(";
    }

    display->setText(expression);
}

void BasicCalcWidget::evaluateExpression() {
    QString input = buildExpression();
    if (input.isEmpty()) {
        return;
    }

    try {
        Evaluator evaluator;
        double value = evaluator.evaluateExpression(input.toStdString());
        QString result = QString::number(value, 'g', 12);

        display->setText(result);
        expression = result;
        isNewNumber = true;
        emit historyRequested("Basic", input, result);
    }
    catch (const std::exception &e) {
        QMessageBox::warning(this, "Calculation error", e.what());
    }
}