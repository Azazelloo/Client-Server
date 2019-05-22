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
	char RecvBuffer[massSize] = { 0 }; //для принятия сообщения от клинета
	char SendBuffer[massSize] = { 0 }; //для отправки сообщения от клинету
	GetDir();
	setlocale(LC_ALL, "Russian");

	//if (!InitializationOscilloscope(namedir)) {
	//	printf("Ошибка при инициализации осциллографа\n");
	//	getchar();
	//	return 1;
	//}

	printf("Ожидание соединения...\n");
	ConnectDetection(namedir);

	MessageReceiving(RecvBuffer); //ожидание сообщения от клиента
	while (strcmp(RecvBuffer, "CLCONNECT")) {
		if (IsQuestion(RecvBuffer)) {
			if (!OscillMsgExchange(RecvBuffer, SendBuffer)) { //обмен сообщениями с осциллографом
				std::cout << "Отправлено на осциллограф: " << RecvBuffer << "\n";
				std::cout << "Принято от осциллографа: " << "Ошибка в команде" << "\n";
				MessageSending("Ошибка в команде"); //отправка сообщения клиенту
			}
			else {
				std::cout << "Отправлено на осциллограф: " << RecvBuffer << "\n";
				std::cout << "Принято от осциллографа: " << SendBuffer << "\n";
				MessageSending(SendBuffer); //отправка сообщения клиенту
			}
		}
		else
			if (!OscillMsgSend(RecvBuffer)) //отправка сообщения осциллографу
				std::cout << "Отправлено на осциллограф: " << RecvBuffer << "	!!!Ошибка в команде!!!\n";
			else
				std::cout << "Отправлено на осциллограф: " << RecvBuffer << "\n";
		
		memset(RecvBuffer, 0, sizeof(RecvBuffer));
		memset(SendBuffer, 0, sizeof(SendBuffer));
		MessageReceiving(RecvBuffer);
	}
	ConnectClose();
	std::cout << "Соединение закрыто\n";

	return 0;
}

void GetDir() { //Запись директории ini-файла
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

bool IsQuestion(char *RecvBuffer) { //устанавливает, есть ли в сообщении знак вопроса
	for (int i = 0; i <= massSize; i++)
		if (RecvBuffer[i] == '?')
			return true;
	return false;
}