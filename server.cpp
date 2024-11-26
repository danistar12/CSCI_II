////////////////////////////////////////////////////////////////////////////////
//#  Program name: server.cpp                                                //
//#  Author: Danielle Lloyd                                                 //
//#  Date last updated: 11/26/2024                                         // 
//#  Purpose: Creates a connection for the client/outputs full state name //
///////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <unordered_map>
#include <string>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

std::unordered_map<std::string, std::string> createStateMap() {
    return {
        {"AL", "Alabama"}, {"AK", "Alaska"}, {"AZ", "Arizona"}, {"AR", "Arkansas"},
        {"CA", "California"}, {"CO", "Colorado"}, {"CT", "Connecticut"}, {"DE", "Delaware"},
        {"FL", "Florida"}, {"GA", "Georgia"}, {"HI", "Hawaii"}, {"ID", "Idaho"},
        {"IL", "Illinois"}, {"IN", "Indiana"}, {"IA", "Iowa"}, {"KS", "Kansas"},
        {"KY", "Kentucky"}, {"LA", "Louisiana"}, {"ME", "Maine"}, {"MD", "Maryland"},
        {"MA", "Massachusetts"}, {"MI", "Michigan"}, {"MN", "Minnesota"}, {"MS", "Mississippi"},
        {"MO", "Missouri"}, {"MT", "Montana"}, {"NE", "Nebraska"}, {"NV", "Nevada"},
        {"NH", "New Hampshire"}, {"NJ", "New Jersey"}, {"NM", "New Mexico"}, {"NY", "New York"},
        {"NC", "North Carolina"}, {"ND", "North Dakota"}, {"OH", "Ohio"}, {"OK", "Oklahoma"},
        {"OR", "Oregon"}, {"PA", "Pennsylvania"}, {"RI", "Rhode Island"}, {"SC", "South Carolina"},
        {"SD", "South Dakota"}, {"TN", "Tennessee"}, {"TX", "Texas"}, {"UT", "Utah"},
        {"VT", "Vermont"}, {"VA", "Virginia"}, {"WA", "Washington"}, {"WV", "West Virginia"},
        {"WI", "Wisconsin"}, {"WY", "Wyoming"}
    };
}

int main() {
    WSADATA wsaData;
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const int PORT = 8080;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return 1;
    }

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
        WSACleanup();
        return 1;
    }

    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) == SOCKET_ERROR) {
        std::cerr << "Setsockopt failed" << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the network address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR) {
        std::cerr << "Bind failed" << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // Start listening for incoming connections
    if (listen(server_fd, 3) == SOCKET_ERROR) {
        std::cerr << "Listen failed" << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    auto stateMap = createStateMap();

    while (true) {
        std::cout << "Waiting for a connection..." << std::endl;

        // Accept an incoming connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) == INVALID_SOCKET) {
            std::cerr << "Accept failed" << std::endl;
            closesocket(server_fd);
            WSACleanup();
            return 1;
        }

        std::cout << "Connection accepted" << std::endl;

        // Read the state abbreviation sent by the client
        int valread = recv(new_socket, buffer, 1024, 0);
        std::string stateAbbreviation(buffer, valread);
        std::cout << "Received state abbreviation: " << stateAbbreviation << std::endl;

        // Lookup the full state name
        std::string stateName = "Invalid State Abbreviation";
        auto it = stateMap.find(stateAbbreviation);
        if (it != stateMap.end()) {
            stateName = it->second;
        }

        // Send back the full state name to the client
        send(new_socket, stateName.c_str(), stateName.length(), 0);
        std::cout << "Sent state name: " << stateName << std::endl;

        // Close the connection to the client
        closesocket(new_socket);
    }

    // Cleanup Winsock
    closesocket(server_fd);
    WSACleanup();

    return 0;
}
