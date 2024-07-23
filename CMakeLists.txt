cmake_minimum_required(VERSION 3.27)
project(UDP_Sender_and_Receiver)


set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++")
set(CMAKE_EXE_LINKER_FLAGS "--static")

add_executable(UDP_Sender_and_Receiver main.cpp udp_sender.cpp udp_sender.h udp_receiver.cpp udp_receiver.h)
target_link_libraries(UDP_Sender_and_Receiver ws2_32)