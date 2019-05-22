#pragma once

class ClientTcp {
	char* m_server_addr;
	int m_port;
	SOCKET* m_sock;
public:
	ClientTcp(const char* addr,int port, SOCKET* sock);
	~ClientTcp();
	int Connect();
};