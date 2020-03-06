#include "Header.h"

ServerTcp::ServerTcp(const char* addr, int port, SOCKET* sock) :m_port(port), m_sock_client(sock)
{
	m_addres_server_machine = new char[strlen(addr) + 1];
	strcpy(m_addres_server_machine, addr);
}

ServerTcp::~ServerTcp()
{
	delete[] m_addres_server_machine;
}

int ServerTcp::Connect()
{
	cout << "Waiting for client connection:" << endl;

	WSADATA ws;
	sockaddr_in s_addr_in,s_addr_out;
	int ret_val;

	if (FAILED(WSAStartup(MAKEWORD(2, 2), &ws))) //инициализация Winsock
	{
		cout << "WSAStart error: " << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}

	SOCKET serverSock = socket(AF_INET, SOCK_STREAM, 0); //создание сокета SOCK_STREAM - TCP, SOCK_DGRAM - UDP
	stop
		if (serverSock == INVALID_SOCKET)//проверяем создание сокета
		{
			cout << "Socket error 1:" << WSAGetLastError() << endl;
			return -1;
		}

	s_addr_in.sin_family = AF_INET; //формат адреса IPv4
	s_addr_in.sin_addr.s_addr = inet_addr(m_addres_server_machine);//htonl(INADDR_ANY);//адрес
	s_addr_in.sin_port = htons(m_port);// порт
	ret_val = bind(serverSock, (struct sockaddr*)& s_addr_in, sizeof(s_addr_in));// присвоение сокету имени
	stop
		if (ret_val == SOCKET_ERROR)
		{
			cout << "Socket error 2:" << WSAGetLastError() << endl;
			WSACleanup();
			return -1;
		}

	ret_val = listen(serverSock, 10); //сокет ожидает запросы на связь с ним, 10 - сколько одновременно запросов может быть принято
	if (ret_val == SOCKET_ERROR)
	{
		cout << "Socket error 3:" << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}

	//SOCKET clientSock;
	//SOCKADDR_IN from;
	int fromlen = sizeof(s_addr_out);
	*m_sock_client = accept(serverSock, (sockaddr*)&s_addr_out, &fromlen);//принять соединение на сокете

	if (serverSock == INVALID_SOCKET)
	{
		cout << "Socket error 4:" << WSAGetLastError() << endl;
		return -1;
	}

	in_addr ip_address = ((sockaddr_in)s_addr_out).sin_addr;
	printf("Connected to %s, port %d\n", inet_ntoa(ip_address), m_port);
	return 1;
}

