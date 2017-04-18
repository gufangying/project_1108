#include <iostream>
#include <unistd.h>
#include "../LWZSocket.h"

using namespace std;

void* UserFunc(void* arg)
{
	//解析参数
	CLWZSocket::stUserData* pUserData = (CLWZSocket::stUserData*)arg;

	const int nSize = 16;
	char szSend[nSize] = "12345678";
	char szRecv[nSize] = "";

	//处理
	while(1)
	{
		//发数据
		if(false == CLWZSocket::Send(pUserData->sockClient, szSend, nSize))
		{
			err("Send Failed \n");
			break;
		}

		//收数据
		if(false == CLWZSocket::Recv(pUserData->sockClient, szRecv, nSize))
		{
			err("Recv Failed \n");
			break;
		}

		szRecv[nSize - 1] = 0;
		prt("RecvData : \n %s \n", szRecv);

		sleep(3);
	}
}

int main(int argc, char* argv[])
{
	cout<<"Test main"<<endl;

	Test();

	//创建服务器的步骤(1,2,3)
	CLWZSocket obj;
	
	//1. 初始化服务器
	obj.InitServer();

	//2. 创建服务器
	obj.CreateServer();

	//3. 等待连接, 传入函数指针, 该函数用户自定义
	obj.Accept(UserFunc);

	prt("Quit \n");

	return 0;
}
