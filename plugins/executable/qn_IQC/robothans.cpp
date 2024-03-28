#include "robothans.h"
#include "./ui_robothans.h"
#include "CTCPClient_Rob.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QStringList>
#include <QMessageBox>

void saveTableToCSV(QTableWidget* table, const QString& filename, QWidget* parentWidget) {
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		// 如果文件无法打开，显示错误消息框
		QMessageBox::warning(parentWidget, "Error", "Cannot open file for writing: " + file.errorString());
		return;
	}

	QTextStream stream(&file);

	// 遍历表格的行和列，获取数据
	for (int i = 0; i < table->rowCount(); ++i) {
		QStringList rowContents;
		for (int j = 0; j < table->columnCount(); ++j) {
			QTableWidgetItem* item = table->item(i, j);
			QString text = item ? item->text() : "";
			// 处理文本中的双引号，将一个双引号替换为两个双引号
			text.replace("\"", "\"\"");
			// 如果文本包含逗号或双引号，将整个字段用双引号括起来
			if (text.contains(',') || text.contains('"')) {
				text.prepend('"').append('"');
			}
			rowContents << text;
		}
		// 将一行数据加入到流中，用逗号分隔
		stream << rowContents.join(',') << "\n";
	}

	file.close(); // 关闭文件

}

using std::string;
CTCPClient tcpClient;


RobotHans::RobotHans(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RobotHans),
	positionCount(0)
{
	AuoCtrlData stAutoData;
	stAutoData.rRobTargetPos[0] = 0;
	stAutoData.rRobTargetPos[1] = 0;
	stAutoData.rRobTargetPos[2] = 0;
	stAutoData.rRobTargetPos[3] = 0;
	stAutoData.rRobTargetPos[4] = 0;
	stAutoData.rRobTargetPos[5] = 0;

    ui->setupUi(this);
	loadAngleCompensationValue();
	connect(ui->saveButtonDegreeCom, &QPushButton::clicked, this, &RobotHans::on_saveButtonDegreeCom_clicked);
	connect(ui->cancelButtonDegreeCom, &QPushButton::clicked, this, &RobotHans::on_cancelButtonDegreeCom_clicked);
	connect(ui->addrow, &QPushButton::clicked, this, &RobotHans::on_addRowButton_clicked);
	connect(ui->deleterow, &QPushButton::clicked, this, &RobotHans::on_deleteRowButton_clicked);
	connect(ui->movedown, &QPushButton::clicked, this, &RobotHans::on_moveDownButton_clicked);
	connect(ui->moveup, &QPushButton::clicked, this, &RobotHans::on_moveUpButton_clicked);
	connect(ui->closeButton, &QPushButton::clicked, this, &RobotHans::on_closeButton_clicked);
	//connect(ui->saveButton, &QPushButton::clicked, this, &RobotHans::on_saveButton_clicked);
	connect(ui->record, &QPushButton::clicked, this, &RobotHans::on_recordButton_clicked);
	connect(ui->runPosButton, &QPushButton::clicked, this, &RobotHans::on_runPosButton_clicked);

}

RobotHans::~RobotHans()
{
	tcpClient.TcpClose();
    delete ui;
	tcpClient.CloseAndReleaseResources();
}

void RobotHans::on_runPosButton_clicked()
{
	QString degreeString = ui->lineEditDegree->text();
	QString degreeCom = ui->lineEditDegreeCom->text();
	bool ok;
	float Degree = degreeString.toFloat();
	float DegreeCom = degreeCom.toFloat();
	bool rc1 = tcpClient.ReadAndAdjustAngle(Degree,DegreeCom);
}

void RobotHans::on_saveButtonDegreeCom_clicked()
{
	QString DegreeCom_Write = ui->lineEditDegreeCom->text();
	float DegreeCom_Write_f = DegreeCom_Write.toFloat();
	currentValue = DegreeCom_Write_f;
	QFile file("angle_compensation_value.txt");
	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream out(&file);
		out << DegreeCom_Write_f;
		file.close();
	}
}

