cmake_minimum_required(VERSION 3.30)
project(Creolio)

set(CMAKE_CXX_STANDARD 20)
find_package(dpp CONFIG REQUIRED)
add_executable(Creolio main.cpp
        BotStuff.cpp
        BotStuff.h)
target_link_libraries(${PROJECT_NAME} PRIVATE dpp::dpp)
