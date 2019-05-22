#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <string>
#include <thread> 


#define PORT 5025
#define SOURCE_POWER "192.168.0.102"
#define GENERATOR "192.168.0.103"
#define SA "192.168.0.104"

#define IDN "*IDN?"
#define SP_BLOCK "SYSTem:COMMunicate:RLSTate REMOTE"
#define SP_VOLT ":SOURce:VOLTage:LEVel:IMMediate:AMPLitude"
#define SP_AMP ":SOURce:CURRent:LEVel:IMMediate:AMPLitude"
#define SP_ON "OUTPUT ON"
#define SP_OFF "OUTPUT OFF"
#define VOLT " 24"
#define AMP " 8"
#define GEN_FREQ ":FREQ"
#define GEN_POW ":POW"
#define GEN_RF_ON ":OUTPUT ON"
#define GEN_RF_OFF ":OUTPUT OFF"
#define FREQ " 100 MHZ"
#define POW " 0 dbm"
#define SA_TRIG ":TRIG:SOUR EXT1"

///////Файл с настройками ППМ////
/*char *ADRESS_KP = "192.168.1.221:1024";
double NUMBER_PPM = 1;
double POLOSA = 1;
double ATT_PRIEM_1 = 63;
double ATT_PRIEM_2 = 63;
double ATT_PRIEM_3 = 63;
double ATT_PRIEM_4 = 63;
double ATT_PEREDAT_1 = 31.5;
double ATT_PEREDAT_2 = 31.5;
double ATT_PEREDAT_3 = 31.5;
double ATT_PEREDAT_4 = 31.5;
double FREQ = 8500;
double REG_PRIEM_1 = 0;
double REG_PRIEM_2 = 0;
double REG_PRIEM_3 = 0;
double REG_PRIEM_4 = 0;
double REG_PEREDAT_1 = 1;
double REG_PEREDAT_2 = 0;
double REG_PEREDAT_3 = 0;
double REG_PEREDAT_4 = 0;
double IMP = 0;
double DLIT = 10;
double PERIOD = 100;*/

////////////////////////////////

#pragma comment(lib,"Ws2_32.lib")

using namespace std;


SOCKET sp_sock;
SOCKET gen_sock;
SOCKET sa_sock;

char buff[2024];
float buffer;
struct sockaddr_in dest_addr;
int nsize;
int message;
HOSTENT *hst;
double massbuf[2];

bool error = false;

int connection(const char* server, int port, SOCKET *my_sock)
{
	/////////////////////////////////ФУНКЦИЯ ПОДКЛЮЧЕНИЯ К СОКЕТУ/////////////////////////////////////////
	if (WSAStartup(0x202, (WSADATA *)&buff[0])) //непонятная функция, проверить нужна ли она вообще
	{
		cout << "WSAStart error\n" << WSAGetLastError();
		error = true;
		return -1;
	}

	*my_sock = socket(AF_INET, SOCK_STREAM, 0); //создаем сокет

	if (*my_sock < 0)
	{
		cout << "Socket error " << WSAGetLastError();
		error = true;
		system("pause"); 
		return -1;
	}

	// заполнение структуры sockaddr_in указание адреса и порта сервера
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(port);
	// преобразование ip адреса из символьного в сетевой формат
	if (inet_addr(server) != INADDR_NONE)
	{
		dest_addr.sin_addr.s_addr = inet_addr(server);
	}
	else
	if (hst = gethostbyname(server)) // попытка получить ip адрес по доменному имени сервера
		// hst->h_addr_list содержит не массив адресов а массив указателей на адреса
		((unsigned long *)&dest_addr.sin_addr)[0] = ((unsigned long **)hst->h_addr_list)[0][0];
	else
	{
		cout << "Invalid address " << server;
		closesocket(*my_sock);
		//WSACleanup();
		error = true;
		return -1;
	}

	//  адрес сервера получен_ пытаемся установить соединение
	if (connect(*my_sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr)))
	{
		closesocket(*my_sock);
		error = true;
		cout << "Connect with adress "<< server <<" error "<<endl;//<< WSAGetLastError();
		return -1;
	}
	cout << "Connect is done " << server << endl;
}

void OnlyWrite(const char* command, SOCKET *my_sock)
{
	send(*my_sock, command, strlen(command) + 1, 0);
}

