#include "SettingsDialog.h"
#include <QtWidgets>
#include <QSettings>

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent) {
	setWindowTitle("设置");
	QVBoxLayout *layout = new QVBoxLayout(this);
	
	// 小数位数
	QHBoxLayout *row1 = new QHBoxLayout();
	row1->addWidget(new QLabel("小数位数:"));
	decimalSpin = new QSpinBox(this);
	decimalSpin->setRange(0, 10);
	row1->addWidget(decimalSpin);
	layout->addLayout(row1);
	
	// 默认长度单位
	QHBoxLayout *row2 = new QHBoxLayout();
	row2->addWidget(new QLabel("默认长度单位:"));
	lengthUnitCombo = new QComboBox(this);
	lengthUnitCombo->addItems({"毫米", "厘米", "米", "千米"});
	row2->addWidget(lengthUnitCombo);
	layout->addLayout(row2);
	
	// 自动保存历史
	autoSaveCheck = new QCheckBox("自动保存历史记录", this);
	layout->addWidget(autoSaveCheck);
	
	// 按钮
	QHBoxLayout *btnLayout = new QHBoxLayout();
	QPushButton *okBtn = new QPushButton("确定", this);
	QPushButton *cancelBtn = new QPushButton("取消", this);
	connect(okBtn, &QPushButton::clicked, this, &SettingsDialog::onOkClicked);
	connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
	btnLayout->addWidget(okBtn);
	btnLayout->addWidget(cancelBtn);
	layout->addLayout(btnLayout);
	
	loadSettings();
}

void SettingsDialog::loadSettings() {
	QSettings settings("MyCompany", "Calculator");
	decimalSpin->setValue(settings.value("decimalPlaces", 6).toInt());
	lengthUnitCombo->setCurrentIndex(settings.value("defaultLengthUnit", 2).toInt()); // 默认米
	autoSaveCheck->setChecked(settings.value("autoSaveHistory", true).toBool());
}

void SettingsDialog::saveSettings() {
	QSettings settings("MyCompany", "Calculator");
	settings.setValue("decimalPlaces", decimalSpin->value());
	settings.setValue("defaultLengthUnit", lengthUnitCombo->currentIndex());
	settings.setValue("autoSaveHistory", autoSaveCheck->isChecked());
}

void SettingsDialog::onOkClicked() {
	saveSettings();
	accept();
}

int SettingsDialog::decimalPlaces() const { return decimalSpin->value(); }
QString SettingsDialog::defaultLengthUnit() const { return lengthUnitCombo->currentText(); }
bool SettingsDialog::autoSaveHistory() const { return autoSaveCheck->isChecked(); }
