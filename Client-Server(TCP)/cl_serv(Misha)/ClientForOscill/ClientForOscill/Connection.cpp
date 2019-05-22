////////////////////////////////////////////////////////////////
//////Для установки соединения в качестве клиента///////////////
////////////////////////////////////////////////////////////////
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <Windows.h> 
#include <iostream>
#include "Header.h"

struct {
	SOCKET s;
	int err;
}addr_info;


void MessageSending(char *str) {
	int rc = send(addr_info.s, str, massSize, 0);
}

void MessageReceiving(char *str) {
	addr_info.err = recv(addr_info.s, str, massSize, 0);
	str[addr_info.err + 1] = 0;
}

bool ConnectDetection(char *namedir) {
	setlocale(LC_ALL, "Russian");
	WSADATA WsaData;
	int err = WSAStartup(0x0101, &WsaData);
	if (err == SOCKET_ERROR)
	{
		//printf("WSAStartup() failed: %ld\n", GetLastError());
		std::cout << "Ошибка открытия драйвера!\n";
		return 1;
	}
	addr_info.s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // SOCK_STREAM - взаимодействие с установкой соединения, AF_INET - TCP/IP
	char SERVERADDR[20] = { 0 };
	GetPrivateProfileStringA((LPCSTR) "IP", (LPCSTR) "1", (LPCSTR) "ERROR", (LPSTR)SERVERADDR, (DWORD) sizeof(SERVERADDR), (LPCSTR)namedir);
	int PORT = GetPrivateProfileIntA((LPCSTR) "PORT", (LPCSTR) "1", 100, (LPCSTR)namedir);
	SOCKADDR_IN anAddr;
	anAddr.sin_family = AF_INET;
	anAddr.sin_port = htons(PORT);
	anAddr.sin_addr.S_un.S_addr = inet_addr(SERVERADDR);

	err = 1;
	while (err != 0) {
		err = connect(addr_info.s, (struct sockaddr *)&anAddr, sizeof(struct sockaddr));
	}
	std::cout << "Соединение установлено!\n";
	return 0;
}

void ConnectClose() {
	closesocket(addr_info.s);
	WSACleanup();
}