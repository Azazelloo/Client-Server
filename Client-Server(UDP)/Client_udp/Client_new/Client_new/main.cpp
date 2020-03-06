#include "Header.h"

DEVICE** devices_array = new DEVICE*[COUNT_DEVICE];//выделяем память под массив устройств

SOCKET sp_sock, gen_sock, sa_sock,misha_sock;
SOCKET* sock_array[COUNT_DEVICE] = { &misha_sock }; //массив сокетов 

const char* name_dev_array[COUNT_DEVICE] = {"misha" };

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
	////////Устанавливаем соединение
	int res = connectionClient(devices_array[0]);
	while (res!=1)
	{	
		Sleep(1000);
		res = connectionClient(devices_array[0]);
	}

	//посылаем сообщение на сервер
	/*char* command = new char[strlen("Exit")+1];
	char read_buffer[128];
	while(strcmp(command,"exit"))
	{
		cout<<endl << "Enter command: "; cin >> command;
		stop
		if (send(misha_sock, command, strlen(command), 0))
		{
			cout << "Command has been sent!" << endl;
			//ожидаем ответ от сервера
			int r_buf = recv(misha_sock, read_buffer, sizeof(read_buffer), 0);
			cout << "Server: ";
			for (int i = 0; i < r_buf; i++)
			{
				cout << read_buffer[i];
			}
			cout << endl;
			
		}
	}*/
	////////
	//Принимаем сообщение с сервера
	/*char read_buffer[128];
	cout << "In_message:";
	int res2=recv(misha_sock, read_buffer, sizeof(read_buffer), 0);
	for (int i = 0; i < res2; i++)
	{
		cout << read_buffer[i];
	}
	cout << endl;*/

	system("pause");
	////////
	////////Закрываем сокеты
	for (int i = 0; i < COUNT_DEVICE; i++)
	{
		closesocket(*sock_array[i]);
	}
	////////чистка памяти
	for (int i = 0; i < COUNT_DEVICE; i++)
	{
		delete[] devices_array[i];
	}
	delete[] devices_array;

	return 0;
}
