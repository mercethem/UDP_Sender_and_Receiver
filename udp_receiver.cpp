#include "udp_receiver.h"
#include <iostream>

void Udp_Receiver::WSA_Start(WORD version) const
{
    // 1- Start WSAStartup
    WSADATA data;
    int wsaStartup = WSAStartup(version, &data);
    if(wsaStartup != 0) {
        std::cout << "Can not start WSAStartup! Error code: " << wsaStartup << std::endl;
        throw std::runtime_error("WSAStartup failed");
    }
}

void Udp_Receiver::Server_Connection(unsigned short myport)
{
    // Create a hint structure for the server
    my_socket = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(myport);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
}

void Udp_Receiver::Create_Socket() const
{
    // Socket creation
    if(my_socket == INVALID_SOCKET) {
        std::cout << "Socket creation failed! Error code: " << WSAGetLastError() << std::endl;
        WSACleanup();
        throw std::runtime_error("Socket creation failed");
    }
}

void Udp_Receiver::Bind_Socket_And_Address() const
{
    // Bind the socket to the address and port
    if(bind(my_socket, (sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
        std::cout << "Bind failed! Error code: " << WSAGetLastError() << std::endl;
        closesocket(my_socket);
        WSACleanup();
        throw std::runtime_error("Bind failed");
    }
}

void Udp_Receiver::Message() const
{
    std::cout << "Waiting for messages..." << " My Port: " << my_port << std::endl;
    while(true) {
        sockaddr_in client{};
        int clientLength = sizeof(client);
        ZeroMemory(&client, clientLength); // Clear the client structure

        char buffer[1024];
        ZeroMemory(buffer, 1024); // Clear the receive buffer

        int bytesReceived = recvfrom(my_socket, buffer, sizeof(buffer) - 1, 0, (sockaddr*) &client, &clientLength);
        if(bytesReceived == SOCKET_ERROR) {
            std::cout << "recvfrom failed! Error code: " << WSAGetLastError() << std::endl;
        }
        else {
            char clientIp[256]; // Create enough space to convert the address byte array
            ZeroMemory(clientIp, 256);
            inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);

            buffer[bytesReceived] = '\0';
            std::cout << "Received message from " << clientIp << " : " << buffer << std::endl;

            std::string message(buffer);
            if(message == "exit") {
                break;
            }
        }
    }
}

void Udp_Receiver::Close() const
{
    closesocket(my_socket);
    WSACleanup();
}