void RobotHans::on_cancelButtonDegreeCom_clicked()
{
	ui->lineEditDegreeCom->setText(QString::number(currentValue));
	QFile file("angle_compensation_value.txt");
	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream out(&file);
		out << currentValue;
		file.close();
	}
}

void RobotHans::on_connectButton_clicked()
{
	
	tcpClient.CreateSocket();
	

	QString ip1 = ui->hans_ip1->text();
	QString ip2 = ui->hans_ip2->text();
	QString ip3 = ui->hans_ip3->text();
	QString ip4 = ui->hans_ip4->text();
	QString ipAdress = ip1 + "." + ip2 + "." + ip3 + "." + ip4;
	QByteArray ipBytes = ipAdress.toUtf8();
	const char* serverIP = ipBytes.constData();
	u_short serverPort = ui->robot_Port->text().toUShort();

	int connectResult = tcpClient.ConnectSocket(serverIP, serverPort);
	//--------------------TurnTable----------------------------
	int rc = tcpClient.ConnectTurnTable();
	
}

void RobotHans::loadAngleCompensationValue()
{
	QFile file("angle_compensation_value.txt");
	if (file.open(QIODevice::ReadOnly)) {
		QTextStream stream(&file);
		ui->lineEditDegreeCom->setText(stream.readLine());
		file.close();
	}
}


void RobotHans::on_readPositionButton_clicked()
{

	string sendData = "ReadActPos,0,;";
	tcpClient.TcpSend(sendData);
	Sleep(100);
	string receivedData = tcpClient.TcpReceive();
	std::vector<std::string> dataParts = tcpClient.split(receivedData, ',');
	std::vector<double> jValues(6);
	QString text;
	for (int i = 0; i < 6; ++i) {
		stAutoData.rRobTargetPos[i] = std::stod(dataParts[i + 2]); // Convert string to double and store in the array
		
		QString jointText = QString::number(stAutoData.rRobTargetPos[i], 'f', 2); // 'f' for fixed-point notation, 2 for two decimals

		switch (i) 
		{
		case 0:
			ui->lineEdit_J1_2->setText(jointText);
			break;
		case 1:
			ui->lineEdit_J2->setText(jointText);
			break;
		case 2:
			ui->lineEdit_J3->setText(jointText);
			break;
		case 3:
			ui->lineEdit_J4->setText(jointText);
			break;
		case 4:
			ui->lineEdit_J5->setText(jointText);
			break;
		case 5:
			ui->lineEdit_J6->setText(jointText);
			break;
		default:
			// Handle unexpected index
			break;
		}
	}
	
}

