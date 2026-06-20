#pragma once

#include <QWidget>
#include <QMap>
#include <QString>

#include "math/Matrix.h"
#include "math/MatrixSolver.h"

QT_BEGIN_NAMESPACE
class QTableWidget;
class QComboBox;
class QSpinBox;
class QPushButton;
class QTextEdit;
class QTabWidget;
QT_END_NAMESPACE

class MatrixWidget : public QWidget {
    Q_OBJECT
public:
    explicit MatrixWidget(QWidget *parent = nullptr);

signals:
    void historyRequested(const QString &type, const QString &input, const QString &result);

private slots:
    void onMatrixTabClosed(int index);
    void onCreateMatrixClicked();
    void onAddClicked();
    void onSubClicked();
    void onDotClicked();
    void onTransposeClicked();
    void onDeterminantClicked();
    void onInverseClicked();
    void onSolveClicked();

private:
    void setupUI();
    QTableWidget* getMatrixTable(const QString &name) const;
    Matrix getMatrixData(const QString &name) const;
    void setMatrixData(const QString &name, const Matrix &data);
    QString matrixToString(const Matrix &data) const;
    void showResult(const QString &result);
    void updateMatrixComboBoxes();

    QTabWidget *tabWidget;
    QMap<QString, QTableWidget*> matrixTables;

    QComboBox *matrixNameCombo;
    QComboBox *matrixACombo;
    QComboBox *matrixBCombo;
    QSpinBox *rowSpin;
    QSpinBox *colSpin;
    QTextEdit *resultDisplay;
};