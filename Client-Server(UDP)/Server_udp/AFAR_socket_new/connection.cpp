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
	SOCKET serverSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //�������� ������ SOCK_STREAM - TCP, SOCK_DGRAM - UDP
	stop
	if (serverSock==INVALID_SOCKET)//��������� �������� ������
	{
		cout << "Socket error 1:" << WSAGetLastError() << endl;
		return -1;
	}
	//��������� ������
	int OptVal = 1;
	int OptLen = sizeof(int);
	int rc = setsockopt(serverSock, SOL_SOCKET, SO_REUSEADDR, (const char*)&OptVal, OptLen);

	SOCKADDR_IN sin; //��������� �������� ������
	sin.sin_family = AF_INET; //������ ������ IPv4
	sin.sin_addr.s_addr = inet_addr(obj_dev->adress);//htonl(INADDR_ANY);//�����
	sin.sin_port = htons(obj_dev->port);// ����
	rc = bind(serverSock, (struct sockaddr*)& sin, sizeof(sin));// ���������� ������ �����
	stop
	if (ret_val == SOCKET_ERROR)
	{
		cout << "Socket error 2:" << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	SOCKADDR_IN from;
	int from_len = sizeof(from);



	////////////////////����� �����������
	char read_buffer[128];
	recvfrom(serverSock, read_buffer, sizeof(read_buffer), 0, (sockaddr*)& from, &from_len);
	in_addr ip_address = ((sockaddr_in)from).sin_addr;
	printf("������� ���������� �� %s, ���� %d\n", inet_ntoa(ip_address), obj_dev->port);


	char* command=new char[128];
	while (strcmp(command, "exit"))
	{
		cout << endl << "Enter command: "; cin >> command;
		stop
			if (sendto(serverSock, command, strlen(command), 0, (sockaddr*)& from, sizeof(from)))
			{
				cout << "Command has been sent!" << endl;
				//������� ����� �� �������
				int r_buf = recvfrom(serverSock, read_buffer, sizeof(read_buffer), 0, (sockaddr*)& from, &from_len);
				stop
				cout << "Server: ";
				for (int i = 0; i < r_buf; i++)
				{
					cout << read_buffer[i];
				}
				cout << endl;

			}
	}
	////////////////////
	closesocket(serverSock);
	return 1;
}