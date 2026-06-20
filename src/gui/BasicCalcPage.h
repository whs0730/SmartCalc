#pragma once

#include <QWidget>
#include <QString>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

class BasicCalcWidget : public QWidget {
    Q_OBJECT
public:
    explicit BasicCalcWidget(QWidget *parent = nullptr);
    void setExpression(const QString &input);

signals:
    void historyRequested(const QString &type, const QString &input, const QString &result);

private slots:
    void onDigitClicked();
    void onOperatorClicked();
    void onEqualsClicked();
    void onClearClicked();
    void onBackspaceClicked();
    void onScientificFunctionClicked();

private:
    void setup();
    QString buildExpression() const;
    void evaluateExpression();

    QLineEdit *display;
    QString expression;
    bool isNewNumber;
};