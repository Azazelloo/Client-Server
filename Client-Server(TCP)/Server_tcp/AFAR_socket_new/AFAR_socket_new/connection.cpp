#include "Header.h"


int connection(const char* adress, int& port, SOCKET* my_sock)
{
	WSADATA ws;
	sockaddr_in addr;

	if (FAILED(WSAStartup(MAKEWORD(1,1),&ws))) //������������� Winsock
	{
		//cout << "WSAStart error: " << WSAGetLastError() << endl;
		return -1;
	}

	if (INVALID_SOCKET==(*my_sock = socket(AF_INET, SOCK_STREAM, 0))) //������� �����
	{
		//cout << "Socket error:" << WSAGetLastError() << endl;
		return -1;
	}
	else //������������� ����������
	{
		ZeroMemory(&addr,sizeof(addr)); //��������� ������ ������
		addr.sin_family = AF_INET;
		addr.sin_addr.S_un.S_addr = inet_addr(adress);
		addr.sin_port = htons(port); //��������� ���� �� �������� ������������� � TCP/IP

		if (SOCKET_ERROR==(connect(*my_sock,(sockaddr*) &addr,sizeof(addr))))
		{
			//cout << "Connect socket error:" << WSAGetLastError() << endl;
			return -1;
		}
		return 1;
	}
}