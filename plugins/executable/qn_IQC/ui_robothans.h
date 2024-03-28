/********************************************************************************
** Form generated from reading UI file 'robothans.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROBOTHANS_H
#define UI_ROBOTHANS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RobotHans
{
public:
    QPushButton *saveButton;
    QPushButton *runPosButton;
    QFrame *line_2;
    QFrame *line_3;
    QWidget *horizontalLayoutWidget_6;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_11;
    QSpacerItem *verticalSpacer_11;
    QLineEdit *scanner_port;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_IP;
    QSpacerItem *verticalSpacer_9;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *hans_ip1;
    QLabel *label;
    QLineEdit *hans_ip2;
    QLabel *label_3;
    QLineEdit *hans_ip3;
    QLabel *label_4;
    QLineEdit *hans_ip4;
    QFrame *line_4;
    QPushButton *readPositionButton;
    QFrame *line;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_IP_2;
    QSpacerItem *verticalSpacer_10;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *scanner_ip1;
    QLabel *label_5;
    QLineEdit *scanner_ip2;
    QLabel *label_6;
    QLineEdit *scanner_ip3;
    QLabel *label_7;
    QLineEdit *scanner_ip4;
    QPushButton *connectButton;
    QLineEdit *lineEdit_FilePath;
    QFrame *line_5;
    QWidget *horizontalLayoutWidget_7;
    QHBoxLayout *horizontalLayout_12;
    QCheckBox *checkBoxTakePhoto;
    QSpacerItem *verticalSpacer_18;
    QCheckBox *checkBoxFlowOver;
    QSpacerItem *verticalSpacer_17;
    QLabel *labelDegree_2;
    QLineEdit *lineEditDegree;
    QTableWidget *tableWidget;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_10;
    QSpacerItem *verticalSpacer_8;
    QLineEdit *robot_Port;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *record;
    QPushButton *addrow;
    QPushButton *deleterow;
    QPushButton *moveup;
    QPushButton *movedown;
    QFrame *line_7;
    QPushButton *saveButtonDegreeCom;
    QPushButton *cancelButtonDegreeCom;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_8;
    QLabel *labelDegree_3;
    QSpacerItem *verticalSpacer_19;
    QLineEdit *lineEditDegreeCom;
    QLabel *label_J1;
    QLineEdit *lineEdit_J1_2;
    QLineEdit *lineEdit_J2;
    QLabel *label_J2;
    QLineEdit *lineEdit_J3;
    QLabel *label_J3;
    QLineEdit *lineEdit_J4;
    QLabel *label_J4;
    QLineEdit *lineEdit_J5;
    QLabel *label_J5;
    QLabel *label_J6;
    QLineEdit *lineEdit_J6;
    QPushButton *closeButton;

    void setupUi(QDialog *RobotHans)
    {
        if (RobotHans->objectName().isEmpty())
            RobotHans->setObjectName(QString::fromUtf8("RobotHans"));
        RobotHans->resize(856, 862);
        saveButton = new QPushButton(RobotHans);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setGeometry(QRect(690, 640, 111, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font.setPointSize(16);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        saveButton->setFont(font);
        saveButton->setStyleSheet(QString::fromUtf8("font: 16pt \"MS Shell Dlg 2\";"));
        runPosButton = new QPushButton(RobotHans);
        runPosButton->setObjectName(QString::fromUtf8("runPosButton"));
        runPosButton->setGeometry(QRect(690, 310, 111, 31));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(runPosButton->sizePolicy().hasHeightForWidth());
        runPosButton->setSizePolicy(sizePolicy);
        runPosButton->setStyleSheet(QString::fromUtf8("font: 16pt \"MS Shell Dlg 2\";"));
        runPosButton->setIconSize(QSize(20, 20));
        line_2 = new QFrame(RobotHans);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(90, 210, 551, 20));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(RobotHans);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(630, 20, 31, 691));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);
        horizontalLayoutWidget_6 = new QWidget(RobotHans);
        horizontalLayoutWidget_6->setObjectName(QString::fromUtf8("horizontalLayoutWidget_6"));
        horizontalLayoutWidget_6->setGeometry(QRect(430, 120, 191, 41));
        horizontalLayout_7 = new QHBoxLayout(horizontalLayoutWidget_6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_11 = new QLabel(horizontalLayoutWidget_6);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        QFont font1;
        font1.setPointSize(11);
        label_11->setFont(font1);

        horizontalLayout_7->addWidget(label_11);

        verticalSpacer_11 = new QSpacerItem(38, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout_7->addItem(verticalSpacer_11);

        scanner_port = new QLineEdit(horizontalLayoutWidget_6);
        scanner_port->setObjectName(QString::fromUtf8("scanner_port"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scanner_port->sizePolicy().hasHeightForWidth());
        scanner_port->setSizePolicy(sizePolicy1);
        scanner_port->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    font: 12pt Microsoft YaHei;\n"
"	border: 1px solid gray;\n"
"}\n"
""));

        horizontalLayout_7->addWidget(scanner_port);

        horizontalLayoutWidget_4 = new QWidget(RobotHans);
        horizontalLayoutWidget_4->setObjectName(QString::fromUtf8("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(110, 70, 291, 41));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_IP = new QLabel(horizontalLayoutWidget_4);
        label_IP->setObjectName(QString::fromUtf8("label_IP"));
        label_IP->setFont(font1);

        horizontalLayout_4->addWidget(label_IP);

        verticalSpacer_9 = new QSpacerItem(38, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout_4->addItem(verticalSpacer_9);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, -1, -1);
        hans_ip1 = new QLineEdit(horizontalLayoutWidget_4);
        hans_ip1->setObjectName(QString::fromUtf8("hans_ip1"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(hans_ip1->sizePolicy().hasHeightForWidth());
        hans_ip1->setSizePolicy(sizePolicy2);
        hans_ip1->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    font: 12pt Microsoft YaHei;\n"
"	border: 1px solid gray;\n"
"}"));
        hans_ip1->setMaxLength(3);
        hans_ip1->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(hans_ip1);

        label = new QLabel(horizontalLayoutWidget_4);
        label->setObjectName(QString::fromUtf8("label"));
        label->setEnabled(true);
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(3);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);
        QFont font2;
        font2.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font2.setPointSize(20);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        label->setFont(font2);
        label->setStyleSheet(QString::fromUtf8(""));
        label->setLineWidth(0);

        horizontalLayout_2->addWidget(label);

        hans_ip2 = new QLineEdit(horizontalLayoutWidget_4);
        hans_ip2->setObjectName(QString::fromUtf8("hans_ip2"));
        sizePolicy2.setHeightForWidth(hans_ip2->sizePolicy().hasHeightForWidth());
        hans_ip2->setSizePolicy(sizePolicy2);
        hans_ip2->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    font: 12pt Microsoft YaHei;\n"
"	border: 1px solid gray;\n"
"}"));
        hans_ip2->setMaxLength(3);
        hans_ip2->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(hans_ip2);

        label_3 = new QLabel(horizontalLayoutWidget_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setEnabled(true);
        sizePolicy3.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy3);
        label_3->setFont(font2);
        label_3->setStyleSheet(QString::fromUtf8(""));
        label_3->setLineWidth(0);

        horizontalLayout_2->addWidget(label_3);

        hans_ip3 = new QLineEdit(horizontalLayoutWidget_4);
        hans_ip3->setObjectName(QString::fromUtf8("hans_ip3"));
        sizePolicy2.setHeightForWidth(hans_ip3->sizePolicy().hasHeightForWidth());
        hans_ip3->setSizePolicy(sizePolicy2);
        hans_ip3->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    font: 12pt Microsoft YaHei;\n"
"	border: 1px solid gray;\n"
"}"));
        hans_ip3->setMaxLength(3);
        hans_ip3->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(hans_ip3);

        label_4 = new QLabel(horizontalLayoutWidget_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setEnabled(true);
        sizePolicy3.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy3);
        label_4->setFont(font2);
        label_4->setStyleSheet(QString::fromUtf8(""));
        label_4->setLineWidth(0);

        horizontalLayout_2->addWidget(label_4);

        hans_ip4 = new QLineEdit(horizontalLayoutWidget_4);
        hans_ip4->setObjectName(QString::fromUtf8("hans_ip4"));
        sizePolicy2.setHeightForWidth(hans_ip4->sizePolicy().hasHeightForWidth());
        hans_ip4->setSizePolicy(sizePolicy2);
        hans_ip4->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    font: 12pt Microsoft YaHei;\n"
"	border: 1px solid gray;\n"
"}"));
        hans_ip4->setMaxLength(3);
        hans_ip4->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(hans_ip4);


        horizontalLayout_4->addLayout(horizontalLayout_2);

        line_4 = new QFrame(RobotHans);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(90, 10, 551, 20));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        readPositionButton = new QPushButton(RobotHans);
        readPositionButton->setObjectName(QString::fromUtf8("readPositionButton"));
        readPositionButton->setGeometry(QRect(690, 260, 111, 31));
        sizePolicy.setHeightForWidth(readPositionButton->sizePolicy().hasHeightForWidth());
        readPositionButton->setSizePolicy(sizePolicy);
        readPositionButton->setStyleSheet(QString::fromUtf8("font: 16pt \"MS Shell Dlg 2\";"));
        readPositionButton->setIconSize(QSize(20, 20));
        line = new QFrame(RobotHans);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(90, 390, 551, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        horizontalLayoutWidget_5 = new QWidget(RobotHans);
        horizontalLayoutWidget_5->setObjectName(QString::fromUtf8("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(110, 120, 291, 41));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget_5);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_IP_2 = new QLabel(horizontalLayoutWidget_5);
        label_IP_2->setObjectName(QString::fromUtf8("label_IP_2"));
        label_IP_2->setFont(font1);

        horizontalLayout_5->addWidget(label_IP_2);

        verticalSpacer_10 = new QSpacerItem(38, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout_5->addItem(verticalSpacer_10);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(1);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(-1, 0, -1, -1);
        scanner_ip1 = new QLineEdit(horizontalLayoutWidget_5);
        scanner_ip1->setObjectName(QString::fromUtf8("scanner_ip1"));
        sizePolicy2.setHeightForWidth(scanner_ip1->sizePolicy().hasHeightForWidth());
        scanner_ip1->setSizePolicy(sizePolicy2);
        scanner_ip1->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    font: 12pt Microsoft YaHei;\n"
"	border: 1px solid gray;\n"
"}"));
        scanner_ip1->setMaxLength(3);
        scanner_ip1->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(scanner_ip1);

        label_5 = new QLabel(horizontalLayoutWidget_5);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setEnabled(true);
        sizePolicy3.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy3);
        label_5->setFont(font2);
        label_5->setStyleSheet(QString::fromUtf8(""));
        label_5->setLineWidth(0);

        horizontalLayout_6->addWidget(label_5);

        scanner_ip2 = new QLineEdit(horizontalLayoutWidget_5);
        scanner_ip2->setObjectName(QString::fromUtf8("scanner_ip2"));
        sizePolicy2.setHeightForWidth(scanner_ip2->sizePolicy().hasHeightForWidth());
        scanner_ip2->setSizePolicy(sizePolicy2);
        scanner_ip2->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    font: 12pt Microsoft YaHei;\n"
"	border: 1px solid gray;\n"
"}"));
        scanner_ip2->setMaxLength(3);
        scanner_ip2->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(scanner_ip2);

        label_6 = new QLabel(horizontalLayoutWidget_5);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setEnabled(true);
        sizePolicy3.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy3);
        label_6->setFont(font2);
        label_6->setStyleSheet(QString::fromUtf8(""));
        label_6->setLineWidth(0);

        horizontalLayout_6->addWidget(label_6);

        scanner_ip3 = new QLineEdit(horizontalLayoutWidget_5);
        scanner_ip3->setObjectName(QString::fromUtf8("scanner_ip3"));
        sizePolicy2.setHeightForWidth(scanner_ip3->sizePolicy().hasHeightForWidth());
        scanner_ip3->setSizePolicy(sizePolicy2);
        scanner_ip3->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    font: 12pt Microsoft YaHei;\n"
"	border: 1px solid gray;\n"
"}"));
        scanner_ip3->setMaxLength(3);
        scanner_ip3->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(scanner_ip3);

        label_7 = new QLabel(horizontalLayoutWidget_5);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setEnabled(true);
        sizePolicy3.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy3);
        label_7->setFont(font2);
        label_7->setStyleSheet(QString::fromUtf8(""));
        label_7->setLineWidth(0);

        horizontalLayout_6->addWidget(label_7);

        scanner_ip4 = new QLineEdit(horizontalLayoutWidget_5);
        scanner_ip4->setObjectName(QString::fromUtf8("scanner_ip4"));
        sizePolicy2.setHeightForWidth(scanner_ip4->sizePolicy().hasHeightForWidth());
        scanner_ip4->setSizePolicy(sizePolicy2);
        scanner_ip4->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    font: 12pt Microsoft YaHei;\n"
"	border: 1px solid gray;\n"
"}"));
        scanner_ip4->setMaxLength(3);
        scanner_ip4->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(scanner_ip4);


        horizontalLayout_5->addLayout(horizontalLayout_6);

        connectButton = new QPushButton(RobotHans);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));
        connectButton->setGeometry(QRect(690, 70, 111, 31));
        sizePolicy.setHeightForWidth(connectButton->sizePolicy().hasHeightForWidth());
        connectButton->setSizePolicy(sizePolicy);
        connectButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	font: 16pt \"MS Shell Dlg 2\";\n"
"    color: rgb(255, 0, 0); \n"
"}"));
        connectButton->setIconSize(QSize(20, 20));
        lineEdit_FilePath = new QLineEdit(RobotHans);
        lineEdit_FilePath->setObjectName(QString::fromUtf8("lineEdit_FilePath"));
        lineEdit_FilePath->setGeometry(QRect(90, 650, 541, 31));
        lineEdit_FilePath->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    font: 12pt Microsoft YaHei;\n"
"	border: 1px solid gray;\n"
"}"));
        line_5 = new QFrame(RobotHans);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setGeometry(QRect(70, 20, 31, 691));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);
        horizontalLayoutWidget_7 = new QWidget(RobotHans);
        horizontalLayoutWidget_7->setObjectName(QString::fromUtf8("horizontalLayoutWidget_7"));
        horizontalLayoutWidget_7->setGeometry(QRect(110, 290, 508, 31));
        horizontalLayout_12 = new QHBoxLayout(horizontalLayoutWidget_7);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        checkBoxTakePhoto = new QCheckBox(horizontalLayoutWidget_7);
        checkBoxTakePhoto->setObjectName(QString::fromUtf8("checkBoxTakePhoto"));
        checkBoxTakePhoto->setStyleSheet(QString::fromUtf8("font: 11pt \"MS Shell Dlg 2\";"));

        horizontalLayout_12->addWidget(checkBoxTakePhoto);

        verticalSpacer_18 = new QSpacerItem(88, 26, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout_12->addItem(verticalSpacer_18);

        checkBoxFlowOver = new QCheckBox(horizontalLayoutWidget_7);
        checkBoxFlowOver->setObjectName(QString::fromUtf8("checkBoxFlowOver"));
        checkBoxFlowOver->setFont(font1);

        horizontalLayout_12->addWidget(checkBoxFlowOver);

        verticalSpacer_17 = new QSpacerItem(88, 26, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout_12->addItem(verticalSpacer_17);

        labelDegree_2 = new QLabel(horizontalLayoutWidget_7);
        labelDegree_2->setObjectName(QString::fromUtf8("labelDegree_2"));
        labelDegree_2->setFont(font1);

        horizontalLayout_12->addWidget(labelDegree_2);

        lineEditDegree = new QLineEdit(horizontalLayoutWidget_7);
        lineEditDegree->setObjectName(QString::fromUtf8("lineEditDegree"));
        sizePolicy1.setHeightForWidth(lineEditDegree->sizePolicy().hasHeightForWidth());
        lineEditDegree->setSizePolicy(sizePolicy1);

        horizontalLayout_12->addWidget(lineEditDegree);

        tableWidget = new QTableWidget(RobotHans);
        if (tableWidget->columnCount() < 9)
            tableWidget->setColumnCount(9);
        QFont font3;
        font3.setPointSize(9);
        font3.setStyleStrategy(QFont::NoAntialias);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem->setFont(font3);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(90, 430, 541, 192));
        tableWidget->setAutoScrollMargin(9);
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(9);
        horizontalLayoutWidget_3 = new QWidget(RobotHans);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(430, 70, 191, 41));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(horizontalLayoutWidget_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font1);

        horizontalLayout_3->addWidget(label_10);

        verticalSpacer_8 = new QSpacerItem(38, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout_3->addItem(verticalSpacer_8);

        robot_Port = new QLineEdit(horizontalLayoutWidget_3);
        robot_Port->setObjectName(QString::fromUtf8("robot_Port"));
        sizePolicy1.setHeightForWidth(robot_Port->sizePolicy().hasHeightForWidth());
        robot_Port->setSizePolicy(sizePolicy1);
        robot_Port->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    font: 12pt Microsoft YaHei;\n"
"	border: 1px solid gray;\n"
"}\n"
""));

        horizontalLayout_3->addWidget(robot_Port);

        layoutWidget = new QWidget(RobotHans);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(690, 400, 111, 201));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        record = new QPushButton(layoutWidget);
        record->setObjectName(QString::fromUtf8("record"));
        sizePolicy.setHeightForWidth(record->sizePolicy().hasHeightForWidth());
        record->setSizePolicy(sizePolicy);
        record->setStyleSheet(QString::fromUtf8("font: 16pt \"MS Shell Dlg 2\";"));
        record->setIconSize(QSize(20, 20));

        verticalLayout_2->addWidget(record);

        addrow = new QPushButton(layoutWidget);
        addrow->setObjectName(QString::fromUtf8("addrow"));
        sizePolicy.setHeightForWidth(addrow->sizePolicy().hasHeightForWidth());
        addrow->setSizePolicy(sizePolicy);
        addrow->setStyleSheet(QString::fromUtf8("font: 16pt \"MS Shell Dlg 2\";"));
        addrow->setIconSize(QSize(20, 20));

        verticalLayout_2->addWidget(addrow);

        deleterow = new QPushButton(layoutWidget);
        deleterow->setObjectName(QString::fromUtf8("deleterow"));
        sizePolicy.setHeightForWidth(deleterow->sizePolicy().hasHeightForWidth());
        deleterow->setSizePolicy(sizePolicy);
        deleterow->setStyleSheet(QString::fromUtf8("font: 16pt \"MS Shell Dlg 2\";"));
        deleterow->setIconSize(QSize(20, 20));

        verticalLayout_2->addWidget(deleterow);

        moveup = new QPushButton(layoutWidget);
        moveup->setObjectName(QString::fromUtf8("moveup"));
        sizePolicy.setHeightForWidth(moveup->sizePolicy().hasHeightForWidth());
        moveup->setSizePolicy(sizePolicy);
        moveup->setStyleSheet(QString::fromUtf8("font: 16pt \"MS Shell Dlg 2\";"));
        moveup->setIconSize(QSize(20, 20));

        verticalLayout_2->addWidget(moveup);

        movedown = new QPushButton(layoutWidget);
        movedown->setObjectName(QString::fromUtf8("movedown"));
        sizePolicy.setHeightForWidth(movedown->sizePolicy().hasHeightForWidth());
        movedown->setSizePolicy(sizePolicy);
        movedown->setStyleSheet(QString::fromUtf8("font: 16pt \"MS Shell Dlg 2\";"));
        movedown->setIconSize(QSize(20, 20));

        verticalLayout_2->addWidget(movedown);

        line_7 = new QFrame(RobotHans);
        line_7->setObjectName(QString::fromUtf8("line_7"));
        line_7->setGeometry(QRect(90, 700, 551, 20));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);
        saveButtonDegreeCom = new QPushButton(RobotHans);
        saveButtonDegreeCom->setObjectName(QString::fromUtf8("saveButtonDegreeCom"));
        saveButtonDegreeCom->setGeometry(QRect(410, 330, 111, 31));
        sizePolicy.setHeightForWidth(saveButtonDegreeCom->sizePolicy().hasHeightForWidth());
        saveButtonDegreeCom->setSizePolicy(sizePolicy);
        saveButtonDegreeCom->setStyleSheet(QString::fromUtf8("font: 16pt \"MS Shell Dlg 2\";"));
        saveButtonDegreeCom->setIconSize(QSize(20, 20));
        cancelButtonDegreeCom = new QPushButton(RobotHans);
        cancelButtonDegreeCom->setObjectName(QString::fromUtf8("cancelButtonDegreeCom"));
        cancelButtonDegreeCom->setGeometry(QRect(520, 330, 111, 31));
        sizePolicy.setHeightForWidth(cancelButtonDegreeCom->sizePolicy().hasHeightForWidth());
        cancelButtonDegreeCom->setSizePolicy(sizePolicy);
        cancelButtonDegreeCom->setStyleSheet(QString::fromUtf8("font: 16pt \"MS Shell Dlg 2\";"));
        cancelButtonDegreeCom->setIconSize(QSize(20, 20));
        layoutWidget1 = new QWidget(RobotHans);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(110, 330, 261, 31));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        labelDegree_3 = new QLabel(layoutWidget1);
        labelDegree_3->setObjectName(QString::fromUtf8("labelDegree_3"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font4.setPointSize(11);
        font4.setBold(false);
        font4.setItalic(false);
        font4.setWeight(50);
        labelDegree_3->setFont(font4);
        labelDegree_3->setStyleSheet(QString::fromUtf8("font: 11pt \"MS Shell Dlg 2\";"));

        horizontalLayout_8->addWidget(labelDegree_3);

        verticalSpacer_19 = new QSpacerItem(88, 26, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout_8->addItem(verticalSpacer_19);

        lineEditDegreeCom = new QLineEdit(layoutWidget1);
        lineEditDegreeCom->setObjectName(QString::fromUtf8("lineEditDegreeCom"));
        sizePolicy1.setHeightForWidth(lineEditDegreeCom->sizePolicy().hasHeightForWidth());
        lineEditDegreeCom->setSizePolicy(sizePolicy1);

        horizontalLayout_8->addWidget(lineEditDegreeCom);

        label_J1 = new QLabel(RobotHans);
        label_J1->setObjectName(QString::fromUtf8("label_J1"));
        label_J1->setGeometry(QRect(110, 240, 14, 36));
        label_J1->setFont(font1);
        lineEdit_J1_2 = new QLineEdit(RobotHans);
        lineEdit_J1_2->setObjectName(QString::fromUtf8("lineEdit_J1_2"));
        lineEdit_J1_2->setGeometry(QRect(140, 240, 41, 36));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(lineEdit_J1_2->sizePolicy().hasHeightForWidth());
        lineEdit_J1_2->setSizePolicy(sizePolicy4);
        lineEdit_J1_2->setFrame(true);
        lineEdit_J2 = new QLineEdit(RobotHans);
        lineEdit_J2->setObjectName(QString::fromUtf8("lineEdit_J2"));
        lineEdit_J2->setGeometry(QRect(239, 240, 41, 36));
        sizePolicy4.setHeightForWidth(lineEdit_J2->sizePolicy().hasHeightForWidth());
        lineEdit_J2->setSizePolicy(sizePolicy4);
        label_J2 = new QLabel(RobotHans);
        label_J2->setObjectName(QString::fromUtf8("label_J2"));
        label_J2->setGeometry(QRect(220, 240, 14, 36));
        label_J2->setFont(font1);
        lineEdit_J3 = new QLineEdit(RobotHans);
        lineEdit_J3->setObjectName(QString::fromUtf8("lineEdit_J3"));
        lineEdit_J3->setGeometry(QRect(330, 240, 41, 36));
        sizePolicy4.setHeightForWidth(lineEdit_J3->sizePolicy().hasHeightForWidth());
        lineEdit_J3->setSizePolicy(sizePolicy4);
        label_J3 = new QLabel(RobotHans);
        label_J3->setObjectName(QString::fromUtf8("label_J3"));
        label_J3->setGeometry(QRect(310, 240, 14, 36));
        label_J3->setFont(font1);
        lineEdit_J4 = new QLineEdit(RobotHans);
        lineEdit_J4->setObjectName(QString::fromUtf8("lineEdit_J4"));
        lineEdit_J4->setGeometry(QRect(410, 240, 41, 36));
        sizePolicy4.setHeightForWidth(lineEdit_J4->sizePolicy().hasHeightForWidth());
        lineEdit_J4->setSizePolicy(sizePolicy4);
        label_J4 = new QLabel(RobotHans);
        label_J4->setObjectName(QString::fromUtf8("label_J4"));
        label_J4->setGeometry(QRect(390, 240, 14, 36));
        label_J4->setFont(font1);
        lineEdit_J5 = new QLineEdit(RobotHans);
        lineEdit_J5->setObjectName(QString::fromUtf8("lineEdit_J5"));
        lineEdit_J5->setGeometry(QRect(500, 240, 31, 36));
        sizePolicy4.setHeightForWidth(lineEdit_J5->sizePolicy().hasHeightForWidth());
        lineEdit_J5->setSizePolicy(sizePolicy4);
        label_J5 = new QLabel(RobotHans);
        label_J5->setObjectName(QString::fromUtf8("label_J5"));
        label_J5->setGeometry(QRect(480, 240, 14, 36));
        label_J5->setFont(font1);
        label_J6 = new QLabel(RobotHans);
        label_J6->setObjectName(QString::fromUtf8("label_J6"));
        label_J6->setGeometry(QRect(560, 240, 14, 36));
        label_J6->setFont(font1);
        lineEdit_J6 = new QLineEdit(RobotHans);
        lineEdit_J6->setObjectName(QString::fromUtf8("lineEdit_J6"));
        lineEdit_J6->setGeometry(QRect(580, 240, 41, 36));
        sizePolicy4.setHeightForWidth(lineEdit_J6->sizePolicy().hasHeightForWidth());
        lineEdit_J6->setSizePolicy(sizePolicy4);
        closeButton = new QPushButton(RobotHans);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setGeometry(QRect(690, 690, 111, 41));
        closeButton->setFont(font);
        closeButton->setStyleSheet(QString::fromUtf8("font: 16pt \"MS Shell Dlg 2\";"));

        retranslateUi(RobotHans);

        QMetaObject::connectSlotsByName(RobotHans);
    } // setupUi

    void retranslateUi(QDialog *RobotHans)
    {
        RobotHans->setWindowTitle(QApplication::translate("RobotHans", "RobotHans", nullptr));
        saveButton->setText(QApplication::translate("RobotHans", "\344\277\235\345\255\230", nullptr));
        runPosButton->setText(QApplication::translate("RobotHans", "\350\275\254\345\212\250", nullptr));
        label_11->setText(QApplication::translate("RobotHans", "\346\211\253\346\217\217\344\273\252\347\253\257\345\217\243", nullptr));
        scanner_port->setText(QApplication::translate("RobotHans", "10004", nullptr));
        label_IP->setText(QApplication::translate("RobotHans", "\346\234\272\346\242\260\350\207\202IP", nullptr));
        hans_ip1->setInputMask(QString());
        hans_ip1->setText(QApplication::translate("RobotHans", "192", nullptr));
        label->setText(QApplication::translate("RobotHans", "\302\267", nullptr));
        hans_ip2->setInputMask(QString());
        hans_ip2->setText(QApplication::translate("RobotHans", "168", nullptr));
        label_3->setText(QApplication::translate("RobotHans", "\302\267", nullptr));
        hans_ip3->setInputMask(QString());
        hans_ip3->setText(QApplication::translate("RobotHans", "1", nullptr));
        label_4->setText(QApplication::translate("RobotHans", "\302\267", nullptr));
        hans_ip4->setInputMask(QString());
        hans_ip4->setText(QApplication::translate("RobotHans", "11", nullptr));
        readPositionButton->setText(QApplication::translate("RobotHans", "\350\257\273\345\217\226\347\202\271\344\275\215", nullptr));
        label_IP_2->setText(QApplication::translate("RobotHans", "\346\211\253\346\217\217\344\273\252IP", nullptr));
        scanner_ip1->setInputMask(QString());
        scanner_ip1->setText(QApplication::translate("RobotHans", "127", nullptr));
        label_5->setText(QApplication::translate("RobotHans", "\302\267", nullptr));
        scanner_ip2->setInputMask(QString());
        scanner_ip2->setText(QApplication::translate("RobotHans", "0", nullptr));
        label_6->setText(QApplication::translate("RobotHans", "\302\267", nullptr));
        scanner_ip3->setInputMask(QString());
        scanner_ip3->setText(QApplication::translate("RobotHans", "0", nullptr));
        label_7->setText(QApplication::translate("RobotHans", "\302\267", nullptr));
        scanner_ip4->setInputMask(QString());
        scanner_ip4->setText(QApplication::translate("RobotHans", "1", nullptr));
        connectButton->setText(QApplication::translate("RobotHans", "\350\277\236\346\216\245", nullptr));
        checkBoxTakePhoto->setText(QApplication::translate("RobotHans", "\346\230\257\345\220\246\346\213\215\347\205\247", nullptr));
        checkBoxFlowOver->setText(QApplication::translate("RobotHans", "\346\230\257\345\220\246\346\265\201\347\250\213\347\273\223\346\235\237", nullptr));
        labelDegree_2->setText(QApplication::translate("RobotHans", "\350\247\222\345\272\246", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("RobotHans", "J1", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("RobotHans", "J2", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("RobotHans", "J3", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("RobotHans", "J4", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("RobotHans", "J5", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("RobotHans", "J6", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("RobotHans", "Take_Photo", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("RobotHans", "Flow_Over", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("RobotHans", "Degree", nullptr));
        label_10->setText(QApplication::translate("RobotHans", "\346\234\272\346\242\260\350\207\202\347\253\257\345\217\243", nullptr));
        robot_Port->setText(QApplication::translate("RobotHans", "10003", nullptr));
        record->setText(QApplication::translate("RobotHans", "\350\256\260\345\275\225", nullptr));
        addrow->setText(QApplication::translate("RobotHans", "\346\226\260\345\242\236\350\241\214", nullptr));
        deleterow->setText(QApplication::translate("RobotHans", "\345\210\240\351\231\244\350\241\214", nullptr));
        moveup->setText(QApplication::translate("RobotHans", "\344\270\212\350\260\203", nullptr));
        movedown->setText(QApplication::translate("RobotHans", "\344\270\213\347\247\273", nullptr));
        saveButtonDegreeCom->setText(QApplication::translate("RobotHans", "\344\277\235\345\255\230", nullptr));
        cancelButtonDegreeCom->setText(QApplication::translate("RobotHans", "\345\217\226\346\266\210", nullptr));
        labelDegree_3->setText(QApplication::translate("RobotHans", "\350\247\222\345\272\246\350\241\245\345\201\277\345\200\274", nullptr));
        label_J1->setText(QApplication::translate("RobotHans", "J1", nullptr));
        label_J2->setText(QApplication::translate("RobotHans", "J2", nullptr));
        label_J3->setText(QApplication::translate("RobotHans", "J3", nullptr));
        label_J4->setText(QApplication::translate("RobotHans", "J4", nullptr));
        label_J5->setText(QApplication::translate("RobotHans", "J5", nullptr));
        label_J6->setText(QApplication::translate("RobotHans", "J6", nullptr));
        closeButton->setText(QApplication::translate("RobotHans", "\345\205\263\351\227\255\347\252\227\345\217\243", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RobotHans: public Ui_RobotHans {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROBOTHANS_H
