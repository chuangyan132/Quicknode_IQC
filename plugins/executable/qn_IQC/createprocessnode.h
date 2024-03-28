/*!
* @brief   
* @project qn_einstarscan
* @file    createprocessnode.h
* @author  sunduo
* @email   sunduo@shining3d.com
* @license 
*     Copyright(C) shining3d. All rights reserved.
* @versions 
*     V0.1-sunduo 2023-08-24 11:02
*/
//==============================================================================
#ifndef QN_HANSROBOT_CREATEPROCESSNODE_H
#define QN_HANSROBOT_CREATEPROCESSNODE_H
//==============================================================================

#include <QFile>
#include <QProcess>
#include <QDebug>
#include "CTCPClient_Rob.h"
#include <QString>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include "../include/basenode.h"


class RobotHansNode : public /*QObject,*/ BaseNode{
  public:
	  RobotHansNode();
    virtual  ~RobotHansNode();

    virtual QN_RESULT apply() override;

  private:
    std::string m_nodeName;
};

class RobotHansMoveNode : public /*QObject,*/ BaseNode {
public:
	RobotHansMoveNode();
	virtual  ~RobotHansMoveNode();

	virtual QN_RESULT apply() override;
	auto formatFloatValue(float val, int fixed)
	{
		auto str = std::to_string(val);
		return str.substr(0, str.find(".") + fixed + 1);
	}

private:
	std::string m_nodeName;
};

class TrunTableNode : public /*QObject,*/ BaseNode {
public:
	TrunTableNode();
	virtual  ~TrunTableNode();

	virtual QN_RESULT apply() override;
	CTCPClient turnTableMove;

private:
	std::string m_nodeName;
};

class IQCScanNode : public /*QObject,*/ BaseNode {
public:
	IQCScanNode();
	virtual  ~IQCScanNode();

	virtual QN_RESULT apply() override;
	auto formatFloatValue(float val, int fixed)
	{
		auto str = std::to_string(val);
		return str.substr(0, str.find(".") + fixed + 1);
	}
	
	

private:
	CTCPClient iqcClient, optimScan, tableClient;
	std::string m_nodeName;
	bool bRobArrived = FALSE, bOptimCmd = FALSE, bTableArrived = FALSE;
	
	bool bPosRun = FALSE, bPosRead = FALSE;
	float rTurnTableActAngle = 0.0;
	float rTurnTableTarAngle = 0.0;
	bool bSrvoRun = FALSE;
	
	
};

class IqcInspectionNode : public /*QObject,*/ BaseNode {
public:
	IqcInspectionNode();
	virtual  ~IqcInspectionNode();

	virtual QN_RESULT apply() override;
	void checkAndCreateFile(const QString& filePath) {
		QFile file(filePath);
		if (!file.exists()) {
			file.open(QIODevice::WriteOnly); // Create the file
			file.close();
		}
	}


private:
	std::string m_nodeName;

};
class RobotScanNode : public /*QObject,*/ BaseNode {
public:
	RobotScanNode();
	virtual  ~RobotScanNode();

	virtual QN_RESULT apply() override;
	auto formatFloatValue(float val, int fixed)
	{
		auto str = std::to_string(val);
		return str.substr(0, str.find(".") + fixed + 1);
	}

private:
	std::string m_nodeName;
};
class QDialog;
class DialogManager : public QObject {
	Q_OBJECT
public:
	static DialogManager *instance();
	bool dialogIsClosed();
public slots:
	void onOpenDialog();
signals:
	void dialogClosed();

private:
	DialogManager(QObject *parent = nullptr);
	~DialogManager();
	bool m_dialogIsClosed = false;
	static DialogManager *m_instance;
	QDialog *m_dialog;
};

class UiHelper : public QObject {
	Q_OBJECT
public:
	static UiHelper &instance();
	UiHelper(QObject *parent = nullptr);
	~UiHelper();

	void openDialog();

signals:
	void toOpenDialog();
};


//==============================================================================
#endif // QN_HANSROBOT_CREATEPROCESSNODE_H
//==============================================================================
