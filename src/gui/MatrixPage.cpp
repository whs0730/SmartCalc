#include "MatrixPage.h"
#include <QtWidgets>
#include <stdexcept>

MatrixWidget::MatrixWidget(QWidget *parent) : QWidget(parent) {
	setupUI();
}

void MatrixWidget::setupUI() {
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	
	QGroupBox *createGroup = new QGroupBox("CreateMatrix", this);
	QHBoxLayout *createLayout = new QHBoxLayout(createGroup);
	
	matrixNameCombo=new QComboBox(this);
	for (char c = 'A'; c <= 'Z'; ++c) matrixNameCombo->addItem(QString(c));
	matrixNameCombo->addItem(QString("Re"));
	createLayout->addWidget(new QLabel("Name:", this));
	createLayout->addWidget(matrixNameCombo);
	
	rowSpin = new QSpinBox(this);
	rowSpin->setRange(1, 6);
	colSpin = new QSpinBox(this);
	colSpin->setRange(1, 6);
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
	
	// ----- 运算区域 -----
	QGroupBox *opGroup = new QGroupBox("MatrixCalculation", this);
	QGridLayout *opLayout = new QGridLayout(opGroup);
	
	matrixACombo = new QComboBox(this);
	matrixBCombo = new QComboBox(this);
	// 填充字母
	for (char c = 'A'; c <= 'Z'; ++c) {
		matrixACombo->addItem(QString(c));
		matrixBCombo->addItem(QString(c));
	}
	matrixACombo->addItem(QString("Re"));
	matrixBCombo->addItem(QString("Re"));
	
	opLayout->addWidget(new QLabel("Mat A:", this),0,0);
	opLayout->addWidget(matrixACombo,0,1);
	opLayout->addWidget(new QLabel("Mat B:", this),0,2);
	opLayout->addWidget(matrixBCombo,0,3);
	
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
	connect(detBtn, &QPushButton::clicked, this, &::MatrixWidget::onDeterminantClicked);
	connect(invBtn, &QPushButton::clicked, this, &MatrixWidget::onInverseClicked);
	connect(solveBtn, &QPushButton::clicked, this, &MatrixWidget::onSolveClicked);
	opLayout->addWidget(addBtn,1,0);
	opLayout->addWidget(subBtn,1,1);
	opLayout->addWidget(dotBtn,1,2);
	opLayout->addWidget(transBtn,1,3);
	opLayout->addWidget(detBtn,2,0);
	opLayout->addWidget(invBtn,2,1);
	opLayout->addWidget(solveBtn,2,2);
	
	mainLayout->addWidget(opGroup);
	
	// 结果显示
	resultDisplay = new QTextEdit(this);
	resultDisplay->setReadOnly(true);
	mainLayout->addWidget(resultDisplay);
}

Matrix MatrixWidget::getMatrixData(const QString &name)const{
	QTableWidget* table=matrixTables.value(name,nullptr);
	if(!table)return {};
	int row=table->rowCount();
	int col=table->columnCount();
	Matrix data=Matrix(row,col);
	for(int i=0;i<row;++i){
		for(int j=0;j<col;++j){
			QTableWidgetItem* item=table->item(i,j);
			data.set(i, j, item?item->text().toDouble():0.0);
		}
	}
	return data;
}
void MatrixWidget::setMatrixData(const QString &name, const Matrix &data){
	if(!matrixTables.contains(name)){
		int r=data.getRow();
		int c=data.getCol();
		QTableWidget* table=matrixTables.value(name,nullptr);
		if(!table){
			table=new QTableWidget(r,c,this);
			int index=tabWidget->addTab(table,name);
			matrixTables[name]=table;
			tabWidget->setCurrentIndex(index);
			updateMatrixComboBoxes();
		}
		else{
			table->setRowCount(r);
			table->setColumnCount(c);
		}
		
		for(int i=0;i<data.getRow();++i){
			for(int j=0;j<data.getCol();++j){
				table->setItem(i, j, new QTableWidgetItem(QString::number(data.get(i,j))));
			}
		}
		int idx = tabWidget->indexOf(table);
		if (idx != -1) tabWidget->setCurrentIndex(idx);
	}
	
}
void MatrixWidget::onCreateMatrixClicked() {
	QString name=matrixNameCombo->currentText();
	int r = rowSpin->value();
	int c = colSpin->value();
	
	if (matrixTables.contains(name)) {
		QTableWidget *old = matrixTables[name];
		int index = tabWidget->indexOf(old);
		if(index!=-1)tabWidget->removeTab(index);
		delete old;
		matrixTables.remove(name);
	}
	
	QTableWidget* table=new QTableWidget(r,c,this);
	for (int i=0; i<r; ++i)
		for (int j=0; j<c; ++j)
			table->setItem(i, j, new QTableWidgetItem("0"));
	int index = tabWidget->addTab(table,name);
	matrixTables[name] = table;
	tabWidget->setCurrentIndex(index);
	
	updateMatrixComboBoxes();

}

