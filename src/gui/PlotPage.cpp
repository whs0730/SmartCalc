#include "PlotPage.h"

#include "core/Evaluator.h"

#include <QtWidgets>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <cmath>
#include <stdexcept>

PlotWidget::PlotWidget(QWidget *parent) : QWidget(parent) {
    setup();
}

void PlotWidget::setup() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *controlLayout = new QHBoxLayout();
    functionInput = new QLineEdit(this);
    functionInput->setPlaceholderText("Input function, e.g. sin(x) or x^2+1");
    controlLayout->addWidget(functionInput);

    startSpin = new QDoubleSpinBox(this);
    startSpin->setRange(-1000, 1000);
    startSpin->setValue(-10);
    controlLayout->addWidget(new QLabel("Start:", this));
    controlLayout->addWidget(startSpin);

    endSpin = new QDoubleSpinBox(this);
    endSpin->setRange(-1000, 1000);
    endSpin->setValue(10);
    controlLayout->addWidget(new QLabel("End:", this));
    controlLayout->addWidget(endSpin);

    pointSpin = new QSpinBox(this);
    pointSpin->setRange(2, 10000);
    pointSpin->setValue(200);
    controlLayout->addWidget(new QLabel("Points:", this));
    controlLayout->addWidget(pointSpin);

    QPushButton *plotBtn = new QPushButton("Plot", this);
    connect(plotBtn, &QPushButton::clicked, this, &PlotWidget::onPlotClicked);
    controlLayout->addWidget(plotBtn);

    mainLayout->addLayout(controlLayout);

    chartView = new QChartView(this);
    chartView->setRenderHint(QPainter::Antialiasing);
    mainLayout->addWidget(chartView);
}

void PlotWidget::onPlotClicked() {
    QString funcExpr = functionInput->text().trimmed();
    if (funcExpr.isEmpty()) {
        QMessageBox::warning(this, "Input error", "Please input a function expression first.");
        return;
    }

    double start = startSpin->value();
    double end = endSpin->value();
    if (start >= end) {
        QMessageBox::warning(this, "Range error", "Start value must be less than end value.");
        return;
    }

    int points = pointSpin->value();
    QLineSeries *series = new QLineSeries();
    series->setName("y");

    Evaluator evaluator;
    QString lastError;
    int validCount = 0;
    double step = (end - start) / (points - 1);

    for (int i = 0; i < points; i++) {
        double x = start + step * i;

        try {
            double y = evaluator.evaluateExpression(funcExpr.toStdString(), x);
            if (std::isfinite(y)) {
                series->append(x, y);
                validCount++;
            }
        }
        catch (const std::exception &e) {
            lastError = e.what();
        }
    }

    if (validCount == 0) {
        delete series;
        QMessageBox::warning(
            this,
            "Plot error",
            lastError.isEmpty() ? "No valid sample points." : lastError
        );
        return;
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle(QString("y = %1").arg(funcExpr));

    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    emit historyRequested(
        "Plot",
        QString("y=%1, x=[%2,%3]").arg(funcExpr).arg(start).arg(end),
        QString("%1 valid points").arg(validCount)
    );
}