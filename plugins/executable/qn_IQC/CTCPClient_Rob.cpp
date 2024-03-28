#include "CTCPClient_Rob.h" // Make sure this is your custom header
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <QFile>
#include <QTextStream>
#include <QStringList>

// Link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")



void CTCPClient::CreateSocket() {
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 2);
	int err = WSAStartup(wVersionRequested, &wsaData);

	if (err != 0) {
		std::cerr << "WSAStartup failed with error: " << err << '\n';
		return;
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		std::cerr << "Incorrect Winsock version\n";
		WSACleanup();
		return;
	}

	sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockClient == INVALID_SOCKET) {
		std::cerr << "Socket creation failed with error: " << WSAGetLastError() << '\n';
		WSACleanup();
		return;
	}

	std::cout << "Socket successfully created.\n";
}
int CTCPClient::ConnectSocket(const char* sIPAddress, u_short usPort) {
	sockaddr_in addrSrvClient;
	int result = inet_pton(AF_INET, sIPAddress, &addrSrvClient.sin_addr);

	if (result != 1) {
		std::cerr << "inet_pton failed with error: " << WSAGetLastError() << '\n';
		return -1; // Return an error code
	}

	addrSrvClient.sin_family = AF_INET;
	addrSrvClient.sin_port = htons(usPort);

	int iRet = connect(sockClient, reinterpret_cast<SOCKADDR*>(&addrSrvClient), sizeof(SOCKADDR));
	if (iRet == SOCKET_ERROR) {
		std::string sFeedback;
		DwordToString(sFeedback, WSAGetLastError());
		std::cerr << "Connect error: " << sFeedback << '\n';
		return -1;
	}

	return iRet;
}
void CTCPClient::TcpSend(const std::string& sSendData) {
	send(sockClient, sSendData.c_str(), static_cast<int>(sSendData.length()), 0);
}
std::string CTCPClient::TcpReceive() {
	const int bufLen = 256;
	char recvBuf[bufLen] = { 0 };
	int size = recv(sockClient, recvBuf, bufLen - 1, 0);

	if (size > 0) {
		recvBuf[size] = '\0'; // Null-terminate the string
		return std::string(recvBuf);
	}

	return std::string();
}
void CTCPClient::TcpClose() {
	closesocket(sockClient);
}
//------------------write Position--------------------------
void CTCPClient::WritePositionToFile(std::ofstream& file, const AuoCtrlData& data) {
	
	for (int i = 0; i < 6; ++i) {
		file << data.rRobTargetPos[i];
		if (i < 5) file << ","; // No comma after the last J position value
	}
	// Additional data can be appended here as necessary

	file << "," << data.rTableAngle
		<< "," << data.bIsTake
		<< "," << data.bIsFlowOver
		<< "\n";
	
}
void CTCPClient::removeLastEntryFromCSV(const std::string& filename)
{
	QString qFilename = QString::fromStdString(filename);
	QFile file(qFilename);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return;
	}
	QStringList lines;
	QTextStream in(&file);
	while (!in.atEnd()) {
		QString line = in.readLine();
		if (!line.isNull()) {
			lines.push_back(line);
		}
	}
	file.close();
	if (!lines.isEmpty()) {
		lines.removeLast(); // Remove the last line
	}
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {

		return;
	}
	QTextStream out(&file);
	for (const QString &line : qAsConst(lines)) {
		out << line << "\n";
	}
	file.close();
}
//------------------TurnTableClient--------------------------
int CTCPClient::ConnectTurnTable()
{
	
	RTUctx = modbus_new_rtu("COM5", 38400, 'N', 8, 1);
	if (RTUctx == NULL)
	{
		std::cout << "Unable to create the libmodbus context\n";
		return -1;
	}

	CmdRet = modbus_set_slave(RTUctx, 1);
	CmdRet = modbus_connect(RTUctx);
	CmdRet = modbus_write_bit(RTUctx, 288, STB_OFF);
	CmdRet = modbus_write_bit(RTUctx, 96, SRVO_ON);
	CmdRet = modbus_write_register(RTUctx, 17428, AbsMove);
	CmdRet = modbus_read_registers(RTUctx, 17429, 1, InvidBlockNo);
	CmdRet = modbus_read_registers(RTUctx, 17430, 1, DataBlocNO);
	CmdRet = modbus_read_bits(RTUctx, 160, 4, DataReady);
}
bool CTCPClient::ReadAndAdjustAngle(float targetAngle, float angleCompensation)
{
	CmdRet = modbus_read_registers(RTUctx, 16898, 3, DataEnco);
	if (DataEnco[2] != 65535)
	{
		bEncoErr = FALSE;
		rTurnTableActAngle = (DataEnco[2] * 8388608 + (DataEnco[0] + DataEnco[1] * 65535)) / (8388608 * 50 / 360.0) - angleCompensation;

	}
	else
	{
		rTurnTableActAngle = 0.0;
		bEncoErr = TRUE;
	}
	uint16_t ActPos[4];
	ActPos[0] = 0;
	ActPos[1] = 512;
	ActPos[2] = (targetAngle + angleCompensation) * 150 ;
	ActPos[3] = 0;
	CmdRet = modbus_write_registers(RTUctx, 18440, 4, ActPos);

	CmdRet = modbus_write_bit(RTUctx, 288, STB_ON);
	Sleep(500);
	while (CmdRet > 0)
	{
		
		CmdRet = modbus_read_registers(RTUctx, 16898, 3, DataEnco);
		if (DataEnco[2] != 65535)
		{
			bEncoErr = FALSE;
			rTurnTableActAngle = (DataEnco[2] * 8388608 + (DataEnco[0] + DataEnco[1] * 65535)) / (8388608 * 50 / 360.0) - angleCompensation;
		}
		else
		{
			rTurnTableActAngle = 0.0;
			bEncoErr = FALSE;
		}
		CmdRet = modbus_read_bits(RTUctx, 160, 4, DataReady);
		if ((abs(rTurnTableActAngle - targetAngle) < 0.1) && (DataReady[2] == 1))
		{
			CmdRet = modbus_write_bit(RTUctx, 288, STB_OFF);
			bTableArrived = TRUE;
			break;
		}
		Sleep(100);

	}

	return 0;
}
void CTCPClient::CloseAndReleaseResources()
{
	modbus_close(RTUctx);
	modbus_free(RTUctx);
	data.clear();
}
//------------------Read Position--------------------------
int CTCPClient::ReadPosFromCSV(std::string &fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open()) {
		return 1;
	}
	std::string line;
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string token;
		AuoCtrlData entry;
		int index = 0;

		while (std::getline(ss, token, ',')) {
			if (index < 6) {
				entry.rRobTargetPos[index] = std::stof(token);
			}
			else if (index == 6) {
				entry.rTableAngle = std::stof(token);
			}
			else if (index == 7) {
				entry.bIsTake = (token == "1");
			}
			else if (index == 8) {
				entry.bIsFlowOver = (token == "1");
			}
			index++;
		}

		data.push_back(entry);
	}
	file.close();
}
std::size_t CTCPClient::GetDataSize() const 
{
	return data.size();
}
//------------------OptimuScanClient--------------------------
int CTCPClient::CheckOptimScan()
{
	int iOptimFed = 0;
	bool CheckSignalOptim = true;
	std::string sClientDataRecv = "";
	while (CheckSignalOptim)
	{
		sClientDataRecv = TcpReceive();
		if (sClientDataRecv == "Start")
		{
			iOptimFed = 1;
			CheckSignalOptim = false;
		}
		else if (sClientDataRecv == "Ok")
		{
			iOptimFed = 2;
			CheckSignalOptim = false;

		}
		else if (sClientDataRecv == "Err:NoProject")
		{
			iOptimFed = -1;
			CheckSignalOptim = false;
		}
		else if (sClientDataRecv == "Err:NoDogData")
		{
			iOptimFed = -2;
			CheckSignalOptim = false;
		}
		else if (sClientDataRecv == "Err:Fail")
		{
			iOptimFed = -3;
			CheckSignalOptim = false;
		}
		else if (sClientDataRecv == "Err:NoCalib")
		{
			iOptimFed = -4;
			CheckSignalOptim = false;
		}
		else if (sClientDataRecv == "Err:Device")
		{
			iOptimFed = -5;
			CheckSignalOptim = false;
		}
		else if (sClientDataRecv == "Err:CapFail")
		{
			iOptimFed = -6;
			CheckSignalOptim = false;
		}
		else if (sClientDataRecv == "Err:NoData")
		{
			iOptimFed = -7;
			CheckSignalOptim = false;
		}
		else if (sClientDataRecv == "Err:NoRef")
		{
			iOptimFed = -8;
			CheckSignalOptim = false;
		}
		else if (sClientDataRecv == "Err:MatchFail")
		{
			iOptimFed = -9;
			CheckSignalOptim = false;
		}
		else
		{
			CheckSignalOptim = true;
		}
	}
	return iOptimFed;
}

void CTCPClient::loadAngleCompensationValue()
{
	QFile file("angle_compensation_value.txt");
	if (file.open(QIODevice::ReadOnly)) 
	{
		QTextStream stream(&file);
		QString line = stream.readLine();
		DegreeCom = line.toFloat();
		file.close();
	}
}



