#include <windows.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

int main()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) == 0) {
        std::cout << "WSAStartup\n";
    }

    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket) {
        std::cout << "listenSocket\n";
    }

    sockaddr_in socketAdress;
    socketAdress.sin_family = AF_INET;
    socketAdress.sin_addr.s_addr = inet_addr("192.168.178.20");
    socketAdress.sin_port = htons(6969);
    if (bind(listenSocket, (SOCKADDR*)&socketAdress, sizeof(sockaddr)) == 0) {
        std::cout << "bind\n";
    }

    if (listen(listenSocket, 1) == 0) {
        std::cout << "listen\n";
    }

    SOCKET clientSocket = accept(listenSocket, 0, 0);
    if (clientSocket) {
        std::cout << "client connected\n";
    }


    char buffer[2];
    while (1) {
        if (recv(clientSocket, buffer, sizeof(buffer), 0) > 0) {
            INPUT input;
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = buffer[0];
            input.ki.wScan = 0;
            input.ki.dwFlags = 0;
            input.ki.time = 0;
            input.ki.dwExtraInfo = 0;
            if (buffer[1] == 'B') {
                input.ki.dwFlags = KEYEVENTF_KEYUP;
            }

            SendInput(1, &input, sizeof(input));
        }
    }
}
