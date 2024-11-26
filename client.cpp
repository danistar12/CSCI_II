#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h> // For inet_addr

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    const int PORT = 8080;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return 1;
    }

    // Create socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
        WSACleanup();
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert the IP address from text to binary form using inet_addr
    const char* ipAddress = "127.0.0.1";
    serv_addr.sin_addr.s_addr = inet_addr(ipAddress);
    if (serv_addr.sin_addr.s_addr == INADDR_NONE) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed" << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Ask the user for the state abbreviation
    std::string stateAbbreviation;
    std::cout << "Enter state abbreviation: ";
    std::cin >> stateAbbreviation;

    // Send the state abbreviation to the server
    send(sock, stateAbbreviation.c_str(), stateAbbreviation.length(), 0);

    // Read the response from the server
    int valread = recv(sock, buffer, 1024, 0);
    std::string stateName(buffer, valread);
    std::cout << "State name: " << stateName << std::endl;

    // Close the socket
    closesocket(sock);
    WSACleanup();

    return 0;
}
