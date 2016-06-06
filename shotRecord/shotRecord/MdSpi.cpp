#include "MdSpi.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


using namespace std;

extern CThostFtdcMdApi *pUserApi;

extern char FRONT_ADDR[];
extern TThostFtdcBrokerIDType BROKER_ID;
extern TThostFtdcInvestorIDType INVESTOR_ID;
extern TThostFtdcPasswordType PASSWORD;
extern char* ppInstrumentID[];
extern int iInstrumentID;
extern int iRequestID;

void MdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	IsErrorRspInfo(pRspInfo);
}

void MdSpi::OnFrontDisconnected(int nReason)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	cerr << "--->>> Reason = " << nReason << endl;
}

void MdSpi::OnHeartBeatWarning(int nTimeLapse)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	cerr << "--->>> nTimerLapse = " << nTimeLapse << endl;
}

void MdSpi::OnFrontConnected()
{
	//cout << "服务器连接成功！" << endl;
	cerr << "--->>> " << __FUNCTION__ << endl;
	///用户登录请求
	ReqUserLogin();
}

void MdSpi::ReqUserLogin()
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, BROKER_ID);
	strcpy_s(req.UserID, INVESTOR_ID);
	strcpy_s(req.Password, PASSWORD);
	int iResult = pUserApi->ReqUserLogin(&req, ++iRequestID);
	cerr << "--->>> 发送用户登录请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
}

void MdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
	CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << __FUNCTION__ << endl;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		///获取当前交易日
		cerr << "--->>> 获取当前交易日 = " << pUserApi->GetTradingDay() << endl;
		// 请求订阅行情
		SubscribeMarketData();
	}
}

void MdSpi::SubscribeMarketData()
{
	int iResult = pUserApi->SubscribeMarketData(ppInstrumentID, iInstrumentID);
	cerr << "--->>> 发送行情订阅请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
}

void MdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << __FUNCTION__ << endl;
}

void MdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << __FUNCTION__ << endl;
}

void MdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	//cerr << __FUNCTION__ << endl;
	cout << pDepthMarketData->InstrumentID << '\t' << pDepthMarketData->AskPrice1 << '\t' << pDepthMarketData->BidPrice1 << endl;
	//ifstream fin("d:\data\data.text");
	stringstream ss1,ss2,ss3,ss4,ss5;
	ss1 << pDepthMarketData->InstrumentID;
	ss2 << pDepthMarketData->TradingDay;
	ss3 << pDepthMarketData->UpdateTime;
	ss4 << pDepthMarketData->AskPrice1;
	ss5 << pDepthMarketData->BidPrice1;
	ofstream fin("d:\data\\data.txt",ios::out|ios::app);

	fin << ss1.str() << "  " << ss2.str() << "  " << ss3.str() << "  " << ss4.str() << "  " << ss5.str() <<endl;
	fin.close();
}

bool MdSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
	// 如果ErrorID != 0, 说明收到了错误的响应
	bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (bResult)
		cerr << "--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
	return bResult;
}