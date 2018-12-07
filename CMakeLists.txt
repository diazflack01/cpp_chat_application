cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

project(cpp_chat_application)

#For include of generated files
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#Auto generate moc
set(CMAKE_AUTOMOC ON)

#Auto generate ui_*.h/ui_*.cpp files from .ui
set(CMAKE_AUTOUIC ON)

#Find package
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_library(server src/server.cpp)

add_library(client src/client.cpp)

add_executable(maServer src/server_main.cpp)
target_link_libraries(maServer server pthread)

add_executable(maClient src/client_main.cpp src/mainwindow.ui src/form.ui)
target_link_libraries(maClient
    client
    pthread
    Qt5::Core
    Qt5::Widgets
)
