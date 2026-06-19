#pragma once
#include<QMainWindow>
#include<QStack>
#include<QString>

#include"BasicCalcPage.h"
#include"MatrixPage.h"
#include"PlotPage.h"
#include"UnitPage.h"

#include "math/ComplexNumber.h"
#include "math/Matrix.h"
#include "math/MatrixSolver.h"
#include "HistoryPage.h"
#include "SettingsDialog.h"

QT_BEGIN_NAMESPACE
class QChartView;
QT_END_NAMESPACE

class MainWindow:public QMainWindow{
	Q_OBJECT
public:
	MainWindow(QWidget *parent=nullptr);
	~MainWindow()=default;
	
	
private slots:
	
	
	// 复数相关（构建、实部、虚部、共轭、模）
	void onComplexFunctionClicked();
	
	void onSettingsClicked();
	void onHistoryDoubleClicked(const QString &input);
	void onHistoryRequested(const QString &type, const QString &input, const QString &result);

private:
	void setupUI();

	void setupMenuBar();
	void applySettings();
	
	BasicCalcWidget *calculatorWidget;
	PlotWidget *plotWidget;
	MatrixWidget *matrixWidget;
	UnitWidget *unitWidget;
	HistoryWidget *historyWidget;
	SettingsDialog *settingsDialog;
	
	QSettings settings;
};

