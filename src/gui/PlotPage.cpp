#include "PlotPage.h"
#include "math/FunctionSampler.h"
#include <QtWidgets>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QMessageBox>
#include <cmath>

PlotWidget::PlotWidget(QWidget *parent) : QWidget(parent) {
	setup();
}

void PlotWidget::setup() {
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	
	// 控制栏
	QHBoxLayout *controlLayout = new QHBoxLayout();
	functionInput = new QLineEdit(this);
	functionInput->setPlaceholderText("输入函数，如 sin(x)");
	controlLayout->addWidget(functionInput);
	
	startSpin = new QDoubleSpinBox(this);
	startSpin->setRange(-1000, 1000);
	startSpin->setValue(-10);
	controlLayout->addWidget(new QLabel("起始:", this));
	controlLayout->addWidget(startSpin);
	
	endSpin = new QDoubleSpinBox(this);
	endSpin->setRange(-1000, 1000);
	endSpin->setValue(10);
	controlLayout->addWidget(new QLabel("结束:", this));
	controlLayout->addWidget(endSpin);
	
	pointSpin = new QSpinBox(this);
	pointSpin->setRange(2, 10000);
	pointSpin->setValue(200);
	controlLayout->addWidget(new QLabel("点数:", this));
	controlLayout->addWidget(pointSpin);
	
	QPushButton *plotBtn = new QPushButton("绘制", this);
	connect(plotBtn, &QPushButton::clicked, this, &PlotWidget::onPlotClicked);
	controlLayout->addWidget(plotBtn);
	
	mainLayout->addLayout(controlLayout);
	
	// 图表
	chartView = new QChartView(this);
	chartView->setRenderHint(QPainter::Antialiasing);
	mainLayout->addWidget(chartView);
}

void PlotWidget::onPlotClicked() {
	QString funcExpr = functionInput->text().trimmed();
	if (funcExpr.isEmpty()) {
		QMessageBox::warning(this, "输入错误", "请先输入函数表达式");
		return;
	}
	
	double start = startSpin->value();
	double end = endSpin->value();
	if (start >= end) {
		QMessageBox::warning(this, "区间错误", "起始值必须小于结束值");
		return;
	}
	int points = pointSpin->value();
	
	try {
		// 调用后端接口（假设后端提供 sampleFunction）
		// 此处先使用占位实现，待后端接口确定后替换
		// 临时方案：仅支持 sin(x), cos(x), tan(x) 演示
		double (*func)(double);
		if (funcExpr == "sin(x)") {
			func = [](double x) { return std::sin(x); };
		} else if (funcExpr == "cos(x)") {
			func = [](double x) { return std::cos(x); };
		} else if (funcExpr == "tan(x)") {
			func = [](double x) { return std::tan(x); };
		} else {
			// 默认使用 sin(x)
			func = [](double x) { return std::sin(x); };
			QMessageBox::information(this, "提示",
									 "当前演示版本仅支持 sin(x), cos(x), tan(x)，已使用 sin(x) 代替");
		}
		
		FunctionSampler sampler;
		auto samples = sampler.sample(start, end, points, func);
		
		
		QLineSeries *series = new QLineSeries();
		for (const auto &p : samples) {
			series->append(p.x, p.y);
		}
		
		QChart *chart = new QChart();
		chart->addSeries(series);
		chart->createDefaultAxes();
		chart->setTitle(QString("y = %1").arg(funcExpr));
		
		chartView->setChart(chart);
		chartView->setRenderHint(QPainter::Antialiasing);
		
	} catch (const std::exception &e) {
		QMessageBox::warning(this, "绘图错误", e.what());
	}
}
