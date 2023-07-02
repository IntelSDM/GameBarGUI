#include "pch.h"
#pragma comment(lib, "ws2_32.lib")
void CreateSockets()
{
    WSADATA data;
    WORD ver = MAKEWORD(2, 2);
    int wsResult = WSAStartup(ver, &data);
    if (wsResult != 0)
    {
        return;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
    {
        WSACleanup();
        return;
    }

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(51000);
    inet_pton(AF_INET, "127.0.0.1", &hint.sin_addr);

    if (connect(sock, reinterpret_cast<sockaddr*>(&hint), sizeof(hint)) == SOCKET_ERROR)
    {
        closesocket(sock);
        WSACleanup();
        return;
    }
}