#pragma once
class ServerTcp {
	char* m_addres_server_machine;
	int m_port;
	SOCKET* m_sock_client;
public:
	ServerTcp(const char* addr, int port, SOCKET* sock);
	~ServerTcp();
	int Connect();
};