void MatrixWidget::onMatrixTabClosed(int index) {
	QWidget *w = tabWidget->widget(index);
	QTableWidget *table = qobject_cast<QTableWidget*>(w);
	if (!table) return;

	QString name = tabWidget->tabText(index);
	matrixTables.remove(name);
	tabWidget->removeTab(index);
	delete table;
	updateMatrixComboBoxes();
}

void MatrixWidget::updateMatrixComboBoxes(){
	QStringList names = matrixTables.keys();
	matrixACombo->clear();
	matrixBCombo->clear();
	matrixACombo->addItems(names);
	matrixBCombo->addItems(names);
	if (names.size() == 1) {
		matrixACombo->setCurrentIndex(0);
		matrixBCombo->setCurrentIndex(0);
	} else if (names.size() >= 2) {
		matrixACombo->setCurrentIndex(0);
		matrixBCombo->setCurrentIndex(1);
	}
}

void MatrixWidget::showResult(const QString &result){
	resultDisplay->append(result);
}

void MatrixWidget::onAddClicked() {
	QString nameA = matrixACombo->currentText();
	QString nameB = matrixBCombo->currentText();
	auto dataA = getMatrixData(nameA);
	auto dataB = getMatrixData(nameB);
	try {
		// 调用后端接口
		// Belike:auto result = dataA.add(dataB);
		// 这里用占位数据
		Matrix result = dataA;
		// 显示结果
		setMatrixData("Re", result);
		showResult("结果已存入矩阵 Re");
	} catch (const std::exception &e) {
		showResult(QString("错误: ") + e.what());
	}
}
void MatrixWidget::onSubClicked(){
	QString nameA = matrixACombo->currentText();
	QString nameB = matrixBCombo->currentText();
	auto dataA = getMatrixData(nameA);
	auto dataB = getMatrixData(nameB);
	try {
		// 调用后端接口
		// Belike:auto result = dataA.add(dataB);
		// 这里用占位数据
		Matrix result = dataA;
		// 显示结果
		setMatrixData("Re", result);
		showResult("结果已存入矩阵 Re");
	} catch (const std::exception &e) {
		showResult(QString("错误: ") + e.what());
	}
}
void MatrixWidget::onDotClicked(){
	QString nameA = matrixACombo->currentText();
	QString nameB = matrixBCombo->currentText();
	auto dataA = getMatrixData(nameA);
	auto dataB = getMatrixData(nameB);
	try {
		// 调用后端接口
		
		// 这里用占位数据
		Matrix result = dataA;
		// 显示结果
		setMatrixData("Re", result);
		showResult("结果已存入矩阵 Re");
	} catch (const std::exception &e) {
		showResult(QString("错误: ") + e.what());
	}
}
void MatrixWidget::onTransposeClicked(){
	QString nameA = matrixACombo->currentText();
	auto dataA = getMatrixData(nameA);
	try {
		// 调用后端接口
		// 这里用占位数据
		Matrix result = dataA;
		// 显示结果
		setMatrixData("Re", result);
		showResult("结果已存入矩阵 Re");
	} catch (const std::exception &e) {
		showResult(QString("错误: ") + e.what());
	}
}
void MatrixWidget::onDeterminantClicked(){
	QString nameA = matrixACombo->currentText();
	auto dataA = getMatrixData(nameA);
	try {
		// 调用后端接口
		// Belike:auto result = dataA.add(dataB);
		// 这里用占位数据
		Matrix result = dataA;
		// 显示结果
		setMatrixData("Re", result);
		showResult("结果已存入矩阵 Re");
	} catch (const std::exception &e) {
		showResult(QString("错误: ") + e.what());
	}
}
void MatrixWidget::onInverseClicked(){
	QString nameA = matrixACombo->currentText();
	auto dataA = getMatrixData(nameA);
	try {
		// 调用后端接口
		// Belike:auto result = dataA.add(dataB);
		// 这里用占位数据
		Matrix result = dataA;
		// 显示结果
		setMatrixData("Re", result);
		showResult("结果已存入矩阵 Re");
	} catch (const std::exception &e) {
		showResult(QString("错误: ") + e.what());
	}
}
void MatrixWidget::onSolveClicked(){
	QString nameA = matrixACombo->currentText();
	QString nameB =matrixBCombo->currentText();
	auto dataA = getMatrixData(nameA);
	auto matB=getMatrixData(nameB);
	if(!(matB.getCol()==1)){
		showResult(QString("Wrong Col,will take the first row"));
	}
	vector<double> dataB(matB.getRow());
	for(int i=0;i<matB.getRow();i++){
		dataB[i]=matB.get(i,0);
	}
	try {
		// 调用后端接口
		//std::vector<double>re=...
		std::vector<double>re=dataB;
		// 这里用占位数据
		Matrix result(1,int(re.size()));
		for(int i=0;i<re.size();i++){
			result.set(1, i, re[i]);
		}
		
		// 显示结果
		setMatrixData("Re", result);
		showResult("结果已存入矩阵 Re");
	} catch (const std::exception &e) {
		showResult(QString("错误: ") + e.what());
	}
}
