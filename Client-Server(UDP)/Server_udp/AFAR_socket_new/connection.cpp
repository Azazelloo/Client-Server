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
	SOCKET serverSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //создание сокета SOCK_STREAM - TCP, SOCK_DGRAM - UDP
	stop
	if (serverSock==INVALID_SOCKET)//проверяем создание сокета
	{
		cout << "Socket error 1:" << WSAGetLastError() << endl;
		return -1;
	}
	//настройка сокета
	int OptVal = 1;
	int OptLen = sizeof(int);
	int rc = setsockopt(serverSock, SOL_SOCKET, SO_REUSEADDR, (const char*)&OptVal, OptLen);

	SOCKADDR_IN sin; //структура описания сокета
	sin.sin_family = AF_INET; //формат адреса IPv4
	sin.sin_addr.s_addr = inet_addr(obj_dev->adress);//htonl(INADDR_ANY);//адрес
	sin.sin_port = htons(obj_dev->port);// порт
	rc = bind(serverSock, (struct sockaddr*)& sin, sizeof(sin));// присвоение сокету имени
	stop
	if (ret_val == SOCKET_ERROR)
	{
		cout << "Socket error 2:" << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	SOCKADDR_IN from;
	int from_len = sizeof(from);



	////////////////////Обмен сообщениями
	char read_buffer[128];
	recvfrom(serverSock, read_buffer, sizeof(read_buffer), 0, (sockaddr*)& from, &from_len);
	in_addr ip_address = ((sockaddr_in)from).sin_addr;
	printf("Принято соединение от %s, порт %d\n", inet_ntoa(ip_address), obj_dev->port);


	char* command=new char[128];
	while (strcmp(command, "exit"))
	{
		cout << endl << "Enter command: "; cin >> command;
		stop
			if (sendto(serverSock, command, strlen(command), 0, (sockaddr*)& from, sizeof(from)))
			{
				cout << "Command has been sent!" << endl;
				//ожидаем ответ от сервера
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