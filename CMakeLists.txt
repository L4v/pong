cmake_minimum_required(VERSION 3.2)
project(pong)
#include_directories("./_include")

find_package(SDL2 REQUIRED)

set(EXECUTABLE_NAME "pong")
set(CMAKE_CXX_FLAGS "-g -DPONG_INTERNAL -DPONG_SLOW -lSDL2 -lGL -lGLU")

file(GLOB HEADERS "*.hpp")
file(GLOB SOURCES "*.cpp")
add_executable(${EXECUTABLE_NAME} ${HEADERS} ${SOURCES})


target_link_libraries(${EXECUTABLE_NAME})
