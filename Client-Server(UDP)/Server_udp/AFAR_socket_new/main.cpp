#include "Header.h"

DEVICE** devices_array = new DEVICE*[COUNT_DEVICE];//�������� ������ ��� ������ ���������

SOCKET misha_sock;
SOCKET* sock_array[COUNT_DEVICE] = { &misha_sock }; //������ ������� 

const char* name_dev_array[COUNT_DEVICE] = { "Server_adress" };

int main(int argc, char* argv[])
{
	////////������ ini ����
	char buf[128];
	for (int i = 0; i < COUNT_DEVICE; i++)
	{
		devices_array[i] = new DEVICE;//�������� ������ ��� ������� ����������
		stop
			GetPrivateProfileString(name_dev_array[i], "adress", "Error!", buf, sizeof(buf), "../settings/conf.ini"); //����� ����� �������, ������� � ���������
		devices_array[i]->adress = new char[strlen(buf) + 1];//�������� ������ ��� ����������� ������ �� ������ � ���������
		strcpy(devices_array[i]->adress, buf);

		devices_array[i]->port = GetPrivateProfileInt(name_dev_array[i], "port", -1, "../settings/conf.ini"); //����� ���� �������, ������� � ���������
		devices_array[i]->sock_dev = sock_array[i]; //����� ����� �������, ������� � ���������
		stop
	}
	////////

	connectionServer(devices_array[0]); // ��������� ����������, ���� ����������� �������


	system("pause");
	////////��������� ������
	/*for (int i = 0; i < COUNT_DEVICE; i++)
	{
		closesocket(*sock_array[i]);
	}
	////////������ ������
	for (int i = 0; i < COUNT_DEVICE; i++)
	{
		delete[] devices_array[i];
	}
	delete[] devices_array;*/

	return 0;
}
