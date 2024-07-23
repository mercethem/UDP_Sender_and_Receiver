#ifndef UDP_SERVER_UDP_RECEIVER_H
#define UDP_SERVER_UDP_RECEIVER_H

#include <ws2tcpip.h>

class Udp_Receiver
{
public:
    Udp_Receiver(WORD windows_socket_version, unsigned short port)
            : w_sock_ver(windows_socket_version), my_port(port)
    {
        WSA_Start(w_sock_ver);
        Create_Socket();
        Server_Connection(port);
        Bind_Socket_And_Address();
        Message();
        Close();
    }

    void WSA_Start(WORD version) const;

    void Server_Connection(unsigned short myport);

    void Create_Socket() const;

    void Bind_Socket_And_Address() const;

    void Message() const;

    void Close() const;

private:
    SOCKET my_socket{};
    sockaddr_in server{};
    WORD w_sock_ver{};
    const unsigned short my_port{};
};

#endif //UDP_SERVER_UDP_RECEIVER_H