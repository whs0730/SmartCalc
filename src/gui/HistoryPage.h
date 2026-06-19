#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QList>
#include <QDateTime>

struct HistoryItem {
	QDateTime timestamp;
	QString type;
	QString input;
	QString result;
};

class HistoryWidget : public QWidget {
	Q_OBJECT
public:
	explicit HistoryWidget(QWidget *parent = nullptr);
	
	void addHistory(const HistoryItem &item);
	void clearHistory();
	
signals:
	void historyItemDoubleClicked(const QString &input); // 点击时发送信号
	
	private slots:
	void onClearClicked();
	void onCellDoubleClicked(int row, int column);
	
private:
	void setupUI();
	void refreshTable();
	
	QTableWidget *table;
	QPushButton *clearBtn;
	QList<HistoryItem> items;
};
