#pragma once
#include <QWidget>
#include "math/UnitConverter.h"

QT_BEGIN_NAMESPACE
class QComboBox;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

class UnitWidget : public QWidget {
	Q_OBJECT
public:
	explicit UnitWidget(QWidget *parent = nullptr);

signals:
	void historyRequested(const QString &type, const QString &input, const QString &result);
	
	private slots:
	void onCategoryChanged(int index);
	void onConvertClicked();
	
private:
	void setupUI();
	void updateUnitCombos(int categoryIndex);
	double convert(double value, int fromIdx, int toIdx, int categoryIdx);
	
	UnitConverter converter;
	
	QComboBox *categoryCombo;
	QComboBox *fromUnitCombo;
	QComboBox *toUnitCombo;
	QLineEdit *inputEdit;
	QLineEdit *resultEdit;
	QPushButton *convertBtn;
	
	// 类别枚举
	enum Category { LENGTH, TEMPERATURE, ANGLE };
};
