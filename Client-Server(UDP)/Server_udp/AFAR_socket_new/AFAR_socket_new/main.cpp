#include "Header.h"

DEVICE** devices_array=new DEVICE*[COUNT_DEVICE];
SOCKET sp_sock, gen_sock, sa_sock;

SOCKET sock_array[COUNT_DEVICE] = { sp_sock, gen_sock, sa_sock }; //������ ������� 
const char* name_dev_array[COUNT_DEVICE] = { "source_power","generator","signal_anal" };

int main(int argc, char* argv[])
{	
	////////������ ini ����
	char buf[128];
	for (int i=0;i<COUNT_DEVICE;i++)
	{
		devices_array[i] = new DEVICE;
		stop
		GetPrivateProfileString(name_dev_array[i], "adress", "Error!", devices_array[i]->adress, sizeof(devices_array[i]->adress), "../settings/conf.ini"); //����� ����� �������, ������� � ���������

		stop
		devices_array[i]->port = GetPrivateProfileInt(name_dev_array[i], "port", -1, "../settings/conf.ini"); //����� ���� �������, ������� � ���������
		devices_array[i]->sock_dev = sock_array[i]; //����� ����� �������, ������� � ���������
		stop
	}
	////////

	////////������������ � ��������
	for (int i=0;i<COUNT_DEVICE;i++)
	{

		cout << name_dev_array[i] << ":" << endl;
		int res = connection(devices_array[i]->adress, devices_array[i]->port, &devices_array[i]->sock_dev);

		if (res>0)
		{
			cout << " ----------------- connected!" << endl;
		}
		else
		{
			cout << " ----------------- not connected!" << endl;
		}
	}
	////////

	////////�������������� �����
	cout << endl << read("*IDN?\n", &sp_sock) << endl << read("*IDN?\n", &gen_sock) << endl << read("*IDN?\n", &sa_sock) << endl;

	system("pause");
	////////
	////////��������� ������
	for (int i = 0; i < COUNT_DEVICE; i++)
	{
		closesocket(sock_array[i]);
	}
	////////������ ������
	for (int i=0;i<COUNT_DEVICE;i++)
	{
		delete[] devices_array[i];
	}
	delete[] devices_array;

	return 0;
}
