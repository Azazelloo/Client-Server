#include "Header.h"

int main(int argc, char* argv[])
{
	SOCKET sock_1;
	ClientTcp conection_1("192.168.0.16", 4554, &sock_1);
	conection_1.Connect();

	/////////////запрос->ответ сервера
	char command[] = "String test";
	char read_buffer[128];
	send(sock_1, command, strlen(command), 0);

	recv(sock_1, read_buffer, sizeof(read_buffer), 0);
	stop
	/////////////
	closesocket(sock_1);
	system("pause");
}