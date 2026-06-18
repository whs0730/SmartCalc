#include"BasicCalcPage.h"
#include<QWidget>
#include <QtCharts>
#include <stdexcept>

BasicCalcWidget::BasicCalcWidget(QWidget *parent){
	setup();
}
void BasicCalcWidget::setup(){
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	
	// 显示框
	display = new QLineEdit(this);
	display->setReadOnly(true);
	display->setAlignment(Qt::AlignRight);
	display->setFont(QFont("Arial", 24));
	display->setText("0");
	mainLayout->addWidget(display);
	
	// 科学函数按钮行
	QHBoxLayout *funcRow = new QHBoxLayout();
	QStringList funcs = {"sin", "cos", "tan", "ln", "log", "√", "x²", "xⁿ", "n!"};
	for (const QString &text : funcs) {
		QPushButton *btn = new QPushButton(text, this);
		btn->setProperty("func", text);
		connect(btn, &QPushButton::clicked, this, &BasicCalcWidget::onScientificFunctionClicked);
		funcRow->addWidget(btn);
	}
	mainLayout->addLayout(funcRow);
	
	// 数字和运算符网格
	QGridLayout *grid = new QGridLayout();
	QStringList buttons = {
		"C", "DEL", "(", ")",
		"7", "8", "9", "×",
		"4", "5", "6", "-",
		"1", "2", "3", "+",
		"0", ".", "=","/"};
	int row = 0, col = 0;
	for (const QString &text : buttons) {
		QPushButton *btn = new QPushButton(text, this);
		btn->setMinimumHeight(50);
		btn->setFont(QFont("Arial", 16));
		if (text == "=") {
			btn->setStyleSheet("background-color: #4CAF50; color: white;");
			connect(btn, &QPushButton::clicked, this, &BasicCalcWidget::onEqualsClicked);
		} else if (text == "C") {
			connect(btn, &QPushButton::clicked, this, &BasicCalcWidget::onClearClicked);
		} else if (text == "DEL") {
			connect(btn, &QPushButton::clicked, this, &BasicCalcWidget::onBackspaceClicked);
		} else if (text == "+" || text == "-" || text == "×" || text == "/") {
            btn->setProperty("op", text);
            connect(btn, &QPushButton::clicked, this, &BasicCalcWidget::onOperatorClicked);
        } else {
            connect(btn, &QPushButton::clicked, this, &BasicCalcWidget::onDigitClicked);
        }
        grid->addWidget(btn, row, col);
        col++;
        if (col > 3) { col = 0; row++; }
    }
    mainLayout->addLayout(grid);
}
void BasicCalcWidget::onDigitClicked(){
	QPushButton *btn = qobject_cast<QPushButton*>(sender());
	if (!btn) return;
	QString text = btn->text();
	
	if (isNewNumber) {
		expression=text;
		isNewNumber = false;
	} else {
		expression+=text;
	}
	display->setText(expression);
}
void BasicCalcWidget::onOperatorClicked(){
	isNewNumber=false;
	QPushButton *btn = qobject_cast<QPushButton*>(sender());
	if (!btn) return;
	QString op = btn->property("op").toString();
	
	QString stdOp;
	if(op=="x")stdOp="*";
	else if(op=="/")stdOp="/";
	else stdOp=op;
	
	expression+=stdOp;
	display->setText(expression);
}
void BasicCalcWidget::onEqualsClicked(){
	evaluateExpression();
}
void BasicCalcWidget::onClearClicked(){
	expression.clear();
	display->setText("0");
	isNewNumber=true;
}
void BasicCalcWidget::onBackspaceClicked(){
	if(!expression.isEmpty()){
		expression.chop(1);
		display->setText(expression.isEmpty()?"0":expression);
	}
}

void BasicCalcWidget::onScientificFunctionClicked(){
	isNewNumber=false;
	QPushButton *btn = qobject_cast<QPushButton*>(sender());
	if (!btn) return;
	QString func = btn->property("func").toString();
	
	QString stdFunc;
	
	if (func == "sin") {stdFunc="sin";}
	else if (func == "cos") {stdFunc = "cos";}
	else if (func == "tan") {stdFunc = "tan";}
	else if (func == "ln") {stdFunc = "ln";}
	else if (func == "log") {stdFunc = "log";}
	else if (func == "√") {stdFunc="sqrt";}
	else if (func == "x²") {stdFunc="squa";}
	else if (func == "xⁿ") {stdFunc="pow";}
	else if (func == "n!") {stdFunc="fact";}
	else {return;}
	
	expression+= stdFunc+"(";
	display->setText(expression);
}

void BasicCalcWidget::evaluateExpression()
{
	try{
		double result=0.0;
		//TODO:实现计算，交给负责计算的同学
		//格式:result=calculate(expression.toStdString.c_str())
		
		display->setText(QString::number(result));
		expression=QString::number(result);
		isNewNumber = true;
	}
	catch(const std::exception &e){
		QMessageBox::warning(this, "wrong calcultion", e.what());
	}
}

