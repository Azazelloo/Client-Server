#include "Header.h"

int connectionServer(DEVICE* obj_dev)//const char* adress, int& port, SOCKET* my_sock)
{
	//////////Серверная часть
	setlocale(LC_ALL, "Russian");
	cout << "Ожидание соединения..." << endl;
	WSADATA ws;
	sockaddr_in addr;
	int ret_val;

	if (FAILED(WSAStartup(MAKEWORD(2,2), &ws))) //инициализация Winsock
	{
		cout << "WSAStart error: " << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	//SOCKET serverSock TCP
	SOCKET serverSock = socket(AF_INET, SOCK_STREAM, 0); //создание сокета SOCK_STREAM - TCP, SOCK_DGRAM - UDP
	stop
	if (serverSock==INVALID_SOCKET)//проверяем создание сокета
	{
		cout << "Socket error 1:" << WSAGetLastError() << endl;
		return -1;
	}

	SOCKADDR_IN sin; //структура описания сокета
	sin.sin_family = AF_INET; //формат адреса IPv4
	sin.sin_addr.s_addr = inet_addr(obj_dev->adress);//htonl(INADDR_ANY);//адрес
	sin.sin_port = htons(obj_dev->port);// порт
	ret_val = bind(serverSock, (struct sockaddr*)& sin, sizeof(sin));// присвоение сокету имени
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
	//начинаем слушать сокет
	ret_val = listen(serverSock,10); //сокет ожидает запросы на связь с ним, 10- сколько одновременно запросов может быть принято
	if (ret_val == SOCKET_ERROR)
	{
		cout << "Socket error 3:" << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	//ждем клиент
	SOCKET clientSock;
	SOCKADDR_IN from;
	int fromlen = sizeof(from);
	clientSock = accept(serverSock, (sockaddr*)&from, &fromlen);//принять соединение на сокете

	if (serverSock == INVALID_SOCKET)
	{
		cout << "Socket error 4:" << WSAGetLastError() << endl;
		return -1;
	}
	*obj_dev->sock_dev = clientSock;
	/////////////////////
	in_addr ip_address = ((sockaddr_in)from).sin_addr;
	printf("Принято соединение от %s, порт %d\n", inet_ntoa(ip_address), obj_dev->port);
	stop
	//////////
	return 1;
}