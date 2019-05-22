#include "Header.h"

DEVICE** devices_array = new DEVICE*[COUNT_DEVICE];//�������� ������ ��� ������ ���������

SOCKET sp_sock, gen_sock, sa_sock,misha_sock;
SOCKET* sock_array[COUNT_DEVICE] = { &misha_sock }; //������ ������� 

const char* name_dev_array[COUNT_DEVICE] = {"misha" };

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
	int res = connectionClient(devices_array[0]);
	while (res!=1)
	{	
		Sleep(1);
		res = connectionClient(devices_array[0]);
	}

	//�������� ��������� �� ������
	/*char* command = new char[strlen("Exit")+1];
	char read_buffer[128];
	while(strcmp(command,"exit"))
	{
		cout<<endl << "Enter command: "; cin >> command;
		stop
		if (send(misha_sock, command, strlen(command), 0))
		{
			cout << "Command has been sent!" << endl;
			//������� ����� �� �������
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
	//��������� ��������� � �������
	/*char read_buffer[128];
	cout << "In_message:";
	int res2=recv(misha_sock, read_buffer, sizeof(read_buffer), 0);
	for (int i = 0; i < res2; i++)
	{
		cout << read_buffer[i];
	}
	cout << endl;*/

	stop
	////////
	
	stop 
	system("pause");
	////////
	////////��������� ������
	for (int i = 0; i < COUNT_DEVICE; i++)
	{
		closesocket(*sock_array[i]);
	}
	////////������ ������
	for (int i = 0; i < COUNT_DEVICE; i++)
	{
		delete[] devices_array[i];
	}
	delete[] devices_array;

	return 0;
}
