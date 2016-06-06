// shotRecord.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"
#include "ThostFtdcUserApiDataType.h"
#include "ThostFtdcUserApiStruct.h"

#include "MdSpi.h"

using namespace std;

CThostFtdcMdApi* pUserApi;

char FRONT_ADDR[] = "tcp://180.166.65.120:41213";
TThostFtdcBrokerIDType	BROKER_ID = "8086";				// 经纪公司代码
TThostFtdcInvestorIDType INVESTOR_ID = "00090000001";			// 投资者代码
//TThostFtdcInvestorIDType INVESTOR_ID = "00090000336";	
//TThostFtdcPasswordType  PASSWORD = "888888";			// 用户密码

//char FRONT_ADDR[] = "tcp://218.202.237.33:10012";
//TThostFtdcBrokerIDType	BROKER_ID = "9999";				// 经纪公司代码
//TThostFtdcInvestorIDType INVESTOR_ID = "060850";			// 投资者代码
TThostFtdcPasswordType  PASSWORD = "maoheng0";			// 用户密码

char *ppInstrumentID[] = { "IF1606"};			// 行情订阅列表
int iInstrumentID = 1;									// 行情订阅数量

														// 请求编号
int iRequestID = 0;

int main()
{
	// 初始化UserApi
	pUserApi = CThostFtdcMdApi::CreateFtdcMdApi();			// 创建UserApi
	CThostFtdcMdSpi* pUserSpi = new MdSpi();
	pUserApi->RegisterSpi(pUserSpi);						// 注册事件类
	pUserApi->RegisterFront(FRONT_ADDR);					// connect
	pUserApi->Init();
	//cout << "登陆0" << endl;
	pUserApi->Join();

	//cout << "登陆1" << endl;
	/*//pUserApi->Join();
	//pUserSpi->OnFrontConnected();
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy_s(req.BrokerID, BROKER_ID);
	strcpy_s(req.UserID, INVESTOR_ID);
	strcpy_s(req.Password, PASSWORD);
	int iResult = pUserApi->ReqUserLogin(&req, ++iRequestID);
	//cerr << "--->>> 发送用户登录请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
	cout << iResult << endl;	// 0发送成功-1因网络原因发送失败-2未处理请求队列总数量超限-3每秒发送请求数量超限
	cout << "登陆2" << endl;*/

	system("pause");

	return 0;
}