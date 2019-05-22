#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#define COUNT_DEVICE 3

#include <iostream>
#include <Winsock2.h>
#include <windows.h>

#define	  stop __asm nop
using namespace std;

#pragma comment(lib,"Wsock32.lib")

struct DEVICE
{
	char adress[128];
	int port;
	SOCKET sock_dev;
};

char read_buffer[1024];

int connection(const char* adress, int& port, SOCKET* my_sock);
void write(const char* command, SOCKET* my_sock);
const char* read(const char* command, SOCKET* my_sock);