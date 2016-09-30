//Date: 2016.09.29
//Author: Park Jiun
#include"stdafx.h"
#pragma comment(lib, "ws2_32.lib")
#define PORT "5111"

void ErrorHandling(char* message);

void first_request(){
	WSADATA	wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAddr, clntAddr;
	int szClntAddr;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(PORT));

	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");

	if (listen(hServSock, 5) == SOCKET_ERROR)
		ErrorHandling("listen() error");

	szClntAddr = sizeof(clntAddr);
	hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr);
	if (hClntSock == INVALID_SOCKET)
		ErrorHandling("accept() error");

	int read_len;
	char num[1];
	read_len = recv(hClntSock, num, 1, 0);
	bool verify;
	switch (num[0] - '0') {
	case 0:
		char *parameterToVerify[3];
		for (int i = 0; i < 3; i++) {
			read_len = recv(hClntSock, parameterToVerify[i], sizeof(parameterToVerify[i]) - 1, 0);

			if (read_len == -1) ErrorHandling("read() error!");
		}
		std::cout << Verify(parameterToVerify);
		break;
	case 1:
		break;
	default:
		ErrorHandling("unvalid request!");
	}
	closesocket(hClntSock);
	closesocket(hServSock);
	WSACleanup();
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}