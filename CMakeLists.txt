cmake_minimum_required(VERSION 3.2)
project(pong)
#include_directories("./_include")


find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(EXECUTABLE_NAME "pong")
set(CMAKE_CXX_FLAGS "-g -DPONG_INTERNAL -DPONG_SLOW -I/usr/include/SDL2 -D_REENTRANT -L/usr/lib -pthread -lSDL2")

file(GLOB HEADERS "*.hpp")
file(GLOB SOURCES "*.cpp")
add_executable(${EXECUTABLE_NAME} ${HEADERS} ${SOURCES})


target_link_libraries(${EXECUTABLE_NAME} sfml-system sfml-window sfml-graphics ${SDL2_LIBRARIES})
