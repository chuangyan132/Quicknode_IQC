#ifndef CTCPCLIENT_ROB_H
#define CTCPCLIENT_ROB_H

#include <string>
#include <vector>
#include <winsock2.h>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include "structInfo.h"
#include "modbus-rtu.h"

// Make sure to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

#define STB_ON 1
#define STB_OFF 0
#define SRVO_ON 1
#define SRVO_OFF 0
#define AbsMove 2



class CTCPClient {
private:
	SOCKET sockClient;

public:
	CTCPClient() : sockClient(INVALID_SOCKET) {}
	~CTCPClient() {
		if (sockClient != INVALID_SOCKET) {
			closesocket(sockClient);
			WSACleanup();
		}
	}

	void DwordToString(std::string &outstr, DWORD dwValue) {
		char szHex[10];
		sprintf_s(szHex, "0x%08X", dwValue); // Use sprintf_s for safety
		outstr = szHex;
	}

	void CreateSocket();
	int ConnectSocket(const char* sIPAddress, u_short usPort);
	void TcpSend(const std::string& sSendData);
	std::string TcpReceive();
	void TcpClose();
	void WritePositionToFile(std::ofstream& file, const AuoCtrlData& data);
	void removeLastEntryFromCSV(const std::string& filename);
	inline std::string GetFormattedDateTime() {
		std::time_t t = std::time(nullptr);
		std::tm tm;
		// Use the appropriate function for your platform
		// For POSIX platforms you might use localtime_r instead of localtime_s
		localtime_s(&tm, &t);
		std::ostringstream oss;
		oss << std::put_time(&tm, "%Y%m%d_%H%M");
		return oss.str();
	}
	static std::vector<std::string> split(const std::string &s, char delimiter) {
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(s);
		while (std::getline(tokenStream, token, delimiter)) {
			tokens.push_back(token);
		}
		return tokens;
	}

	static std::string formatFloatValue(float val, int fixed) {
		std::string str = std::to_string(val);
		auto decimalPos = str.find(".");
		if (decimalPos != std::string::npos && decimalPos + fixed + 1 < str.size()) {
			return str.substr(0, decimalPos + fixed + 1);
		}
		return str; // If the decimal point is not found or the string is too short, return the original string
	}
	//------------------TurnTableClient--------------------------
	int ConnectTurnTable();
	void CloseAndReleaseResources();
	bool ReadAndAdjustAngle(float targetAngle, float angleCompensation);
	//------------------Read Position--------------------------
	int ReadPosFromCSV(std::string &fileName);
	std::size_t GetDataSize() const;
	const AuoCtrlData& GetDataElement(std::size_t index) const {
		if (index < data.size()) {
			return data[index];
		}
		// Handle the case where the index is out of bounds
		throw std::out_of_range("Index is out of bounds.");
	}
	int CheckOptimScan();
	void loadAngleCompensationValue();
	float DegreeCom = 0;
	


private:
	
	//------------------TurnTableClient--------------------------

	int CmdRet;
	modbus_t *RTUctx;
	bool bSrvoRun = FALSE;
	float rTurnTableActAngle = 0.0;
	
	bool bEncoErr = FALSE;
	bool bRobArrived = FALSE, bOptimCmd = FALSE, bTableArrived = FALSE;
	uint8_t DataReady[4];
	uint16_t InvidBlockNo[1];
	uint16_t  DataBlocNO[1];
	uint16_t DataEnco[3];
	std::vector<AuoCtrlData> data;

};

#endif // CTCPCLIENT_ROB_H

