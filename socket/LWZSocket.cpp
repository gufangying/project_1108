#include "LWZSocket.h"

void Test()
{
	cout<<"Hello, World"<<endl;
}

/********************************************************************
函 数 名 : CLWZSocket
函数功能 ：构造函数
返 回 值 : bool
参    数 : 无
修改时间 : 1. 2017/4/17，卢磊，生成函数
********************************************************************/
CLWZSocket::CLWZSocket()
{
	prt("CLWZSocket Enter \n");

	Init();
}

/********************************************************************
函 数 名 : ~CLWZSocket
函数功能 ：析构函数
返 回 值 : bool
参    数 : 无
修改时间 : 1. 2017/4/17，卢磊，生成函数
********************************************************************/
CLWZSocket::~CLWZSocket()
{
	
}

/********************************************************************
函 数 名 : Init
函数功能 ：对象初始化
返 回 值 : bool
参    数 : 无
修改时间 : 1. 2017/4/17，卢磊，生成函数
********************************************************************/
bool CLWZSocket::Init()
{
	prt("Init Enter \n");

	m_nPortLocal = 0;
	m_nPortFar = 0;
	sprintf(m_szIP, "%s", "127.0.0.1");
	m_sockLocal = 0;
	m_sockFar = 0;

	return true;
}

/********************************************************************
函 数 名 : InitServer
函数功能 ：初始化服务器
返 回 值 : bool
参    数 : 无
修改时间 : 1. 2017/4/17，卢磊，生成函数
********************************************************************/
bool CLWZSocket::InitServer(int nPort, const char* pszIP)
{
	m_nPortLocal = nPort;
	sprintf(m_szIP, "%s", pszIP);

	return true;
}

/********************************************************************
函 数 名 : CreateServer
函数功能 ：创建服务端
返 回 值 : bool
参    数 : 无
修改时间 : 1. 2017/4/17，卢磊，生成函数
********************************************************************/
bool CLWZSocket::CreateServer()
{
	if(Socket())
	{
		if(SetSocket())
		{
			if(Bind())
			{
				if(Listen())
				{
					prt("Successful\n");
				}
			}
		}
	}

	return true;
}

/********************************************************************
函 数 名 : Accept
函数功能 ：等待连接
返 回 值 : bool
参    数 : 无
修改时间 : 1. 2017/4/17，卢磊，生成函数
********************************************************************/
bool CLWZSocket::Accept()
{
	//客户端
	int sockClient = 0;

	//客户端信息
	struct sockaddr stNewClientAddr;
	socklen_t nClientAddrLen = sizeof(stNewClientAddr);
	
	while(true)
	{
		prt("Wait Client Conn... \n");
		sockClient = accept(m_sockLocal, (struct sockaddr *)&stNewClientAddr, &nClientAddrLen);

		if (sockClient < 0)
		{
			err("Accept Failed \n");
			continue;
		}

		prt("A New Client Connected\n");

		//创建处理线程
		pthread_t AppThdID;
		stUserData* pUserData = new stUserData();
		pUserData->sockClient = sockClient;
		if (pthread_create(&AppThdID, NULL, HandleFunc, (void *)pUserData))
		{
			err("Create Handle Thread Failed \n");
			continue;
		}

		//设置子线程为脱离状态
		pthread_detach(AppThdID);
	}

	return true;
}

/********************************************************************
函 数 名 : InitClient
函数功能 ：初始化客户端
返 回 值 : bool
参    数 : 无
修改时间 : 1. 2017/4/17，卢磊，生成函数
********************************************************************/
bool CLWZSocket::InitClient(int nPort, const char* pszIP)
{
	if(Socket())
	{
		//远程服务器端口
		m_nPortFar = nPort;

		//远程服务器ip
		sprintf(m_szIP, "%s", pszIP);
	}
}

