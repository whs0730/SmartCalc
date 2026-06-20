#pragma once

#include <QMainWindow>
#include <QSettings>
#include <QString>

#include "BasicCalcPage.h"
#include "MatrixPage.h"
#include "PlotPage.h"
#include "UnitPage.h"
#include "HistoryPage.h"
#include "SettingsDialog.h"
#include "storage/HistoryManager.h"

QT_BEGIN_NAMESPACE
class QTabWidget;
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:
    void onComplexFunctionClicked();
    void onSettingsClicked();
    void onHistoryDoubleClicked(const QString &input);
    void onHistoryRequested(const QString &type, const QString &input, const QString &result);
    void onHistoryCleared();

private:
    void setupUI();
    void setupMenuBar();
    void applySettings();
    void loadHistory();
    void saveHistory();
    QString historyFileName() const;

    QTabWidget *tabWidget;
    BasicCalcWidget *calculatorWidget;
    PlotWidget *plotWidget;
    MatrixWidget *matrixWidget;
    UnitWidget *unitWidget;
    HistoryWidget *historyWidget;
    SettingsDialog *settingsDialog;

    HistoryManager historyManager;
    QSettings settings;
};