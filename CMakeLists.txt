cmake_minimum_required(VERSION 3.10)

project(HelloWorld)

find_package(SDL2 CONFIG REQUIRED)

add_executable(HelloWorld src/main.cpp)

target_link_libraries(HelloWorld PRIVATE SDL2)