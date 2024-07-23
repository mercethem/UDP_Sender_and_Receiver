#include <iostream>
#include "udp_sender.h"
#include "udp_receiver.h"

#define PORT 8081
#define SOCKET_VERSION MAKEWORD(2, 2)
#define ADDRESS "255.255.255.255"

int main()
{
    std::cout << "SERVER(0)" << "\n" << "RECEIVER(1)" << "\n" << "EXIT(ELSE)" << std::endl;
    std::string choose{};
    std::cin >> choose;
    if(choose == "1") {
        try {
            Udp_Receiver receiver(SOCKET_VERSION, PORT);
        }
        catch(const std::exception &exception) {
            std::cerr << "Exception occurred: " << exception.what() << std::endl;
        }
    }
    else if(choose == "0") {
        try {
            Udp_Sender sender(SOCKET_VERSION, ADDRESS, PORT);
        }
        catch(const std::exception &exception) {
            std::cerr << "Exception occurred: " << exception.what() << std::endl;
        }
    }
    else {
        exit(EXIT_SUCCESS);
    }


    return 0;
}
