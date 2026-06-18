#include"MainWindow.h"

#include <QtWidgets>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <cmath>
#include <stdexcept>

MainWindow::MainWindow(QWidget* parent)
	:QMainWindow(parent)
{
	setupUI();
	setupMenuBar();
	applySettings();
	
	connect(historyWidget, &HistoryWidget::historyItemDoubleClicked, this, &MainWindow::onHistoryDoubleClicked);
}

void MainWindow::setupUI(){
	setWindowTitle("SmartClac");
	resize(1000,700);
	
	// 主窗口部件
	QTabWidget* tabWidget = new QTabWidget(this);
	setCentralWidget(tabWidget);
	
	calculatorWidget = new BasicCalcWidget(this);
	plotWidget = new PlotWidget(this);
	matrixWidget = new MatrixWidget(this);
	unitWidget = new UnitWidget(this);
	historyWidget = new HistoryWidget(this);
	
	tabWidget->addTab(calculatorWidget, "BasicCalc");
	tabWidget->addTab(matrixWidget, "Matrix");
	tabWidget->addTab(plotWidget, "Plot");
	tabWidget->addTab(unitWidget, "Unit");
	tabWidget->addTab(historyWidget, "History");
	
	connect(historyWidget, &HistoryWidget::historyItemDoubleClicked,
			this, &MainWindow::onHistoryDoubleClicked);
	
	//TODO:Connect history sgnals
	
	// 状态栏
	statusBar()->showMessage("就绪");
}
void MainWindow::setupMenuBar()
{
	QMenu *fileMenu = menuBar()->addMenu("文件");
	QAction *settingsAction = new QAction("设置", this);
	connect(settingsAction, &QAction::triggered, this, &MainWindow::onSettingsClicked);
	fileMenu->addAction(settingsAction);
	
	QAction *exitAction = new QAction("退出", this);
	connect(exitAction, &QAction::triggered, this, &QWidget::close);
	fileMenu->addAction(exitAction);
	
	QMenu *helpMenu = menuBar()->addMenu("帮助");
	QAction *aboutAction = new QAction("关于", this);
	connect(aboutAction, &QAction::triggered, this, [this]() {
		QMessageBox::about(this, "关于", "多功能科学计算器 v1.0\n基于 Qt 和 CMake 构建。");
	});
	helpMenu->addAction(aboutAction);
}
void MainWindow::onSettingsClicked()
{
	SettingsDialog dialog(this);
	if (dialog.exec() == QDialog::Accepted) {
		applySettings();
	}
}
void MainWindow::applySettings()
{
	// 读取设置并应用到各模块（例如小数位数）
	int decimals = settings.value("decimalPlaces", 6).toInt();
	// 这里可以通过信号或直接调用各模块的方法来更新显示格式
	// 例如：calculatorWidget->setDecima
	// 由负责历史记录部分的同学完善
}

// 处理历史记录双击：将输入复制到计算器（或当前活动模块）
void MainWindow::onHistoryDoubleClicked(const QString &input)
{
	// 简单演示：将输入设置到计算器的显示栏
	// 可以通过信号或直接调用方法
	// calculatorWidget->setExpression(input);
	QMessageBox::information(this, "历史记录", "双击内容: " + input);
}
// 接收各模块的历史记录请求，统一添加到历史记录组件
void MainWindow::onHistoryRequested(const QString &type, const QString &input, const QString &result)
{
	HistoryItem item;
	item.timestamp = QDateTime::currentDateTime();
	item.type = type;
	item.input = input;
	item.result = result;
	historyWidget->addHistory(item);
}

void MainWindow::onComplexFunctionClicked(){
	QMessageBox::information(this, "复数", "复数运算将在后续实现");
}


