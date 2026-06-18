#include "UnitPage.h"
#include <QtWidgets>
#include <stdexcept>

UnitWidget::UnitWidget(QWidget *parent) : QWidget(parent) {
	setupUI();
}

void UnitWidget::setupUI() {
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	
	// 类别选择
	QHBoxLayout *catLayout = new QHBoxLayout();
	catLayout->addWidget(new QLabel("类别:", this));
	categoryCombo = new QComboBox(this);
	categoryCombo->addItems({"长度", "温度", "角度"});
	connect(categoryCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
			this, &UnitWidget::onCategoryChanged);
	catLayout->addWidget(categoryCombo);
	mainLayout->addLayout(catLayout);
	
	// 转换行：数值 + 源单位 + 箭头 + 目标单位
	QHBoxLayout *convertLayout = new QHBoxLayout();
	inputEdit = new QLineEdit(this);
	inputEdit->setPlaceholderText("输入数值");
	convertLayout->addWidget(inputEdit);
	
	fromUnitCombo = new QComboBox(this);
	convertLayout->addWidget(fromUnitCombo);
	
	QLabel *arrowLabel = new QLabel("→", this);
	arrowLabel->setFont(QFont("Arial", 16));
	convertLayout->addWidget(arrowLabel);
	
	toUnitCombo = new QComboBox(this);
	convertLayout->addWidget(toUnitCombo);
	
	convertBtn = new QPushButton("转换", this);
	connect(convertBtn, &QPushButton::clicked, this, &UnitWidget::onConvertClicked);
	convertLayout->addWidget(convertBtn);
	
	mainLayout->addLayout(convertLayout);
	
	// 结果显示
	resultEdit = new QLineEdit(this);
	resultEdit->setReadOnly(true);
	resultEdit->setPlaceholderText("转换结果");
	mainLayout->addWidget(resultEdit);
	
	// 初始设置单位下拉框（默认长度）
	updateUnitCombos(0);
}

// 当类别改变时，更新单位下拉框
void UnitWidget::onCategoryChanged(int index) {
	updateUnitCombos(index);
}

void UnitWidget::updateUnitCombos(int categoryIndex) {
	fromUnitCombo->clear();
	toUnitCombo->clear();
	
	if (categoryIndex == LENGTH) {
		// 长度单位
		QStringList units = {"毫米", "厘米", "米", "千米"};
		fromUnitCombo->addItems(units);
		toUnitCombo->addItems(units);
		// 默认 米 -> 千米
		fromUnitCombo->setCurrentIndex(2); // 米
		toUnitCombo->setCurrentIndex(3);   // 千米
	} else if (categoryIndex == TEMPERATURE) {
		QStringList units = {"摄氏度", "华氏度", "开尔文"};
		fromUnitCombo->addItems(units);
		toUnitCombo->addItems(units);
		fromUnitCombo->setCurrentIndex(0); // 摄氏度
		toUnitCombo->setCurrentIndex(1);   // 华氏度
	} else if (categoryIndex == ANGLE) {
		QStringList units = {"度", "弧度"};
		fromUnitCombo->addItems(units);
		toUnitCombo->addItems(units);
		fromUnitCombo->setCurrentIndex(0); // 度
		toUnitCombo->setCurrentIndex(1);   // 弧度
	}
}

// 转换核心逻辑
double UnitWidget::convert(double value, int fromIdx, int toIdx, int categoryIdx) {
	if (categoryIdx == LENGTH) {
		// 将索引映射到 LengthUnit 枚举
		// 顺序：MILLIMETER, CENTIMETER, METER, KILOMETER
		UnitConverter::LengthUnit fromUnit;
		UnitConverter::LengthUnit toUnit;
		switch (fromIdx) {
			case 0: fromUnit = UnitConverter::MILLIMETER; break;
			case 1: fromUnit = UnitConverter::CENTIMETER; break;
			case 2: fromUnit = UnitConverter::METER; break;
			case 3: fromUnit = UnitConverter::KILOMETER; break;
		}
		switch (toIdx) {
			case 0: toUnit = UnitConverter::MILLIMETER; break;
			case 1: toUnit = UnitConverter::CENTIMETER; break;
			case 2: toUnit = UnitConverter::METER; break;
			case 3: toUnit = UnitConverter::KILOMETER; break;
		}
		return converter.convertLength(value, fromUnit, toUnit);
	} else if (categoryIdx == TEMPERATURE) {
		UnitConverter::TemperatureUnit fromUnit;
		UnitConverter::TemperatureUnit toUnit;
		switch (fromIdx) {
			case 0: fromUnit = UnitConverter::CELSIUS; break;
			case 1: fromUnit = UnitConverter::FAHRENHEIT; break;
			case 2: fromUnit = UnitConverter::KELVIN; break;
		}
		switch (toIdx) {
			case 0: toUnit = UnitConverter::CELSIUS; break;
			case 1: toUnit = UnitConverter::FAHRENHEIT; break;
			case 2: toUnit = UnitConverter::KELVIN; break;
		}
		return converter.convertTemperature(value, fromUnit, toUnit);
	} else if (categoryIdx == ANGLE) {
		if (fromIdx == 0 && toIdx == 1) return converter.degreeToRadian(value);
		else if (fromIdx == 1 && toIdx == 0) return converter.radianToDegree(value);
		else return value; // 相同单位
	}
	return 0.0;
}

void UnitWidget::onConvertClicked() {
	QString inputText = inputEdit->text().trimmed();
	if (inputText.isEmpty()) {
		QMessageBox::warning(this, "输入错误", "请输入数值");
		return;
	}
	bool ok;
	double value = inputText.toDouble(&ok);
	if (!ok) {
		QMessageBox::warning(this, "输入错误", "请输入有效的数字");
		return;
	}
	
	int categoryIdx = categoryCombo->currentIndex();
	int fromIdx = fromUnitCombo->currentIndex();
	int toIdx = toUnitCombo->currentIndex();
	
	try {
		double result = convert(value, fromIdx, toIdx, categoryIdx);
		resultEdit->setText(QString::number(result, 'f', 6));
	} catch (const std::exception &e) {
		QMessageBox::warning(this, "转换错误", e.what());
	}
}
