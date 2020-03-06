#include "Header.h"

ClientTcp::ClientTcp(const char* addr,int port, SOCKET* sock):m_port(port),m_sock(sock)
{
	m_server_addr = new char[strlen(addr) + 1];
	strcpy(m_server_addr,addr);
}

ClientTcp::~ClientTcp()
{
	delete[] m_server_addr;
}

int ClientTcp::Connect()
{
	cout << "Waiting for server connection......"<<endl;
	
	WSADATA ws;
	sockaddr_in sock_addr;
	HOSTENT* hst;
	int ret_val;

	if (FAILED(WSAStartup(MAKEWORD(2, 2), &ws))) //инициализация Winsock
	{
		cout << "WSAStart error: " << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}

	//SOCKET clientSocket;
	*m_sock = socket(AF_INET, SOCK_STREAM, 0); //создание сокета SOCK_STREAM - TCP, SOCK_DGRAM - UDP
	if (*m_sock == INVALID_SOCKET) //создаем сокет
	{
		cout << "Socket error 1:" << WSAGetLastError() << endl;
		return -1;
	}
	else //устанавливаем соединение
	{
		sock_addr.sin_family = AF_INET;
		sock_addr.sin_port = htons(m_port); //переводим порт из обычного представления в TCP/IP
		sock_addr.sin_addr.s_addr = inet_addr(m_server_addr);

		if (connect(*m_sock, (sockaddr*)& sock_addr, sizeof(sock_addr)) == SOCKET_ERROR)
		{
			cout << "Socket error 2:" << WSAGetLastError() << endl;
			WSACleanup();
			return -1;
		}

		printf("Connected to %s, port %d\n", m_server_addr, m_port);
	}
}
