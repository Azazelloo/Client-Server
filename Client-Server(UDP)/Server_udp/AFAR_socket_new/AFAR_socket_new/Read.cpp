#include "Header.h"

const char* read(const char* command, SOCKET* my_sock)
{
	write(command,my_sock);

	int nsize;
	if ((nsize = recv(*my_sock, read_buffer, sizeof(read_buffer), 0)) == SOCKET_ERROR)
	{
		cout << "Recv error!" << endl;
		return 0;
	}
	else
	{
		read_buffer[nsize] = 0;
	}
	return read_buffer;
}