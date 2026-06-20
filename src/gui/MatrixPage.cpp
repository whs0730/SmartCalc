#include "MatrixPage.h"

#include <QtWidgets>
#include <stdexcept>
#include <vector>

MatrixWidget::MatrixWidget(QWidget *parent) : QWidget(parent) {
    setupUI();
}

void MatrixWidget::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QGroupBox *createGroup = new QGroupBox("Create Matrix", this);
    QHBoxLayout *createLayout = new QHBoxLayout(createGroup);

    matrixNameCombo = new QComboBox(this);
    for (char c = 'A'; c <= 'Z'; ++c) {
        matrixNameCombo->addItem(QString(c));
    }
    matrixNameCombo->addItem("Re");
    createLayout->addWidget(new QLabel("Name:", this));
    createLayout->addWidget(matrixNameCombo);

    rowSpin = new QSpinBox(this);
    rowSpin->setRange(1, 6);
    rowSpin->setValue(2);
    colSpin = new QSpinBox(this);
    colSpin->setRange(1, 6);
    colSpin->setValue(2);
    createLayout->addWidget(new QLabel("Row:", this));
    createLayout->addWidget(rowSpin);
    createLayout->addWidget(new QLabel("Col:", this));
    createLayout->addWidget(colSpin);

    QPushButton *createBtn = new QPushButton("Create", this);
    connect(createBtn, &QPushButton::clicked, this, &MatrixWidget::onCreateMatrixClicked);
    createLayout->addWidget(createBtn);

    mainLayout->addWidget(createGroup);

    tabWidget = new QTabWidget(this);
    tabWidget->setTabsClosable(true);
    tabWidget->setMinimumHeight(200);
    connect(tabWidget, &QTabWidget::tabCloseRequested, this, &MatrixWidget::onMatrixTabClosed);
    mainLayout->addWidget(tabWidget);

    QGroupBox *opGroup = new QGroupBox("Matrix Calculation", this);
    QGridLayout *opLayout = new QGridLayout(opGroup);

    matrixACombo = new QComboBox(this);
    matrixBCombo = new QComboBox(this);

    opLayout->addWidget(new QLabel("Mat A:", this), 0, 0);
    opLayout->addWidget(matrixACombo, 0, 1);
    opLayout->addWidget(new QLabel("Mat B:", this), 0, 2);
    opLayout->addWidget(matrixBCombo, 0, 3);

    QPushButton *addBtn = new QPushButton("add", this);
    QPushButton *subBtn = new QPushButton("sub", this);
    QPushButton *dotBtn = new QPushButton("dot", this);
    QPushButton *transBtn = new QPushButton("trans", this);
    QPushButton *detBtn = new QPushButton("det", this);
    QPushButton *invBtn = new QPushButton("inverse", this);
    QPushButton *solveBtn = new QPushButton("solve", this);

    connect(addBtn, &QPushButton::clicked, this, &MatrixWidget::onAddClicked);
    connect(subBtn, &QPushButton::clicked, this, &MatrixWidget::onSubClicked);
    connect(dotBtn, &QPushButton::clicked, this, &MatrixWidget::onDotClicked);
    connect(transBtn, &QPushButton::clicked, this, &MatrixWidget::onTransposeClicked);
    connect(detBtn, &QPushButton::clicked, this, &MatrixWidget::onDeterminantClicked);
    connect(invBtn, &QPushButton::clicked, this, &MatrixWidget::onInverseClicked);
    connect(solveBtn, &QPushButton::clicked, this, &MatrixWidget::onSolveClicked);

    opLayout->addWidget(addBtn, 1, 0);
    opLayout->addWidget(subBtn, 1, 1);
    opLayout->addWidget(dotBtn, 1, 2);
    opLayout->addWidget(transBtn, 1, 3);
    opLayout->addWidget(detBtn, 2, 0);
    opLayout->addWidget(invBtn, 2, 1);
    opLayout->addWidget(solveBtn, 2, 2);

    mainLayout->addWidget(opGroup);

    resultDisplay = new QTextEdit(this);
    resultDisplay->setReadOnly(true);
    mainLayout->addWidget(resultDisplay);

    updateMatrixComboBoxes();
}

QTableWidget* MatrixWidget::getMatrixTable(const QString &name) const {
    return matrixTables.value(name, nullptr);
}

