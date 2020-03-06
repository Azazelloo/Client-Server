#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <Winsock2.h>
#include <windows.h>
#include "ServerTcp.h"

#define	  stop __asm nop
using namespace std;

#pragma comment(lib,"Wsock32.lib")
