#include "udp_sender.h"
#include <iostream>

void Udp_Sender::WSA_Start(WORD version) const
{
    // 1- start WSAStartup
    WSADATA data;
    int wsaStartup = WSAStartup(version, &data);
    if(wsaStartup != 0) {
        std::cout << "Can not start WSAStartup! Error code: " << wsaStartup << std::endl;
        throw std::runtime_error("WSAStartup failed");
    }
}

void Udp_Sender::Create_Socket()
{
    // 2- create socket
    my_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if(my_socket == INVALID_SOCKET) {
        std::cout << "Can not create socket! Error code: " << WSAGetLastError() << std::endl;
        WSACleanup();
        throw std::runtime_error("Socket creation failed");
    }
}

void Udp_Sender::Enable_Broadcast_Option() const
{
    // 3- Enable broadcast option
    BOOL broadcast = TRUE;
    if(setsockopt(my_socket, SOL_SOCKET, SO_BROADCAST, (char*) &broadcast, sizeof(broadcast)) == SOCKET_ERROR) {
        std::cout << "Failed to enable broadcast option. Error code: " << WSAGetLastError() << std::endl;
        closesocket(my_socket);
        WSACleanup();
        throw std::runtime_error("Failed to enable broadcast option");
    }
}

void Udp_Sender::Set_Broadcast_Address_Port()
{
    // 4- specify the broadcast address and port
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(my_port); // Broadcast port
    inet_pton(AF_INET, addr, &server_address.sin_addr); // Broadcast IP address
}

void Udp_Sender::SendMessage() const
{
    // 5- prepare and send the message
    std::string message;
    while(true) {
        std::cout << "Enter a message to send (or type 'exit' to quit): ";
        std::getline(std::cin, message);

        int sendResult = sendto(my_socket, message.c_str(), static_cast<int>(message.size() + 1), 0,
                                (sockaddr*) &server_address,
                                sizeof(server_address));
        if(sendResult == SOCKET_ERROR) {
            std::cout << "Error sending message. Error code: " << WSAGetLastError() << std::endl;
        }
        else if(message == "exit") {
            break;
        }
        else {
            std::cout << "Message sent: " << message << std::endl;
        }
    }
}

void Udp_Sender::Close() const
{
    // 6- close socket
    closesocket(my_socket);

    // 7- shutdown WSA
    WSACleanup();
}
