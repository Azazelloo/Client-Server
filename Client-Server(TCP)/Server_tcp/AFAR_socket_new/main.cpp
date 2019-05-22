#include "Header.h"

DEVICE** devices_array = new DEVICE*[COUNT_DEVICE];//выдел€ем пам€ть под массив устройств

SOCKET sp_sock, gen_sock, sa_sock,misha_sock;
SOCKET* sock_array[COUNT_DEVICE] = { &misha_sock }; //массив сокетов 

const char* name_dev_array[COUNT_DEVICE] = { "Server_adress" };

int main(int argc, char* argv[])
{
	////////„итаем ini файл
	char buf[128];
	for (int i = 0; i < COUNT_DEVICE; i++)
	{
		devices_array[i] = new DEVICE;//выдел€ем пам€ть под текущее устройство
		stop
			GetPrivateProfileString(name_dev_array[i], "adress", "Error!", buf, sizeof(buf), "../settings/conf.ini"); //берем адрес прибора, заносим в структуру
		devices_array[i]->adress = new char[strlen(buf) + 1];//выдел€ем пам€ть дл€ копировани€ адреса из буфера в структуру
		strcpy(devices_array[i]->adress, buf);

		devices_array[i]->port = GetPrivateProfileInt(name_dev_array[i], "port", -1, "../settings/conf.ini"); //берем порт прибора, заносим в структуру
		devices_array[i]->sock_dev = sock_array[i]; //берем сокет прибора, заносим в структуру
		stop
	}
	////////

	connectionServer(devices_array[0]); // открываем соединение, ждем подключени€ клиента

	//принимаем сообщение с клиента
	/*char read_buffer[128];
	int res=recv(misha_sock, read_buffer, sizeof(read_buffer), 0); 
	stop
	for (int i=0;i<res;i++)
	{
		cout << read_buffer[i];
	}
	cout << endl;
	stop
	//ќтправл€ем сообщение на клиент
	const char* message = "Misha NE pidr!";
	if (send(misha_sock, message, strlen(message), 0))
	{
		cout << "Message has been sent!" << endl;
	}
	stop
	*/
	system("pause");
	////////
	////////«акрываем сокеты
	for (int i = 0; i < COUNT_DEVICE; i++)
	{
		closesocket(*sock_array[i]);
	}
	////////чистка пам€ти
	for (int i = 0; i < COUNT_DEVICE; i++)
	{
		delete[] devices_array[i];
	}
	delete[] devices_array;

	return 0;
}
