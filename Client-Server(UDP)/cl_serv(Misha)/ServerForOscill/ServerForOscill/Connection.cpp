////////////////////////////////////////////////////////////////
//////Для установки соединения в качестве сервера///////////////
////////////////////////////////////////////////////////////////
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <Windows.h> 
#include <iostream>
#include "Header.h"

struct {
	SOCKET s, s1;
	int err;
}addr_info;

bool ConnectDetection(char *namedir) {
	setlocale(LC_ALL, "Russian");
	WSADATA WsaData;
	char SERVERADDR[128] = { 0 };
	int PORT;
	int err = WSAStartup(0x0101, &WsaData);
	if (err == SOCKET_ERROR)
	{
		printf("WSAStartup() failed: %ld\n", GetLastError());
		return 1;
	}
	
	GetPrivateProfileStringA((LPCSTR) "IP", (LPCSTR) "0", (LPCSTR) "ERROR", (LPSTR)SERVERADDR, (DWORD) sizeof(SERVERADDR), (LPCSTR)namedir);
	PORT = GetPrivateProfileIntA((LPCSTR) "PORT", (LPCSTR) "0", 100, (LPCSTR)namedir);
	addr_info.s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // SOCK_STREAM - взаимодействие с установкой соединения, AF_INET - TCP/IP
	SOCKADDR_IN sin;

	sin.sin_family = AF_INET; // определяет используемый формат адреса (AF_INET - дл¤ TCP/IP)
	sin.sin_addr.s_addr = inet_addr(SERVERADDR);//INADDR_ANY; //адрес (номер) узла сети

	sin.sin_port = htons(PORT); // номер порта на узле сети


	addr_info.err = bind(addr_info.s, (LPSOCKADDR)&sin, sizeof(sin));

	addr_info.err = listen(addr_info.s, SOMAXCONN);

	SOCKADDR_IN from;

	int fromlen = sizeof(from);
	addr_info.s1 = accept(addr_info.s, (struct sockaddr*)&from, &fromlen);
	printf("принято соединение от %s, порт %d\n", SERVERADDR, PORT);
	printf("принято соединение от %s, порт %d\n", inet_ntoa(from.sin_addr), htons(from.sin_port));
	return 0;
}

void MessageSending(char *str) {
	int rc = send(addr_info.s1, str, massSize, 0);
}

void MessageReceiving(char *str) {
	addr_info.err = recv(addr_info.s1, str, massSize, 0);
	str[addr_info.err + 1] = 0;
}

void ConnectClose() {
	closesocket(addr_info.s);
	closesocket(addr_info.s1);
	WSACleanup();
}