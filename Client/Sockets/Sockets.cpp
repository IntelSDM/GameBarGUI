#include "pch.h"
#include "Sockets.h"
#pragma comment(lib, "ws2_32.lib")

sockaddr_in HInt;
SOCKET Listening;
sockaddr_in ClientAddress;

void CreateSockets()
{
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);
    WSAStartup(ver, &wsData); // start the server

    Listening = socket(AF_INET, SOCK_STREAM, 0); // create socket instance

    HInt.sin_family = AF_INET; // declare the ip and port and connection rules
    HInt.sin_port = htons(51000);
    HInt.sin_addr.S_un.S_addr = INADDR_ANY;

    bind(Listening, reinterpret_cast<sockaddr*>(&HInt), sizeof(HInt)); // bind the connection rules to the listening socket
    listen(Listening, SOMAXCONN); // keep socket open
}

void AcceptClients()
{
    while (true)
    {
        int clientSize = sizeof(ClientAddress);
        SOCKET clientSocket = accept(Listening, reinterpret_cast<SOCKADDR*>(&ClientAddress), &clientSize);
        if (clientSocket != INVALID_SOCKET)
        {
            std::cout << "connection\n";
        }
    }
}
