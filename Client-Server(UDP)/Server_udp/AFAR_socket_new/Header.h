#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#define COUNT_DEVICE 1

#include <iostream>
#include <Winsock2.h>
#include <windows.h>

#define	  stop __asm nop
using namespace std;

#pragma comment(lib,"Wsock32.lib")

struct DEVICE
{
	char* adress;
	int port;
	SOCKET* sock_dev;
};

int connectionServer(DEVICE* obj_dev);