/********************************************************************
函 数 名 : Connect
函数功能 ：连接服务器
返 回 值 : bool
参    数 : 无
修改时间 : 1. 2017/4/17，卢磊，生成函数
********************************************************************/
bool CLWZSocket::Connect()
{
	struct hostent *host;
	struct sockaddr_in serv_addr;

	host = gethostbyname(m_szIP);

	serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(m_nPortFar);
    serv_addr.sin_addr = *((struct in_addr *)host->h_addr);


	if(connect(m_sockLocal,(struct sockaddr *)&serv_addr, sizeof(struct sockaddr))== -1)
    {
        err("Connect Failed \n");
        return false;
    }

    prt("Successful \n");
}

/********************************************************************
函 数 名 : Send
函数功能 ：发送数据
返 回 值 : bool
参    数 : 无
修改时间 : 1. 2017/4/17，卢磊，生成函数
********************************************************************/
bool CLWZSocket::Send()
{
	return true;
}

/********************************************************************
函 数 名 : Recv
函数功能 ：接收数据
返 回 值 : bool
参    数 : 无
修改时间 : 1. 2017/4/17，卢磊，生成函数
********************************************************************/
bool CLWZSocket::Recv()
{
	return true;
}

/********************************************************************
函 数 名 : Socket
函数功能 ：创建socket
返 回 值 : bool
参    数 : 无
修改时间 : 1. 2017/4/17，卢磊，生成函数
********************************************************************/
bool CLWZSocket::Socket()
{
	m_sockLocal = socket(AF_INET, SOCK_STREAM, 0);
	if(m_sockLocal < 0)
	{
		err("Socket Failed \n");
		return false;
	}

	return true;
}

/********************************************************************
函 数 名 : SetSocket
函数功能 ：设置属性
返 回 值 : bool
参    数 : 无
修改时间 : 1. 2017/4/17，卢磊，生成函数
********************************************************************/
bool CLWZSocket::SetSocket()
{
	int flag = 1;
	int option = 1;


	//设置地址复用
	if (setsockopt(m_sockLocal, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int)) < 0)
	{
		err("Faied \n");
		return false;
	}

	//设置端口复用
	if (setsockopt(m_sockLocal, SOL_SOCKET, SO_REUSEPORT, &option, sizeof(option)) < 0)
	{
		err("Faied \n");
		return false;
	}

	return true;
}

/********************************************************************
函 数 名 : Bind
函数功能 ：绑定端口
返 回 值 : bool
参    数 : 无
修改时间 : 1. 2017/4/17，卢磊，生成函数
********************************************************************/
bool CLWZSocket::Bind()
{
	struct sockaddr_in stSockAcAddr;
	memset(&stSockAcAddr, 0, sizeof(stSockAcAddr));
	stSockAcAddr.sin_family = AF_INET;

	prt("nPort: %d \t ip: %s \n", m_nPortLocal, m_szIP);

	//设置ip
	inet_pton(AF_INET, m_szIP, &stSockAcAddr.sin_addr);

	//设置端口
	stSockAcAddr.sin_port = htons(m_nPortLocal);

	if(bind(m_sockLocal, (struct sockaddr *)&stSockAcAddr, sizeof(stSockAcAddr)))
	{
		err("Bind Faied \n");
		return false;
	}

	return true;
}

/********************************************************************
函 数 名 : Listen
函数功能 ：监听端口
返 回 值 : bool
参    数 : 无
修改时间 : 1. 2017/4/17，卢磊，生成函数
********************************************************************/
bool CLWZSocket::Listen()
{
	//完成三次握手队列长度
	int nBlack = 5;

	if(listen(m_sockLocal, nBlack))
	{
		err("Listen Faied \n");
		return false;
	}

	return true;
}

/********************************************************************
函 数 名 : HandleFunc
函数功能 ：处理线程函数
返 回 值 : void
参    数 : void*,用户参数
修改时间 : 1. 2017/4/17，卢磊，生成函数
********************************************************************/
void* CLWZSocket::HandleFunc(void* pData)
{
	if(NULL == pData){
		err("NULL == pData \n");
	}

	//参数
	stUserData* pUserData = (stUserData*)pData;

	//处理...

	//最后记得释放pData
	delete pUserData;
}

void CLWZSocket::Show()
{
	cout<<"CLWZSocket::Show"<<endl;
}