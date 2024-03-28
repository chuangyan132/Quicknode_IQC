#ifndef ROBOTHANS_H
#define ROBOTHANS_H

#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>
#include <fstream>
#include "structInfo.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>


QT_BEGIN_NAMESPACE
namespace Ui { class RobotHans; }
QT_END_NAMESPACE

class RobotHans : public QDialog
{
    Q_OBJECT

public:
    RobotHans(QWidget *parent = nullptr);
    ~RobotHans();

	void closeEvent(QCloseEvent *event) {
		emit dialogClosed();
		QDialog::closeEvent(event);
	}
	void loadAngleCompensationValue();

signals:
	void dialogClosed();

private:
	void swapRows(int row1, int row2);

private slots:
	void on_connectButton_clicked();
	void on_runPosButton_clicked();
    void on_readPositionButton_clicked();
	void on_recordButton_clicked();
	void on_addRowButton_clicked();
	void on_deleteRowButton_clicked();
	void on_moveDownButton_clicked();
	void on_moveUpButton_clicked();
	void on_saveButton_clicked();
	void on_saveButtonDegreeCom_clicked();
	void on_cancelButtonDegreeCom_clicked();
	void on_closeButton_clicked();


private:
    Ui::RobotHans *ui;
	AuoCtrlData stAutoData;
	std::string filePath1;
	int positionCount = 0;
	float currentValue = 0;
	
};
#endif // ROBOTHANS_H
