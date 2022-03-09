#include <windows.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

SOCKET clientSocket;
sockaddr_in sockAddress;

LRESULT CALLBACK hookFunction(int code, WPARAM wParam, LPARAM lParam) {

	KBDLLHOOKSTRUCT* key = (KBDLLHOOKSTRUCT*)lParam;

	char vkchar = (char)MapVirtualKey(key->vkCode, MAPVK_VK_TO_CHAR);
	
	if (vkchar == 'W' || vkchar == 'A' || vkchar == 'S' || vkchar == 'D' || vkchar == 'E') {
		char buffer[2];

		buffer[0] = vkchar;
		buffer[1] = 'A';
		if (wParam == WM_KEYUP) {
			buffer[1] = 'B';
		}
		send(clientSocket, buffer, sizeof(buffer), 0);
		return -1;
	}
	else {
		return CallNextHookEx(0, code, wParam, lParam);
	}
}

int main() {

	HINSTANCE instance = GetModuleHandle(0);
	HHOOK hock = SetWindowsHookEx(WH_KEYBOARD_LL, hookFunction, instance, 0);
	
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) == 0) {
		std::cout << "WSAStartup\n";
	}

	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket) {
		std::cout << "clientSocket\n";
	}

	sockAddress.sin_family = AF_INET;
	sockAddress.sin_addr.s_addr = inet_addr("192.168.178.20");
	sockAddress.sin_port = htons(6969);
	if (connect(clientSocket, (SOCKADDR*)&sockAddress, sizeof(sockAddress)) == 0) {
		std::cout << "connected to server\n";
	}

	MSG msg;
	while (1) {
		PeekMessage(&msg, 0, 0, 0, PM_REMOVE);
		Sleep(1);
	}
	return 0;
}
