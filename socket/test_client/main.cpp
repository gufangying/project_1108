#include <iostream>
#include <unistd.h>
#include "../socket/LWZSocket.h"

using namespace std;

int main(int argc, char* argv[])
{
	cout<<"Test_Client main"<<endl;

	//创建客户端的步骤(1,2,3)
	CLWZSocket obj;

	//1. 初始化客户端
	obj.InitClient();

	//2. 连接服务器
	obj.Connect();

	//3. 通过函数GetFarSocket可以获取通信socket

	const int nSize = 16;
	char szSend[nSize] = "87654321";
	char szRecv[nSize] = "";

	//处理
	while(1)
	{
		//收数据
		if(false == CLWZSocket::Recv(obj.GetFarSocket(), szRecv, nSize))
		{
			err("Recv Failed \n");
			break;
		}

		szRecv[nSize - 1] = 0;
		prt("RecvData : \n %s \n", szRecv);

		sleep(3);

		//发数据
		if(false == CLWZSocket::Send(obj.GetFarSocket(), szSend, nSize))
		{
			err("Send Failed \n");
			break;
		}

	}

	prt("Quit \n");

	return 0;
}
