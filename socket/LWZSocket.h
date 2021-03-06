/**********************************************************************************
文 件 名:LWZSocket.h
描    述:自定义socket类
作    者:卢磊
时    间:2017/4/14
修    改:
**********************************************************************************/

#ifndef __LWZSOCKET_H__
#define __LWZSOCKET_H__

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstdio>
#include <cstring>
#include "../public/common.h"

using namespace std;

class CLWZSocket
{
public:
	//定义类中的局部类型
	//1. 用户处理函数类型
	typedef void* (*HAND_FUNC)(void*);

	//2. 线程处理函数参数类型
	typedef class FUNC_PARAM{
	public:
		FUNC_PARAM(){
			sockClient = 0;
			pUserData = NULL;
			pUserFunc = NULL;
		}

		int GetSocket(){return sockClient;}
		void* GetUserData(){return pUserData;}
		HAND_FUNC GetUserFunc(){return pUserFunc;}
		void SetSocket(int nSocket){sockClient = nSocket;}
		void SetUserData(void* pData){pUserData = pData;};
		void SetUserFunc(HAND_FUNC pFunc){pUserFunc = pFunc;}
	private:
		int sockClient;

		//用户数据
		void* pUserData;

		//用户处理函数
		HAND_FUNC pUserFunc;
	}stFuncParam;

	CLWZSocket();
	~CLWZSocket();

	//外部接口
	bool InitServer(int nPort = 6000, const char* pszIP = "127.0.0.1");
	bool CreateServer();
	bool Accept(HAND_FUNC pUserFunc);
	bool InitClient(int nPort = 6000, const char* pszIP = "127.0.0.1");
	bool Connect();
	int GetFarSocket();
	int GetLocalSocket();

	static bool Send(int nSocket, const char* const pSendData, const int nSize);
	static bool Recv(int nSocket, char* const pRecvData, const int nSize);

private:
	bool Init();
	bool Socket(int& nSocket);
	bool SetSocket(int& nSocket);
	bool Bind();
	bool Listen();

	static void* HandleFunc(void* pData);
private:
	const static int m_IP_Size = 32;
	char m_szIP[m_IP_Size];
	int m_nPortLocal;
	int m_nPortFar;
	int m_sockLocal;
	int m_sockFar;
};

//常静态成员初始化
const int CLWZSocket::m_IP_Size;

#endif