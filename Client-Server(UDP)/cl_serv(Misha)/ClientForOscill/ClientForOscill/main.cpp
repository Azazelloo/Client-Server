#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h>
#include <iostream>
#include "Connection.h"
#include "Header.h"

static char namedir[massSize];
void GetDir();
bool IsQuestion(char *RecvBuffer);

int main() {
	GetDir();
	char SendBuffer[massSize] = { 0 }; //для отправки сообщения серверу
	char RecvBuffer[massSize] = ""; //для принятия сообщения от сервера
	int i;

	setlocale(LC_ALL, "Russian");
	if (ConnectDetection(namedir)) {
		std::cout << "Соединение не было установлено!\n";
		return 1;
	}
	while (strcmp(SendBuffer, "CLCONNECT")) {
		memset(SendBuffer, 0, sizeof(RecvBuffer));
		memset(RecvBuffer, 0, sizeof(RecvBuffer));
		printf("Введите команду: ");
		std::cin.getline(SendBuffer, massSize);

		for (i = sizeof(SendBuffer) - 1; i >= 0; i--) {
			if (SendBuffer[i] == '\\') {
				SendBuffer[i] = '\n';
				SendBuffer[i + 1] = 0;
				break;
			}
		}
		MessageSending(SendBuffer);
		if (IsQuestion(SendBuffer)) {
			MessageReceiving(RecvBuffer);
			std::cout << "Ответ:		" << RecvBuffer << "\n";
		}
	}
	ConnectClose();
	std::cout << "Соединение закрыто\n";

	return 0;
}

void GetDir() { //Запись директории ini-файла
	char name[massSize * 2] = { 0 };

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

bool IsQuestion(char *SendBuffer) { //устанавливает, есть ли в сообщении знак вопроса
	for (int i = 0; i <= massSize; i++)
		if (SendBuffer[i] == '?')
			return true;
	return false;
}