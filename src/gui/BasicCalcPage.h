#pragma once
#include"math/ScientificFunction.h"
#include "math/UnitConverter.h"

#include<QStack>
#include<QWidget>
QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE


class BasicCalcWidget:public QWidget{
	Q_OBJECT
public:
	explicit BasicCalcWidget(QWidget *parent = nullptr);
	private slots:
	// 数字和小数点
	void onDigitClicked();
	// 运算符 (+ - × ÷)
	void onOperatorClicked();
	// 等号
	void onEqualsClicked();
	// 清除 (C/CE)
	void onClearClicked();
	// 退格
	void onBackspaceClicked();
	
	// 科学函数 (sin, cos, tan, ln, log, sqrt, x², xⁿ, !)
	void onScientificFunctionClicked();
private:
	void setup();
	QString buildExpression() const;
	void evaluateExpression();
	
	QLineEdit* display;
	QString expression;
	bool isNewNumber;
	
};
