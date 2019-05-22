#include "Header.h"

int connectionClient(DEVICE* obj_dev)//const char* adress, int& port, SOCKET* my_sock)
{
	//////////Клиентская часть
	setlocale(LC_ALL, "Russian");
	cout << "Ожидание соединения..." << endl;
	WSADATA ws;
	sockaddr_in server,client;
	int ret_val;

	if (FAILED(WSAStartup(MAKEWORD(2, 2), &ws))) //инициализация Winsock
	{
		cout << "WSAStart error: " << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	SOCKET clientSocket;
	clientSocket= socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //создание сокета SOCK_STREAM - TCP, SOCK_DGRAM - UDP
	if (clientSocket == INVALID_SOCKET) //создаем сокет
	{
		cout << "Socket error 1:" << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	else //устанавливаем соединение
	{
		int OptVal = 1;
		int OptLen = sizeof(int);
		int rc = setsockopt(clientSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&OptVal, OptLen);

		//запонлняем структуру для сервера
		server.sin_family = AF_INET;
		server.sin_port = htons(obj_dev->port); //переводим порт из обычного представления в TCP/IP
		server.sin_addr.s_addr = inet_addr(obj_dev->adress);
		
		//запонлняем структуру для клиента
		int client_len = sizeof(client);
		client.sin_family = AF_INET;
		client.sin_port = htons(obj_dev->port);
		client.sin_addr.s_addr = INADDR_ANY;
		stop
		rc = bind(clientSocket, (struct sockaddr*)& client, client_len);
		stop
		if (rc == SOCKET_ERROR)
		{
			cout << "Socket error 2:" << WSAGetLastError() << endl;
			WSACleanup();
			return 0;
		}
		stop
			//////////////////////Обмен командами
		char mes[] = "client test string!";
		cout << "Send message>>" << endl;
			if (sendto(clientSocket, mes, sizeof(mes), 0, (sockaddr*)&server, sizeof(server)))
			{
				cout << "Message has been sent!" << endl;
			}
		
		//////////////////////
		closesocket(clientSocket);
		return 1;
	}
}