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
#include "../public/common.h"

using namespace std;

void Test();

class CLWZSocket
{
public:
	void Show();
	
private:
	int m_nPort;
	
};

#endif