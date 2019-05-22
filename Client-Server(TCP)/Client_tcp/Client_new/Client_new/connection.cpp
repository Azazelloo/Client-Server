#include "Header.h"

int connectionClient(DEVICE* obj_dev)//const char* adress, int& port, SOCKET* my_sock)
{
	//////////���������� �����
	setlocale(LC_ALL, "Russian");
	cout << "�������� ����������..." << endl;
	WSADATA ws;
	sockaddr_in addr;
	int ret_val;

	if (FAILED(WSAStartup(MAKEWORD(2, 2), &ws))) //������������� Winsock
	{
		cout << "WSAStart error: " << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	SOCKET clientSocket;
	clientSocket= socket(AF_INET, SOCK_STREAM, 0); //�������� ������ SOCK_STREAM - TCP, SOCK_DGRAM - UDP
	if (clientSocket == INVALID_SOCKET) //������� �����
	{
		cout << "Socket error 1:" << WSAGetLastError() << endl;
		return -1;
	}
	else //������������� ����������
	{
		//ZeroMemory(&addr, sizeof(addr)); //��������� ������ ������
		addr.sin_family = AF_INET;
		addr.sin_port = htons(obj_dev->port); //��������� ���� �� �������� ������������� � TCP/IP

		//TCP
		HOSTENT* hst;
		if (inet_addr(obj_dev->adress) != INADDR_NONE)
		{
			addr.sin_addr.s_addr = inet_addr(obj_dev->adress);
		}
		/*else //�������� �������� ����� ����� ��� �����
		{
			if (hst = gethostbyname(obj_dev->adress))
			{
				((unsigned long*)& dest_addr.sin_addr)[0] = ((unsigned long **)hst->h_addr_list)[0][0];
			}
			else
			{
				printf("invalid adress %s\n", obj_dev->adress);
				closesocket(*obj_dev->sock_dev);
				WSACleanup();
				return -1;
			}
		}*/

		if (connect(clientSocket, (sockaddr*)& addr, sizeof(addr))== SOCKET_ERROR)
		{
			cout << "Socket error 2:" << WSAGetLastError() << endl;
			WSACleanup();
			return -1;
		}
		stop
		*obj_dev->sock_dev = clientSocket;
		printf("����������� ���������� � %s, ���� %d\n", obj_dev->adress, obj_dev->port);
		//////////////////////////////////////////////����� ���������
		char message[] = "111111";
		for(int i=0;i<10;i++)
		{
			if (sendto(clientSocket, message, strlen(message), 0, (sockaddr*)& addr, sizeof(addr)))
			{
				cout << "Message has been sent!" << endl;
				Sleep(3000);
			}
		}
		closesocket(clientSocket);
		stop
		//////////////////////////////////////////////
		return 1;
	}
}