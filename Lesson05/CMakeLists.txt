cmake_minimum_required(VERSION 3.22)
project("ClientServerModel")
set(CMAKE_CXX_STANDARD 11)

add_executable(client client.cpp)
add_executable(server server.cpp)
