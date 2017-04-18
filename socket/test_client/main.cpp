#include <iostream>
#include "../socket/LWZSocket.h"

using namespace std;

int main(int argc, char* argv[])
{
	cout<<"Test_Client main"<<endl;

	CLWZSocket obj;

	obj.InitClient();
	obj.Connect();

	prt("Quit \n");

	return 0;
}
