#include "Header.h"

int main(int argc, char* argv[])
{
	SOCKET sock_client;
	ServerTcp client("192.168.0.16",4554,&sock_client);
	client.Connect();
	/////////////запрос->ответ сервера

	char command[] = "test done!";
	char read_buffer[128];
	recv(sock_client, read_buffer, sizeof(read_buffer), 0);
	stop

	
	send(sock_client, command, strlen(command), 0);
	/////////////
	closesocket(sock_client);
	system("pause");
}