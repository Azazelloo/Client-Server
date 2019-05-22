#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "AgInfiniiVision.lib")

#include <WinSock2.h>
#include <iostream>
#include "AgInfiniiVision.h"
#include "Oscill.h"
#include "Connection.h"
#include "Header.h"

static char namedir[massSize];
void GetDir();
bool IsQuestion(char *RecvBuffer);

int main() {
	char RecvBuffer[massSize] = { 0 }; //��� �������� ��������� �� �������
	char SendBuffer[massSize] = { 0 }; //��� �������� ��������� �� �������
	GetDir();
	setlocale(LC_ALL, "Russian");

	//if (!InitializationOscilloscope(namedir)) {
	//	printf("������ ��� ������������� ������������\n");
	//	getchar();
	//	return 1;
	//}

	printf("�������� ����������...\n");
	ConnectDetection(namedir);

	MessageReceiving(RecvBuffer); //�������� ��������� �� �������
	while (strcmp(RecvBuffer, "CLCONNECT")) {
		if (IsQuestion(RecvBuffer)) {
			if (!OscillMsgExchange(RecvBuffer, SendBuffer)) { //����� ����������� � �������������
				std::cout << "���������� �� �����������: " << RecvBuffer << "\n";
				std::cout << "������� �� ������������: " << "������ � �������" << "\n";
				MessageSending("������ � �������"); //�������� ��������� �������
			}
			else {
				std::cout << "���������� �� �����������: " << RecvBuffer << "\n";
				std::cout << "������� �� ������������: " << SendBuffer << "\n";
				MessageSending(SendBuffer); //�������� ��������� �������
			}
		}
		else
			if (!OscillMsgSend(RecvBuffer)) //�������� ��������� ������������
				std::cout << "���������� �� �����������: " << RecvBuffer << "	!!!������ � �������!!!\n";
			else
				std::cout << "���������� �� �����������: " << RecvBuffer << "\n";
		
		memset(RecvBuffer, 0, sizeof(RecvBuffer));
		memset(SendBuffer, 0, sizeof(SendBuffer));
		MessageReceiving(RecvBuffer);
	}
	ConnectClose();
	std::cout << "���������� �������\n";

	return 0;
}

void GetDir() { //������ ���������� ini-�����
	char name[massSize*2] = { 0 };

	int j = GetModuleFileName(GetModuleHandle(NULL), (LPWSTR)name, massSize) - 1;

	for (int i = 0; i < massSize; i++)
		namedir[i] = name[i * 2];
	j = sizeof(namedir) - 1;
	do {
		if (namedir[j] == '\\')
			break;
		namedir[j] = 0;
	} while (--j);
	j++;
	char nameIni[] = { "options.ini" };
	for (int i = 0; i < sizeof(nameIni); i++) {
		namedir[j + i] = nameIni[i];
	}
}

bool IsQuestion(char *RecvBuffer) { //�������������, ���� �� � ��������� ���� �������
	for (int i = 0; i <= massSize; i++)
		if (RecvBuffer[i] == '?')
			return true;
	return false;
}