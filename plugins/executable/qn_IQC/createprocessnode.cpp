/*!
* @brief   
* @project qn_einstarscan
* @file    createprocessnode.cpp
* @author  sunduo
* @email   sunduo@shining3d.com
* @license 
*     Copyright(C) shining3d. All rights reserved.
* @versions 
*     V0.1-sunduo 2023-08-24 11:02
*/
#include <QFile>
#include <QProcess>
#include <QThread>
#include <QDialog>
#include <QCoreApplication>
#include <QDir>
#include <cstdlib>
#include <QTimer>
#include <QString>
#include "qn_errors.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "createprocessnode.h"
#include "../include/plugincorehelper.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <iomanip> 
#include <sstream>
#include "robothans.h"
#include "CTCPClient_Rob.h"
using std::string;



REGISTER(IQC_ConfDlg, RobotHansNode);
REGISTER(IQC_Scan, IQCScanNode);
REGISTER(IQC_Hans, RobotHansMoveNode);
REGISTER(IQC_TurnTable, TrunTableNode);
REGISTER(IQC_Inspection, IqcInspectionNode);
REGISTER(RobotScan, RobotScanNode);


DialogManager *DialogManager::m_instance = new DialogManager(qApp);
DialogManager *DialogManager::instance() {
	//static DialogManager inst;
	if (m_instance)
		return m_instance;
}
DialogManager::DialogManager(QObject *parent) : QObject(parent), m_dialog(nullptr) {
}
DialogManager::~DialogManager() {
	if (m_dialog)
		m_dialog->deleteLater();
}
bool DialogManager::dialogIsClosed() {
	return m_dialogIsClosed;
}
void DialogManager::onOpenDialog()
{
	
	RobotHans w;
	w.exec();


}
UiHelper &UiHelper::instance() {
	static UiHelper _helper;
	return _helper;
}
UiHelper::UiHelper(QObject *parent) : QObject(parent) {
	connect(this, &UiHelper::toOpenDialog, DialogManager::instance(), &DialogManager::onOpenDialog, Qt::BlockingQueuedConnection);
}
UiHelper::~UiHelper()
{
}
void UiHelper::openDialog()
{
	emit this->toOpenDialog();
}
// ===========================================  IQC_ConfigNode  ===========================================
RobotHansNode::RobotHansNode() {
	m_nodeName = "IQC_ConfDlg";
}
RobotHansNode::~RobotHansNode() {
}
QN_RESULT RobotHansNode::apply() {
	QnRtnCode rc;

	UiHelper::instance().openDialog();


	return rc;

}
// ===========================================  RobotHansMoveNode  ===========================================
RobotHansMoveNode::RobotHansMoveNode() {
	m_nodeName = "IQC_Hans";
}
RobotHansMoveNode::~RobotHansMoveNode() {
}
QN_RESULT RobotHansMoveNode::apply() {
	struct HansCtrlCmmd
	{
		bool  bReadActPos;
		bool  bRobMoveJ;
		bool  bRobEnable;
		bool  bReadActPosFlag;
		bool  bRobMoveJFlag;
		string sRobTartgetPos;
	};
	struct DataCtrl
	{
		string  sClientDataRecv;
		string  sClientDataSend;
		string CSClientDataRecv;
	};
	CTCPClient robotMove;
	DataCtrl TenCom;
	HansCtrlCmmd stRobCtrlCmd;
	QnRtnCode rc1, rc2, rc3, rc;
	std::string port1 = "PosPath";
	std::string port2 = "robotIP";
	std::string port3 = "robotPort";
	std::string PosPath1 = "";
	std::string robotIP1 = "";
	int robotPort1 = 0;
	rc1 = hasProperty(port1);
	rc2 = hasProperty(port2);
	rc3 = hasProperty(port3);

	if (rc1.isSuccess() && rc2.isSuccess() && rc3.isSuccess())
	{
		auto data1 = property(port1);
		auto data2 = property(port2);
		auto data3 = property(port3);
		Json::Reader reader;
		Json::Value root;
		if (reader.parse(data1, root, true))
			if (!root.empty())
				if (root.isObject())
					if (root.isMember("value"))
						if (root["value"].isString())
							PosPath1 = root["value"].asCString();
		if (reader.parse(data2, root, true))
			if (!root.empty())
				if (root.isObject())
					if (root.isMember("value"))
						if (root["value"].isString())
							robotIP1 = root["value"].asCString();
		if (reader.parse(data3, root, true))
			if (!root.empty())
				if (root.isObject())
					if (root.isMember("value"))
						if (root["value"].isInt())
							robotPort1 = root["value"].asInt();

	}

	robotMove.CreateSocket();
	u_short ushortRobotPort1 = static_cast<u_short>(robotPort1);
	int connectResult = robotMove.ConnectSocket(robotIP1.c_str(), ushortRobotPort1);
	robotMove.ReadPosFromCSV(PosPath1);
	std::size_t dataSize = robotMove.GetDataSize();
	for (std::size_t i = 0; i < dataSize; i++)
	{
		try {
			const AuoCtrlData& stAutoDataDo = robotMove.GetDataElement(i);

			string command = "MoveJ,0,";
			stRobCtrlCmd.sRobTartgetPos = "";
			for (int j = 0; j < 6; j++)
			{
				command = command + formatFloatValue(stAutoDataDo.rRobTargetPos[j], 2) + ",";
			}

			stRobCtrlCmd.sRobTartgetPos = command + ";";
			TenCom.sClientDataSend = stRobCtrlCmd.sRobTartgetPos;
			robotMove.TcpSend(TenCom.sClientDataSend);
			TenCom.sClientDataRecv = robotMove.TcpReceive();
			bool CheckSignal = true;
			while (CheckSignal)
			{

				string command1 = "ReadActPos,0,;";

				robotMove.TcpSend(command1);
				Sleep(100);
				TenCom.sClientDataRecv = robotMove.TcpReceive();
				std::vector<std::string> dataParts = robotMove.split(TenCom.sClientDataRecv, ',');
				std::vector<double> jValues(6);
				float ActJoint[6];
				bool bRes[6];
				for (int i = 0; i < 6; ++i)
				{
					ActJoint[i] = std::stod(dataParts[i + 2]);
					if (abs(ActJoint[i] - stAutoDataDo.rRobTargetPos[i]) < 0.5)
					{
						bRes[i] = TRUE;
					}
					else
					{
						bRes[i] = FALSE;
					}
				}

				if ((bRes[0] == true) && (bRes[1] == true) && (bRes[2] == true)
					&& (bRes[3] == true) && (bRes[4] == true) && (bRes[5] == true))
				{
					CheckSignal = FALSE;
				}
				else
				{
					CheckSignal = TRUE;
				}

				Sleep(100);
			}

		}
		catch (const std::out_of_range& e) {
			return rc = -1;
			// Handle error
		}
	}
	

	return rc;

}
// ===========================================  RobotScanNode  ===========================================
RobotScanNode::RobotScanNode() {
	m_nodeName = "RobotScan";
}
RobotScanNode::~RobotScanNode() {
}
QN_RESULT RobotScanNode::apply() {
	QnRtnCode rc1, rc2, rc3, rc;
	CTCPClient robotMove, turnTableMove;

	int rct = turnTableMove.ConnectTurnTable();
	struct HansCtrlCmmd
	{
		bool  bReadActPos;
		bool  bRobMoveJ;
		bool  bRobEnable;
		bool  bReadActPosFlag;
		bool  bRobMoveJFlag;
		string sRobTartgetPos;
	};
	struct DataCtrl
	{
		string  sClientDataRecv;
		string  sClientDataSend;
		string CSClientDataRecv;
	};

	DataCtrl TenCom;
	HansCtrlCmmd stRobCtrlCmd;

	std::string port1 = "PosPath";
	std::string port2 = "robotIP";
	std::string port3 = "robotPort";
	std::string PosPath1 = "";
	std::string robotIP1 = "";
	int robotPort1 = 0;
	rc1 = hasProperty(port1);
	rc2 = hasProperty(port2);
	rc3 = hasProperty(port3);

	if (rc1.isSuccess() && rc2.isSuccess() && rc3.isSuccess())
	{
		auto data1 = property(port1);
		auto data2 = property(port2);
		auto data3 = property(port3);
		Json::Reader reader;
		Json::Value root;
		if (reader.parse(data1, root, true))
			if (!root.empty())
				if (root.isObject())
					if (root.isMember("value"))
						if (root["value"].isString())
							PosPath1 = root["value"].asCString();
		if (reader.parse(data2, root, true))
			if (!root.empty())
				if (root.isObject())
					if (root.isMember("value"))
						if (root["value"].isString())
							robotIP1 = root["value"].asCString();
		if (reader.parse(data3, root, true))
			if (!root.empty())
				if (root.isObject())
					if (root.isMember("value"))
						if (root["value"].isInt())
							robotPort1 = root["value"].asInt();

	}

	robotMove.CreateSocket();
	u_short ushortRobotPort1 = static_cast<u_short>(robotPort1);
	int connectResult = robotMove.ConnectSocket(robotIP1.c_str(), ushortRobotPort1);
	robotMove.ReadPosFromCSV(PosPath1);
	std::size_t dataSize = robotMove.GetDataSize();
	for (std::size_t i = 0; i < dataSize; i++)
	{
		try {
			const AuoCtrlData& stAutoDataDo = robotMove.GetDataElement(i);

			string command = "MoveJ,0,";
			stRobCtrlCmd.sRobTartgetPos = "";
			for (int j = 0; j < 6; j++)
			{
				command = command + formatFloatValue(stAutoDataDo.rRobTargetPos[j], 2) + ",";
			}

			stRobCtrlCmd.sRobTartgetPos = command + ";";
			TenCom.sClientDataSend = stRobCtrlCmd.sRobTartgetPos;
			robotMove.TcpSend(TenCom.sClientDataSend);
			TenCom.sClientDataRecv = robotMove.TcpReceive();
			bool CheckSignal = true;
			while (CheckSignal)
			{

				string command1 = "ReadActPos,0,;";

				robotMove.TcpSend(command1);
				Sleep(100);
				TenCom.sClientDataRecv = robotMove.TcpReceive();
				std::vector<std::string> dataParts = robotMove.split(TenCom.sClientDataRecv, ',');
				std::vector<double> jValues(6);
				float ActJoint[6];
				bool bRes[6];
				for (int i = 0; i < 6; ++i)
				{
					ActJoint[i] = std::stod(dataParts[i + 2]);
					if (abs(ActJoint[i] - stAutoDataDo.rRobTargetPos[i]) < 0.5)
					{
						bRes[i] = TRUE;
					}
					else
					{
						bRes[i] = FALSE;
					}
				}

				if ((bRes[0] == true) && (bRes[1] == true) && (bRes[2] == true)
					&& (bRes[3] == true) && (bRes[4] == true) && (bRes[5] == true))
				{
					CheckSignal = FALSE;
				}
				else
				{
					CheckSignal = TRUE;
				}

				Sleep(100);
			}

			//check turnTable status
			turnTableMove.loadAngleCompensationValue();
			bool rcTable = turnTableMove.ReadAndAdjustAngle(stAutoDataDo.rTableAngle, turnTableMove.DegreeCom);
			
		}
		catch (const std::out_of_range& e) {
			return rc = -1;
			// Handle error
		}
	}

	turnTableMove.CloseAndReleaseResources();


	return rc;

}
// ===========================================  TurnTableRunNode  ===========================================
TrunTableNode::TrunTableNode() {
	m_nodeName = "IQC_TurnTable";
	turnTableMove.loadAngleCompensationValue();
}
TrunTableNode::~TrunTableNode() {
	
}
QN_RESULT TrunTableNode::apply() {
	
	int rc1 = turnTableMove.ConnectTurnTable();

	QnRtnCode rc,rc3;
	std::string port1 = "TurnTableAngle";
	float TurnTableAngle = 0;
	rc3 = hasProperty(port1);
	if (rc3.isSuccess())
	{
		auto data1 = property(port1);
		Json::Reader reader;
		Json::Value root;
		if (reader.parse(data1, root, true))
			if (!root.empty())
				if (root.isObject())
					if (root.isMember("value"))
						if (root["value"].isNumeric())
							TurnTableAngle = root["value"].asFloat();
	}
	turnTableMove.loadAngleCompensationValue();
	bool rc2 = turnTableMove.ReadAndAdjustAngle(TurnTableAngle, turnTableMove.DegreeCom);

	turnTableMove.CloseAndReleaseResources();

	return rc;
	
	

}
// ===========================================  IQC_ScanNode  ===========================================
IQCScanNode::IQCScanNode() {
	m_nodeName = "IQC_Scan";
	iqcClient.loadAngleCompensationValue();
}
IQCScanNode::~IQCScanNode() {
	//
}
QN_RESULT IQCScanNode::apply() 
{
	QnRtnCode rc1, rc2, rc3, rc4, rc5, rc, rc6, rc7, rc8;
	struct HansCtrlCmmd
	{
		bool  bReadActPos;
		bool  bRobMoveJ;
		bool  bRobEnable;
		bool  bReadActPosFlag;
		bool  bRobMoveJFlag;
		string sRobTartgetPos;
	};
	struct DataCtrl
	{
		string  sClientDataRecv;
		string  sClientDataSend;
		string CSClientDataRecv;
	};
	
	HansCtrlCmmd stRobCtrlCmd;
	DataCtrl TenCom, OptimCom;

	
	std::string port1 = "PosPath";
	std::string port2 = "robotIP";
	std::string port3 = "robotPort";
	std::string port4 = "scannerIP";
	std::string port5 = "scannerPort";
	std::string port7 = "projectPath";
	std::string PosPath1 = "";
	std::string robotIP1 = "";
	int robotPort1 = 0;
	std::string scannerIP1 = "";
	int scannerPort1 = 0;
	std::string projectPath1 = "";
	rc1 = hasProperty(port1);
	rc2 = hasProperty(port2);
	rc3 = hasProperty(port3);
	rc4 = hasProperty(port4);
	rc5 = hasProperty(port5);
	rc7 = hasProperty(port7);
	
	// ===================  Connect Robot  ========================
	if (rc1.isSuccess() && rc2.isSuccess() && rc3.isSuccess())
	{
		auto data1 = property(port1);
		auto data2 = property(port2);
		auto data3 = property(port3);
		Json::Reader reader;
		Json::Value root;
		if (reader.parse(data1, root, true))
			if (!root.empty())
				if (root.isObject())
					if (root.isMember("value"))
						if (root["value"].isString())
							PosPath1 = root["value"].asCString();
		if (reader.parse(data2, root, true))
			if (!root.empty())
				if (root.isObject())
					if (root.isMember("value"))
						if (root["value"].isString())
							robotIP1 = root["value"].asCString();
		if (reader.parse(data3, root, true))
			if (!root.empty())
				if (root.isObject())
					if (root.isMember("value"))
						if (root["value"].isInt())
							robotPort1 = root["value"].asInt();

	}
	iqcClient.CreateSocket();
	u_short ushortRobotPort1 = static_cast<u_short>(robotPort1);
	int connectResult = iqcClient.ConnectSocket(robotIP1.c_str(), ushortRobotPort1);
	
	// ===================  Connect 5MP  ========================
	
	if (rc4.isSuccess() && rc5.isSuccess() && rc7.isSuccess())
	{
		auto data4 = property(port4);
		auto data5 = property(port5);
		auto data7 = property(port7);
		
		Json::Reader reader;
		Json::Value root;
		if (reader.parse(data4, root, true))
			if (!root.empty())
				if (root.isObject())
					if (root.isMember("value"))
						if (root["value"].isString())
							scannerIP1 = root["value"].asCString();
		if (reader.parse(data5, root, true))
			if (!root.empty())
				if (root.isObject())
					if (root.isMember("value"))
						if (root["value"].isInt())
							scannerPort1 = root["value"].asInt();
		if (reader.parse(data7, root, true))
			if (!root.empty())
				if (root.isObject())
					if (root.isMember("value"))
						if (root["value"].isString())
							projectPath1 = root["value"].asCString();


	}
	optimScan.CreateSocket();
	u_short ushortScannerPort2 = static_cast<u_short>(scannerPort1);
	connectResult = optimScan.ConnectSocket(scannerIP1.c_str(), ushortScannerPort2);

	//check 5MP status
	bool CheckSignalOptim = true;
	int iOptimFed = 0;
	
	OptimCom.sClientDataSend = "B:";
	OptimCom.sClientDataSend = OptimCom.sClientDataSend + projectPath1;
	OptimCom.sClientDataRecv = "";
	optimScan.TcpSend(OptimCom.sClientDataSend);
	iOptimFed = optimScan.CheckOptimScan();
	if (iOptimFed < 0)
	{
		return rc6;
	}

	// ===================  Connect TurnTable  ========================
	rc8 = iqcClient.ConnectTurnTable();

	// ===================  Work starts  ========================
	iqcClient.ReadPosFromCSV(PosPath1);
	std::size_t dataSize = iqcClient.GetDataSize();
	for (std::size_t i = 0; i < dataSize; i++)
	{
		try {
			const AuoCtrlData& stAutoDataDo = iqcClient.GetDataElement(i);

			string command = "MoveJ,0,";
			stRobCtrlCmd.sRobTartgetPos = "";
			for (int j = 0; j < 6; j++)
			{
				command = command + formatFloatValue(stAutoDataDo.rRobTargetPos[j], 2) + ",";
			}

			stRobCtrlCmd.sRobTartgetPos = command + ";";
			TenCom.sClientDataSend = stRobCtrlCmd.sRobTartgetPos;
			iqcClient.TcpSend(TenCom.sClientDataSend);
			TenCom.sClientDataRecv = iqcClient.TcpReceive();
			//check robot status
			bool CheckSignalRobot = true;
			while (CheckSignalRobot)
			{
				
				string command1 = "ReadActPos,0,;";

				iqcClient.TcpSend(command1);
				Sleep(100);
				TenCom.sClientDataRecv = iqcClient.TcpReceive();
				std::vector<std::string> dataParts = iqcClient.split(TenCom.sClientDataRecv, ',');
				std::vector<double> jValues(6);
				float ActJoint[6];
				bool bRes[6];
				for(int i = 0; i < 6; ++i)
				{
					ActJoint[i] = std::stod(dataParts[i + 2]);
					if (abs(ActJoint[i] - stAutoDataDo.rRobTargetPos[i]) < 0.5)
					{
						bRes[i] = TRUE;
					}
					else
					{
						bRes[i] = FALSE;
					}
				}

				if ((bRes[0] == true) && (bRes[1] == true) && (bRes[2] == true)
					&& (bRes[3] == true) && (bRes[4] == true) && (bRes[5] == true))
				{
					CheckSignalRobot = FALSE;
				}
				else
				{
					CheckSignalRobot = TRUE;
				}

				Sleep(100);
			}
			
			//check turnTable status
			bool rcTable = iqcClient.ReadAndAdjustAngle(stAutoDataDo.rTableAngle, iqcClient.DegreeCom);

			if (stAutoDataDo.bIsTake == TRUE)
			{
				OptimCom.sClientDataSend = "S";
				OptimCom.sClientDataRecv = "";
				iOptimFed = 0;
				optimScan.TcpSend(OptimCom.sClientDataSend);
				bool isFinished = true;
				while (isFinished)
				{
					int receiveMsg = optimScan.CheckOptimScan();

					if (receiveMsg == 2)
					{
						break;
					}
					
					else
					{
						Sleep(100);
						continue;
					}
				}
			}
			if (stAutoDataDo.bIsFlowOver == TRUE)
			{
				Sleep(200);
				OptimCom.sClientDataSend = "M";
				OptimCom.sClientDataRecv = "";
				iOptimFed = 0;
				optimScan.TcpSend(OptimCom.sClientDataSend);
				bool isFinished = true;
				while (isFinished)
				{
					int receiveMsg = optimScan.CheckOptimScan();

					if (receiveMsg == 2)
					{
						break;
					}

					else
					{
						Sleep(100);
						continue;
					}
				}
			}

		}
		catch (const std::out_of_range& e) 
		{
			return rc;
		}
	}
	iqcClient.CloseAndReleaseResources();
	return rc;

}
// ===========================================  IQC_InspectionNode  ===========================================
IqcInspectionNode::IqcInspectionNode() {
	m_nodeName = "IQC_Inspection";
}
IqcInspectionNode::~IqcInspectionNode() {
}
QN_RESULT IqcInspectionNode::apply() {

	QnRtnCode rc1, rc2, rc3, rc4, rc;
	std::string port1 = "stlPath";
	std::string port2 = "reportPath";
	std::string port3 = "exePath";
	std::string port4 = "SNIprojPath";


	std::string stlPath1 = "";
	std::string reportPath1 = "";
	std::string exePathPath1 = "";
	std::string SNIprojPath1 = "";

	rc1 = hasProperty(port1);
	rc2 = hasProperty(port2);
	rc3 = hasProperty(port3);
	rc4 = hasProperty(port4);
	//check inputs and properties,
	if (rc1.isSuccess() && rc2.isSuccess() && rc3.isSuccess() && rc4.isSuccess())
	{
		auto data1 = property(port1);
		auto data2 = property(port2);
		auto data3 = property(port3);
		auto data4 = property(port4);


		Json::Reader reader;
		Json::Value root;
		if (reader.parse(data1, root, true))
			if (!root.empty())
				if (root.isObject())
					if (root.isMember("value"))
						if (root["value"].isString())
							stlPath1 = root["value"].asCString();
		if (reader.parse(data2, root, true))
			if (!root.empty())
				if (root.isObject())
					if (root.isMember("value"))
						if (root["value"].isString())
							reportPath1 = root["value"].asCString();
		if (reader.parse(data3, root, true))
			if (!root.empty())
				if (root.isObject())
					if (root.isMember("value"))
						if (root["value"].isString())
							exePathPath1 = root["value"].asCString();
		if (reader.parse(data4, root, true))
			if (!root.empty())
				if (root.isObject())
					if (root.isMember("value"))
						if (root["value"].isString())
							SNIprojPath1 = root["value"].asCString();

	}
	std::string mode = "1";
	QString reportPathQ1 = QString::fromStdString(reportPath1);
	checkAndCreateFile(reportPathQ1);
	
	std::string command = exePathPath1 + " \"" + SNIprojPath1 + "\" \"" + stlPath1 + "\" \"" + reportPath1 + "\" \"" + mode + "\"";

	system(command.c_str());
	return rc;

}
