#pragma once

#include <QWidget>
#include <QtCharts/QChartView>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QDoubleSpinBox;
class QSpinBox;
class QPushButton;
QT_END_NAMESPACE

class PlotWidget : public QWidget {
    Q_OBJECT
public:
    explicit PlotWidget(QWidget *parent = nullptr);

signals:
    void historyRequested(const QString &type, const QString &input, const QString &result);

private slots:
    void onPlotClicked();

private:
    void setup();

    QLineEdit *functionInput;
    QDoubleSpinBox *startSpin;
    QDoubleSpinBox *endSpin;
    QSpinBox *pointSpin;
    QChartView *chartView;
};