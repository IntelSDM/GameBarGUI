#include "pch.h"
#include "Sockets.h"
#pragma comment(lib, "ws2_32.lib")
#include "Config.h"



Config ConfigInstance;

void main()
{
	json j;
	ConfigInstance.toJson(j);
	std::cout << j.dump() << "\n";

	CreateSockets();
	std::thread listernerthread(AcceptClients);
	listernerthread.join();
}