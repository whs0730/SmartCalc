#include "HistoryPage.h"
#include <QtWidgets>
#include <QVBoxLayout>

HistoryWidget::HistoryWidget(QWidget *parent) : QWidget(parent) {
	setupUI();
}

void HistoryWidget::setupUI() {
	QVBoxLayout *layout = new QVBoxLayout(this);
	
	table = new QTableWidget(this);
	table->setColumnCount(4);
	table->setHorizontalHeaderLabels({"时间", "类型", "输入", "结果"});
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->setSelectionBehavior(QAbstractItemView::SelectRows);
	connect(table, &QTableWidget::cellDoubleClicked, this, &HistoryWidget::onCellDoubleClicked);
	layout->addWidget(table);
	
	clearBtn = new QPushButton("清空历史", this);
	connect(clearBtn, &QPushButton::clicked, this, &HistoryWidget::onClearClicked);
	layout->addWidget(clearBtn);
}

void HistoryWidget::addHistory(const HistoryItem &item) {
	items.prepend(item); // 最新在上
	refreshTable();
}

void HistoryWidget::clearHistory() {
	items.clear();
	refreshTable();
}

void HistoryWidget::refreshTable() {
	table->setRowCount((int)items.size());
	for (int i = 0; i < items.size(); ++i) {
		const HistoryItem &item = items[i];
		table->setItem(i, 0, new QTableWidgetItem(item.timestamp.toString("yyyy-MM-dd hh:mm:ss")));
		table->setItem(i, 1, new QTableWidgetItem(item.type));
		table->setItem(i, 2, new QTableWidgetItem(item.input));
		table->setItem(i, 3, new QTableWidgetItem(item.result));
	}
}

void HistoryWidget::onClearClicked() {
	if (QMessageBox::question(this, "确认", "确定清空所有历史记录吗？") == QMessageBox::Yes) {
		clearHistory();
		emit historyCleared();
	}
}

void HistoryWidget::onCellDoubleClicked(int row, int column) {
	if (row < 0 || row >= items.size()) return;
	QString input = items[row].input;
	emit historyItemDoubleClicked(input);
}
