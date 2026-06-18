#pragma once
#include <QDialog>
#include <QSettings>

QT_BEGIN_NAMESPACE
class QSpinBox;
class QComboBox;
class QCheckBox;
QT_END_NAMESPACE

class SettingsDialog : public QDialog {
	Q_OBJECT
public:
	explicit SettingsDialog(QWidget *parent = nullptr);
	
	int decimalPlaces() const;
	QString defaultLengthUnit() const;
	bool autoSaveHistory() const;
	
	private slots:
	void onOkClicked();
	
private:
	void loadSettings();
	void saveSettings();
	
	QSpinBox *decimalSpin;
	QComboBox *lengthUnitCombo;
	QCheckBox *autoSaveCheck;
};
