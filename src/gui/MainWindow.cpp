#include "MainWindow.h"

#include <QtWidgets>
#include <QCoreApplication>
#include <QDir>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      tabWidget(nullptr),
      calculatorWidget(nullptr),
      plotWidget(nullptr),
      matrixWidget(nullptr),
      unitWidget(nullptr),
      historyWidget(nullptr),
      settingsDialog(nullptr) {
    setupUI();
    setupMenuBar();
    loadHistory();
    applySettings();
}


void MainWindow::setupUI() {
    setWindowTitle("SmartCalc");
    resize(1000, 700);

    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);

    calculatorWidget = new BasicCalcWidget(this);
    matrixWidget = new MatrixWidget(this);
    plotWidget = new PlotWidget(this);
    unitWidget = new UnitWidget(this);
    historyWidget = new HistoryWidget(this);

    tabWidget->addTab(calculatorWidget, "BasicCalc");
    tabWidget->addTab(matrixWidget, "Matrix");
    tabWidget->addTab(plotWidget, "Plot");
    tabWidget->addTab(unitWidget, "Unit");
    tabWidget->addTab(historyWidget, "History");

    connect(calculatorWidget, &BasicCalcWidget::historyRequested,
            this, &MainWindow::onHistoryRequested);
    connect(matrixWidget, &MatrixWidget::historyRequested,
            this, &MainWindow::onHistoryRequested);
    connect(plotWidget, &PlotWidget::historyRequested,
            this, &MainWindow::onHistoryRequested);
    connect(unitWidget, &UnitWidget::historyRequested,
            this, &MainWindow::onHistoryRequested);
    connect(historyWidget, &HistoryWidget::historyItemDoubleClicked,
            this, &MainWindow::onHistoryDoubleClicked);
    connect(historyWidget, &HistoryWidget::historyCleared,
            this, &MainWindow::onHistoryCleared);

    statusBar()->showMessage("Ready");
}

void MainWindow::setupMenuBar() {
    QMenu *fileMenu = menuBar()->addMenu("File");

    QAction *settingsAction = new QAction("Settings", this);
    connect(settingsAction, &QAction::triggered, this, &MainWindow::onSettingsClicked);
    fileMenu->addAction(settingsAction);

    QAction *exitAction = new QAction("Exit", this);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    fileMenu->addAction(exitAction);

    QMenu *helpMenu = menuBar()->addMenu("Help");
    QAction *aboutAction = new QAction("About", this);
    connect(aboutAction, &QAction::triggered, this, [this]() {
        QMessageBox::about(this, "About", "SmartCalc v1.0\nBuilt with CMake and Qt Widgets.");
    });
    helpMenu->addAction(aboutAction);
}

void MainWindow::onSettingsClicked() {
    SettingsDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        applySettings();
    }
}

void MainWindow::applySettings() {
    int decimals = settings.value("decimalPlaces", 6).toInt();
    statusBar()->showMessage(QString("Precision: %1").arg(decimals), 2000);
}

void MainWindow::onHistoryDoubleClicked(const QString &input) {
    calculatorWidget->setExpression(input);
    tabWidget->setCurrentWidget(calculatorWidget);
    statusBar()->showMessage("History expression loaded", 2000);
}

void MainWindow::onHistoryRequested(const QString &type, const QString &input, const QString &result) {
    HistoryItem item;
    item.timestamp = QDateTime::currentDateTime();
    item.type = type;
    item.input = input;
    item.result = result;
    historyWidget->addHistory(item);

    historyManager.addRecord(input.toStdString(), result.toStdString());
    saveHistory();
}

void MainWindow::onHistoryCleared() {
    historyManager.clearHistory();
    saveHistory();
}

QString MainWindow::historyFileName() const {
    QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    if (dir.isEmpty()) {
        dir = QCoreApplication::applicationDirPath();
    }

    QDir().mkpath(dir);
    return dir + "/history.txt";
}

void MainWindow::loadHistory() {
    historyManager.loadFromFile(historyFileName().toStdString());
    std::vector<HistoryRecord> records = historyManager.getRecords();

    for (int i = 0; i < static_cast<int>(records.size()); i++) {
        const HistoryRecord &record = records[i];
        HistoryItem item;
        item.timestamp = QDateTime::fromString(
            QString::fromStdString(record.getTimestamp()),
            "yyyy-MM-dd hh:mm:ss"
        );
        if (!item.timestamp.isValid()) {
            item.timestamp = QDateTime::currentDateTime();
        }
        item.type = "Saved";
        item.input = QString::fromStdString(record.getExpression());
        item.result = QString::fromStdString(record.getResult());
        historyWidget->addHistory(item);
    }
}

void MainWindow::saveHistory() {
    historyManager.saveToFile(historyFileName().toStdString());
}

void MainWindow::onComplexFunctionClicked() {
    QMessageBox::information(this, "Complex", "Complex calculation can be added on this page later.");
}