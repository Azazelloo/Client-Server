#include "Header.h"

DEVICE** devices_array = new DEVICE*[COUNT_DEVICE];//выделяем память под массив устройств

SOCKET misha_sock;
SOCKET* sock_array[COUNT_DEVICE] = { &misha_sock }; //массив сокетов 

const char* name_dev_array[COUNT_DEVICE] = { "Server_adress" };

int main(int argc, char* argv[])
{
	////////Читаем ini файл
	char buf[128];
	for (int i = 0; i < COUNT_DEVICE; i++)
	{
		devices_array[i] = new DEVICE;//выделяем память под текущее устройство
		stop
			GetPrivateProfileString(name_dev_array[i], "adress", "Error!", buf, sizeof(buf), "../settings/conf.ini"); //берем адрес прибора, заносим в структуру
		devices_array[i]->adress = new char[strlen(buf) + 1];//выделяем память для копирования адреса из буфера в структуру
		strcpy(devices_array[i]->adress, buf);

		devices_array[i]->port = GetPrivateProfileInt(name_dev_array[i], "port", -1, "../settings/conf.ini"); //берем порт прибора, заносим в структуру
		devices_array[i]->sock_dev = sock_array[i]; //берем сокет прибора, заносим в структуру
		stop
	}
	////////

	connectionServer(devices_array[0]); // открываем соединение, ждем подключения клиента


	system("pause");
	////////Закрываем сокеты
	/*for (int i = 0; i < COUNT_DEVICE; i++)
	{
		closesocket(*sock_array[i]);
	}
	////////чистка памяти
	for (int i = 0; i < COUNT_DEVICE; i++)
	{
		delete[] devices_array[i];
	}
	delete[] devices_array;*/

	return 0;
}