char* WriteAndRead(const char* command, SOCKET *my_sock)
{
	send(*my_sock, command, strlen(command) + 1, 0);

	if ((nsize = recv(*my_sock, buff, sizeof(buff), 0)) == SOCKET_ERROR)
	{
		cout << "Recv error \n" <<endl;
		closesocket(*my_sock);
		//WSACleanup();
		return 0;
	}
	else
	{
		buff[nsize] = 0;
	}
	
	return buff;
}

char* editCommand(char *command, char* parametr, SOCKET *my_sock, int flag)
{
	char rez_array[100]="";
	strcat(rez_array,command);
	strcat(rez_array,parametr);
	strcat(rez_array,"\n");
	if (flag == 1)
	{
		OnlyWrite(rez_array, my_sock);
	}
	if (flag == 2)
	{
		return WriteAndRead(rez_array, my_sock);
	}
}

int main(int argc, char* argv[])
{
	//setlocale(LC_ALL, "Russian");
	
	connection(SOURCE_POWER, PORT, &sp_sock);
	if (error==false)
	{
		connection(GENERATOR, PORT, &gen_sock);
		if (error==false)
		{
			connection(SA,PORT,&sa_sock);
			if (error==false)
			{
				////////////////////////////////////
				cout << "[Source Power]" << endl << editCommand("*IDN","?",&sp_sock,2) << endl;//подключились к ИП
				editCommand(SP_BLOCK,"",&sp_sock,1); //заблокировали клавиши ИП
				editCommand(SP_VOLT,VOLT,&sp_sock,1); //установили напряжение
				cout << "-----Voltage = " << editCommand(SP_VOLT,"?",&sp_sock,2) << endl;

				editCommand(SP_AMP,AMP,&sp_sock,1); // установили амплитуду
				cout << "-----Amplitude = " << editCommand(SP_AMP,"?",&sp_sock,2) << endl;
				editCommand(SP_ON,"",&sp_sock,1);
				cout << "-----Power = ON" << endl;

				///////////////Тест автоскейла/////////////////////
				/*cout << "[Generator]" << endl << editCommand("*IDN", "?", &gen_sock, 2) << endl;
				cout << "[SA]" << endl << editCommand("*IDN", "?", &sa_sock, 2) << endl;

				ofstream F;
				F.open("logs.txt", ios_base::ate);
				for (double i = 8500; i <= 9500; i += 50)
				{
					char new_freq[32];
					_itoa(i, new_freq, 10);
					strcat(new_freq, " "); strcat(new_freq,"MHZ");
					editCommand(GEN_FREQ, new_freq, &gen_sock, 1); //установили частоту на генераторе
					editCommand(GEN_POW, POW, &gen_sock, 1); //установили амплитуду на генераторе
					editCommand(GEN_RF_ON, "", &gen_sock, 1); // включили RF
					
					editCommand("FREQ:TUNE:IMM", "", &sa_sock, 1);
					editCommand(":POW:ATT"," 20",&sa_sock,1);
					cout << "Auto Tune ---------done" << endl;
					Sleep(5000);

					double temp_cent_freq = atof(editCommand("CALC:MARK1:X", "?", &sa_sock, 2));
					cout << "Established freq: " << fixed << i * 1000000 << endl;
					cout << "Take the frequency: " << fixed << temp_cent_freq << endl;
					cout << "Difference: " << fixed << i * 1000000 - temp_cent_freq << endl;
					F << "Take the frequency: " << fixed << temp_cent_freq << " = " << fixed << i * 1000000 - temp_cent_freq << "\n";
					Sleep(5000);
				}
				F.close();*/
				////////////////////////////////////
				cout << "[Generator]" << endl << editCommand("*IDN", "?", &gen_sock, 2) << endl;

				editCommand(GEN_FREQ,FREQ,&gen_sock,1); //установили частоту на генераторе
				cout << "-----Frequency = " << editCommand(GEN_FREQ,"?",&gen_sock,2) << endl;
				editCommand(GEN_POW,POW,&gen_sock,1); //установили амплитуду на генераторе
				cout << "-----Amplitude = " << editCommand(GEN_POW,"?",&gen_sock,2) << endl;
				editCommand(GEN_RF_ON,"",&gen_sock,1); // включили RF
				cout << "-----RF output = ON" << endl;
				///////////////////////////////////
				cout << "[SA]" << endl << editCommand("*IDN", "?", &sa_sock, 2) << endl;
				Sleep(4000);
				cout << "----------" << endl;
				/*
				ofstream F;
				F.open("logs.txt", ios_base::ate);
				for (double i = 8500; i <= 9500; i += 50)
				{
					char new_reg[32];
					_itoa(i, new_reg, 10);
					WritePrivateProfileStringA("Basic", "CarrierFreq", (LPCSTR)new_reg, "C:/Users/SVCH-1611/Desktop/Afar_PO/Calibr_and_PO/PO2/Load100_1.ini");
					system("afarLoad.exe -f1 -t0 -s1 -p1 -k1 -iLoad100_1.ini -n192.168.20.1");
					Sleep(3000);
					editCommand("FREQ:TUNE:IMM", "", &sa_sock, 1);
					OnlyWrite(SA_TRIG, &sa_sock);
					editCommand(":POW:ATT", " 20", &sa_sock, 1);
					cout << "-----SA trigger selected" << endl;
					Sleep(5000);
					cout << "Auto Tune ---------done" << endl;

					double temp_cent_freq = atof(editCommand("CALC:MARK1:X", "?", &sa_sock, 2));

					cout << "Established freq: " << fixed << i * 1000000 << endl;
					cout << "Take the frequency: " << fixed << temp_cent_freq << endl;
					cout << "Difference: " << fixed << i * 1000000 - temp_cent_freq << endl;

					F << "Take the frequency: " << fixed << temp_cent_freq << " = "<< fixed << i * 1000000 - temp_cent_freq << "\n";
					Sleep(5000);
				}
				F.close();
				*/

				///////////////////////////////////
				editCommand(":INST:SEL BASIC", "", &sa_sock, 1);
				editCommand(":CONF:WAV", "", &sa_sock, 1);
				editCommand(":DISP:WAV:VIEW IQ", "", &sa_sock, 1);
				editCommand("POW:ATT 20", "", &sa_sock, 1);

				editCommand(":TRIG:WAV:SOUR EXT1", "", &sa_sock, 1);
				editCommand(":FREQ:CENT 8500000001.58 Hz", "", &sa_sock, 1);

				system("afarLoad.exe -f1 -t0 -s1 -p1 -k1 -iLoad100_1.ini -n192.168.20.1");
				for (int i=0;i<=360;i=i+1)
				{
					char new_reg[32];
					_itoa(i, new_reg, 10);
					strcat(new_reg,".wav");
					WritePrivateProfileStringA("Basic", "tFile", (LPCSTR)new_reg, "C:/Users/SVCH-1611/Desktop/Afar_PO/Calibr_and_PO/PO2/Load100_1.ini");
					system("afarLoad.exe   -p1 -k1 -iLoad100_1.ini -n192.168.20.1");
					cout << "IQ waveform mode ----- on" << endl;
					//Sleep(2000);
					if (i == 0)
					{
						system("pause");
					}
					char new_name[32];
					_itoa(i, new_name, 10);
					strcat(new_name,".csv'");
					char command[32] = ":MMEM:STOR:RES '";
					strcat(command,new_name);
					editCommand(command, "", &sa_sock, 1);
					//Sleep(2000);
				}
				
				///////////////////////////////////
				//editCommand(":MMEMory:CDIRectory \"D:\"","",&sa_sock,1);
				//cout << editCommand(":MMEM:CDIR","?",&sa_sock,2) << endl;
				//system("pause");
				editCommand(GEN_RF_OFF,"",&gen_sock,1);//OnlyWrite(GEN_RF_OFF, &gen_sock);
				cout << "-----RF output = OFF" << endl;
				editCommand(SP_OFF,"",&sp_sock,1);//OnlyWrite(SP_OFF, &sp_sock);
				cout << "-----Power = OFF" << endl;
			}
			else
			{
				cout << "-----SA not connected" << endl;
			}
			
		}
		else
		{
			cout << "-----Generator not connected" << endl;
		}
	}
	else
	{
		cout << "-----Source Power not connected" << endl;
	}
	////////////////////////////

	closesocket(sp_sock);
	closesocket(gen_sock);
	closesocket(sa_sock);
	system("pause");
}