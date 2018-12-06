cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 14)
project(cpp_chat_application)

add_library(server src/server.cpp)

add_executable(maMain src/main.cpp)

target_link_libraries(maMain server pthread)
