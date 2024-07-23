#ifndef UDP_SERVER_UDP_SENDER_H
#define UDP_SERVER_UDP_SENDER_H

#include <ws2tcpip.h>

class Udp_Sender
{
public:
    Udp_Sender(WORD windows_socket_version, const char* address, unsigned short port)
            : w_sock_ver{windows_socket_version}, addr{address}, my_port{port}
    {
        WSA_Start(w_sock_ver);
        Create_Socket();
        Enable_Broadcast_Option();
        Set_Broadcast_Address_Port();
        SendMessage();
        Close();
    }

    void WSA_Start(WORD version) const;

    void Create_Socket();

    void Enable_Broadcast_Option() const;

    void Set_Broadcast_Address_Port();

    void SendMessage() const;

    void Close() const;

private:
    SOCKET my_socket{};
    WORD w_sock_ver{};
    sockaddr_in server_address{};
    const char* addr{};
    const unsigned short my_port{};
};


#endif //UDP_SERVER_UDP_SENDER_H
