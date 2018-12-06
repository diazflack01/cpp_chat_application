cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 14)
project(cpp_chat_application)

add_library(server src/server.cpp)

add_library(client src/client.cpp)

add_executable(maServer src/server_main.cpp)
target_link_libraries(maServer server pthread)

add_executable(maClient src/client_main.cpp)
target_link_libraries(maClient client pthread)
