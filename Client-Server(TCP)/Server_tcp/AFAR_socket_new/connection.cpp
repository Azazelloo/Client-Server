#include "Header.h"

int connectionServer(DEVICE* obj_dev)//const char* adress, int& port, SOCKET* my_sock)
{
	//////////��������� �����
	setlocale(LC_ALL, "Russian");
	cout << "�������� ����������..." << endl;
	WSADATA ws;
	sockaddr_in addr;
	int ret_val;

	if (FAILED(WSAStartup(MAKEWORD(2,2), &ws))) //������������� Winsock
	{
		cout << "WSAStart error: " << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	//SOCKET serverSock TCP
	SOCKET serverSock = socket(AF_INET, SOCK_STREAM, 0); //�������� ������ SOCK_STREAM - TCP, SOCK_DGRAM - UDP
	stop
	if (serverSock==INVALID_SOCKET)//��������� �������� ������
	{
		cout << "Socket error 1:" << WSAGetLastError() << endl;
		return -1;
	}

	SOCKADDR_IN sin; //��������� �������� ������
	sin.sin_family = AF_INET; //������ ������ IPv4
	sin.sin_addr.s_addr = inet_addr(obj_dev->adress);//htonl(INADDR_ANY);//�����
	sin.sin_port = htons(obj_dev->port);// ����
	ret_val = bind(serverSock, (struct sockaddr*)& sin, sizeof(sin));// ���������� ������ �����
	stop
	if (ret_val == SOCKET_ERROR)
	{
		cout << "Socket error 2:" << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	//UDP
	/*SOCKADDR_IN from;
	char buff[128];
	int from_len = sizeof(from);
	recvfrom(serverSock,buff,128,0, (struct sockaddr*)& from, &from_len );
	stop*/
	// TCP
	//�������� ������� �����
	ret_val = listen(serverSock,10); //����� ������� ������� �� ����� � ���, 10- ������� ������������ �������� ����� ���� �������
	if (ret_val == SOCKET_ERROR)
	{
		cout << "Socket error 3:" << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	//���� ������
	SOCKET clientSock;
	SOCKADDR_IN from;
	int fromlen = sizeof(from);
	clientSock = accept(serverSock, (sockaddr*)&from, &fromlen);//������� ���������� �� ������

	if (serverSock == INVALID_SOCKET)
	{
		cout << "Socket error 4:" << WSAGetLastError() << endl;
		return -1;
	}
	*obj_dev->sock_dev = clientSock;
	/////////////////////
	in_addr ip_address = ((sockaddr_in)from).sin_addr;
	printf("������� ���������� �� %s, ���� %d\n", inet_ntoa(ip_address), obj_dev->port);
	stop
	//////////
	return 1;
}