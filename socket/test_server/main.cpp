#include <iostream>
#include "../socket/LWZSocket.h"

using namespace std;

int main(int argc, char* argv[])
{
	cout<<"Test main"<<endl;

	Test();

	CLWZSocket obj;

	obj.InitServer();
	obj.CreateServer();
	obj.Accept();

	prt("Quit \n");

	return 0;
}