void RobotHans::on_recordButton_clicked()
{
	QStringList values;
	values << ui->lineEdit_J1_2->text()
		<< ui->lineEdit_J2->text()
		<< ui->lineEdit_J3->text()
		<< ui->lineEdit_J4->text()
		<< ui->lineEdit_J5->text()
		<< ui->lineEdit_J6->text()
		<< QString::number(ui->lineEditDegree->text().toFloat())
		<< (ui->checkBoxTakePhoto->isChecked() ? "1" : "0")
		<< (ui->checkBoxFlowOver->isChecked() ? "1" : "0");
	int rowCount = ui->tableWidget->rowCount();
	ui->tableWidget->insertRow(rowCount);
	for (int i = 0; i < values.size(); ++i)
	{
		// 为每列创建一个新的QTableWidgetItem，并设置其文本值
		ui->tableWidget->setItem(rowCount, i, new QTableWidgetItem(values.at(i)));
	}

	
}
void RobotHans::on_addRowButton_clicked()
{
	QList<QTableWidgetItem *> selectedItems = ui->tableWidget->selectedItems();
	int insertRow = 0;

	if (!selectedItems.isEmpty()) {
		// Get the row number of the first selected item
		insertRow = ui->tableWidget->row(selectedItems.first()) + 1;
	}
	else {
		// If no row is selected, append a new row at the end
		insertRow = ui->tableWidget->rowCount();
	}

	// Insert a new row at the determined position
	ui->tableWidget->insertRow(insertRow);

	// Optionally clear the selection and select the new row
	ui->tableWidget->clearSelection();
	ui->tableWidget->selectRow(insertRow);
}
void RobotHans::on_deleteRowButton_clicked()
{
	QItemSelectionModel *select = ui->tableWidget->selectionModel();

	// Check if there is any selection
	if (!select->hasSelection()) {
		// If no selection, check the row count
		if (ui->tableWidget->rowCount() == 0) {
			// If there are no rows, show a message box
			QMessageBox::warning(this, "Warning", "剩余0行"); // "Remaining 0 rows"
		}
		else {
			// If there are rows but no selection, possibly prompt the user to select a row
			QMessageBox::information(this, "Information", "请选择要删除的行"); // "Please select a row to delete"
		}
		return; // Exit the function if nothing is selected
	}

	// Get the selected rows as a list of QModelIndexes
	QModelIndexList selectedRows = select->selectedRows();

	// Sort the row indices in descending order
	std::sort(selectedRows.begin(), selectedRows.end(), [](const QModelIndex &a, const QModelIndex &b) {
		return a.row() > b.row();
	});

	// Remove the rows from the highest index to the lowest
	for (const QModelIndex &index : selectedRows) {
		ui->tableWidget->removeRow(index.row());
	}
}
void RobotHans::on_moveDownButton_clicked()
{
	int currentRow = ui->tableWidget->currentRow();
	int rowCount = ui->tableWidget->rowCount(); // 获取表格的总行数
	if (currentRow >= 0 && currentRow < rowCount - 1) { // 确保不是最后一行
		swapRows(currentRow, currentRow + 1);
		ui->tableWidget->setCurrentCell(currentRow + 1, 0); // 更新选中行
	}
}
void RobotHans::on_moveUpButton_clicked()
{
	int currentRow = ui->tableWidget->currentRow();
	if (currentRow > 0) { // 确保不是第一行
		swapRows(currentRow, currentRow - 1);
		ui->tableWidget->setCurrentCell(currentRow - 1, 0); // 更新选中行
	}
}
void RobotHans::on_closeButton_clicked()
{
	this->close();
}
void RobotHans::on_saveButton_clicked()
{
	QString defaultDir = QCoreApplication::applicationDirPath();
	QString fileName = QFileDialog::getSaveFileName(this, tr("选择文件"), defaultDir, tr("CSV文件 (*.csv);;所有文件 (*.*)"));

	
	if (!fileName.isEmpty()) {
		
		QFileInfo fileInfo(fileName);
		if (fileInfo.exists()) {
			
			QMessageBox::StandardButton reply;
			reply = QMessageBox::question(this, tr("文件存在"), tr("文件 \"%1\" 已存在。您想要替换它吗?").arg(fileName),
				QMessageBox::Yes | QMessageBox::No);
			if (reply == QMessageBox::No) {
				
				return;
			}
			
		}

		
		saveTableToCSV(ui->tableWidget, fileName, this);

		ui->lineEdit_FilePath->setText(fileName);
	}
}
void RobotHans::swapRows(int row1, int row2)
{
	if (row1 < 0 || row2 < 0 || row1 >= ui->tableWidget->rowCount() || row2 >= ui->tableWidget->rowCount())
	{
		return;
	}

	for (int column = 0; column < ui->tableWidget->columnCount(); ++column)
	{
		QTableWidgetItem *item1 = ui->tableWidget->takeItem(row1, column);
		QTableWidgetItem *item2 = ui->tableWidget->takeItem(row2, column);
		ui->tableWidget->setItem(row1, column, item2);
		ui->tableWidget->setItem(row2, column, item1);
	}

}