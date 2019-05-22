#include "Header.h"

void write(const char* command, SOCKET* my_sock)
{
	if (SOCKET_ERROR == send(*my_sock, command, strlen(command), 0))
	{
		cout << "Error write: " << WSAGetLastError();
	}
}