Matrix MatrixWidget::getMatrixData(const QString &name) const {
    QTableWidget *table = getMatrixTable(name);
    if (!table) {
        throw std::invalid_argument("Please create the selected matrix first.");
    }

    int row = table->rowCount();
    int col = table->columnCount();
    Matrix data(row, col);

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            QTableWidgetItem *item = table->item(i, j);
            if (!item) {
                data.set(i, j, 0.0);
                continue;
            }

            bool ok = false;
            double value = item->text().toDouble(&ok);
            if (!ok) {
                throw std::invalid_argument("Matrix cell must be a number.");
            }
            data.set(i, j, value);
        }
    }

    return data;
}

void MatrixWidget::setMatrixData(const QString &name, const Matrix &data) {
    QTableWidget *table = matrixTables.value(name, nullptr);

    if (!table) {
        table = new QTableWidget(data.getRow(), data.getCol(), this);
        int index = tabWidget->addTab(table, name);
        matrixTables[name] = table;
        tabWidget->setCurrentIndex(index);
    }
    else {
        table->setRowCount(data.getRow());
        table->setColumnCount(data.getCol());
    }

    for (int i = 0; i < data.getRow(); ++i) {
        for (int j = 0; j < data.getCol(); ++j) {
            table->setItem(i, j, new QTableWidgetItem(QString::number(data.get(i, j), 'g', 10)));
        }
    }

    int index = tabWidget->indexOf(table);
    if (index != -1) {
        tabWidget->setCurrentIndex(index);
    }

    updateMatrixComboBoxes();
}

QString MatrixWidget::matrixToString(const Matrix &data) const {
    QStringList rows;

    for (int i = 0; i < data.getRow(); ++i) {
        QStringList cols;
        for (int j = 0; j < data.getCol(); ++j) {
            cols << QString::number(data.get(i, j), 'g', 10);
        }
        rows << cols.join(" ");
    }

    return rows.join("; ");
}

void MatrixWidget::onCreateMatrixClicked() {
    QString name = matrixNameCombo->currentText();
    int r = rowSpin->value();
    int c = colSpin->value();

    if (matrixTables.contains(name)) {
        QTableWidget *old = matrixTables[name];
        int index = tabWidget->indexOf(old);
        if (index != -1) {
            tabWidget->removeTab(index);
        }
        delete old;
        matrixTables.remove(name);
    }

    QTableWidget *table = new QTableWidget(r, c, this);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            table->setItem(i, j, new QTableWidgetItem("0"));
        }
    }

    int index = tabWidget->addTab(table, name);
    matrixTables[name] = table;
    tabWidget->setCurrentIndex(index);

    updateMatrixComboBoxes();
}

void MatrixWidget::onMatrixTabClosed(int index) {
    QWidget *widget = tabWidget->widget(index);
    QTableWidget *table = qobject_cast<QTableWidget*>(widget);
    if (!table) {
        return;
    }

    QString name = tabWidget->tabText(index);
    matrixTables.remove(name);
    tabWidget->removeTab(index);
    delete table;
    updateMatrixComboBoxes();
}

void MatrixWidget::updateMatrixComboBoxes() {
    QString currentA = matrixACombo->currentText();
    QString currentB = matrixBCombo->currentText();
    QStringList names = matrixTables.keys();

    matrixACombo->clear();
    matrixBCombo->clear();
    matrixACombo->addItems(names);
    matrixBCombo->addItems(names);

    int indexA = matrixACombo->findText(currentA);
    if (indexA >= 0) {
        matrixACombo->setCurrentIndex(indexA);
    }

    int indexB = matrixBCombo->findText(currentB);
    if (indexB >= 0) {
        matrixBCombo->setCurrentIndex(indexB);
    }
    else if (names.size() >= 2) {
        matrixBCombo->setCurrentIndex(1);
    }
}

void MatrixWidget::showResult(const QString &result) {
    resultDisplay->append(result);
}

