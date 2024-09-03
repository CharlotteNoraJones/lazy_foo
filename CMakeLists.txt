cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME HelloSDL2)

project(${PROJECT_NAME} LANGUAGES CXX)

find_package(SDL2 CONFIG REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
CXX_STANDARD 20
CXX_STANDARD_REQUIRED YES
CXX_EXTENSIONS OFF)

target_link_libraries(${PROJECT_NAME} PRIVATE
$<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
$<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)