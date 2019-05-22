#include "Header.h"

int connectionClient(DEVICE* obj_dev)//const char* adress, int& port, SOCKET* my_sock)
{
	//////////Клиентская часть
	setlocale(LC_ALL, "Russian");
	cout << "Ожидание соединения..." << endl;
	WSADATA ws;
	sockaddr_in addr;
	int ret_val;

	if (FAILED(WSAStartup(MAKEWORD(2, 2), &ws))) //инициализация Winsock
	{
		cout << "WSAStart error: " << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	SOCKET clientSocket;
	clientSocket= socket(AF_INET, SOCK_STREAM, 0); //создание сокета SOCK_STREAM - TCP, SOCK_DGRAM - UDP
	if (clientSocket == INVALID_SOCKET) //создаем сокет
	{
		cout << "Socket error 1:" << WSAGetLastError() << endl;
		return -1;
	}
	else //устанавливаем соединение
	{
		//ZeroMemory(&addr, sizeof(addr)); //заполняем память нулями
		addr.sin_family = AF_INET;
		addr.sin_port = htons(obj_dev->port); //переводим порт из обычного представления в TCP/IP

		//TCP
		HOSTENT* hst;
		if (inet_addr(obj_dev->adress) != INADDR_NONE)
		{
			addr.sin_addr.s_addr = inet_addr(obj_dev->adress);
		}
		/*else //пытаемся получить адрес через имя хоста
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
		printf("Установлено соединение с %s, порт %d\n", obj_dev->adress, obj_dev->port);
		//////////////////////////////////////////////Обмен командами
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