void MatrixWidget::onAddClicked() {
    QString nameA = matrixACombo->currentText();
    QString nameB = matrixBCombo->currentText();

    try {
        Matrix result = getMatrixData(nameA).add(getMatrixData(nameB));
        setMatrixData("Re", result);
        QString resultText = matrixToString(result);
        showResult(QString("%1 + %2 -> Re: %3").arg(nameA, nameB, resultText));
        emit historyRequested("Matrix", nameA + " + " + nameB, resultText);
    }
    catch (const std::exception &e) {
        showResult(QString("Error: ") + e.what());
    }
}

void MatrixWidget::onSubClicked() {
    QString nameA = matrixACombo->currentText();
    QString nameB = matrixBCombo->currentText();

    try {
        Matrix result = getMatrixData(nameA).sub(getMatrixData(nameB));
        setMatrixData("Re", result);
        QString resultText = matrixToString(result);
        showResult(QString("%1 - %2 -> Re: %3").arg(nameA, nameB, resultText));
        emit historyRequested("Matrix", nameA + " - " + nameB, resultText);
    }
    catch (const std::exception &e) {
        showResult(QString("Error: ") + e.what());
    }
}

void MatrixWidget::onDotClicked() {
    QString nameA = matrixACombo->currentText();
    QString nameB = matrixBCombo->currentText();

    try {
        Matrix result = getMatrixData(nameA).dot(getMatrixData(nameB));
        setMatrixData("Re", result);
        QString resultText = matrixToString(result);
        showResult(QString("%1 * %2 -> Re: %3").arg(nameA, nameB, resultText));
        emit historyRequested("Matrix", nameA + " * " + nameB, resultText);
    }
    catch (const std::exception &e) {
        showResult(QString("Error: ") + e.what());
    }
}

void MatrixWidget::onTransposeClicked() {
    QString nameA = matrixACombo->currentText();

    try {
        Matrix result = getMatrixData(nameA).transpose();
        setMatrixData("Re", result);
        QString resultText = matrixToString(result);
        showResult(QString("trans(%1) -> Re: %2").arg(nameA, resultText));
        emit historyRequested("Matrix", "trans(" + nameA + ")", resultText);
    }
    catch (const std::exception &e) {
        showResult(QString("Error: ") + e.what());
    }
}

void MatrixWidget::onDeterminantClicked() {
    QString nameA = matrixACombo->currentText();

    try {
        MatrixSolver solver;
        double value = solver.determinant(getMatrixData(nameA));
        QString resultText = QString::number(value, 'g', 10);
        showResult(QString("det(%1) = %2").arg(nameA, resultText));
        emit historyRequested("Matrix", "det(" + nameA + ")", resultText);
    }
    catch (const std::exception &e) {
        showResult(QString("Error: ") + e.what());
    }
}

void MatrixWidget::onInverseClicked() {
    QString nameA = matrixACombo->currentText();

    try {
        MatrixSolver solver;
        Matrix result = solver.inverse(getMatrixData(nameA));
        setMatrixData("Re", result);
        QString resultText = matrixToString(result);
        showResult(QString("inverse(%1) -> Re: %2").arg(nameA, resultText));
        emit historyRequested("Matrix", "inverse(" + nameA + ")", resultText);
    }
    catch (const std::exception &e) {
        showResult(QString("Error: ") + e.what());
    }
}

void MatrixWidget::onSolveClicked() {
    QString nameA = matrixACombo->currentText();
    QString nameB = matrixBCombo->currentText();

    try {
        Matrix dataA = getMatrixData(nameA);
        Matrix matB = getMatrixData(nameB);

        if (matB.getCol() != 1) {
            throw std::invalid_argument("Right side matrix must be a column vector.");
        }

        std::vector<double> dataB(matB.getRow());
        for (int i = 0; i < matB.getRow(); i++) {
            dataB[i] = matB.get(i, 0);
        }

        MatrixSolver solver;
        std::vector<double> values = solver.solve(dataA, dataB);
        Matrix result(static_cast<int>(values.size()), 1);

        for (int i = 0; i < static_cast<int>(values.size()); i++) {
            result.set(i, 0, values[i]);
        }

        setMatrixData("Re", result);
        QString resultText = matrixToString(result);
        showResult(QString("solve(%1,%2) -> Re: %3").arg(nameA, nameB, resultText));
        emit historyRequested("Matrix", "solve(" + nameA + "," + nameB + ")", resultText);
    }
    catch (const std::exception &e) {
        showResult(QString("Error: ") + e.what());
    }
}