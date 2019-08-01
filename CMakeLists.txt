cmake_minimum_required(VERSION 3.2)
project(pong)
#include_directories("./_include")


set(EXECUTABLE_NAME "pong")
set(CMAKE_CXX_FLAGS "-DPONG_INTERNAL -DPONG_SLOW")

file(GLOB HEADERS "*.hpp")
file(GLOB SOURCES "*.cpp")
add_executable(${EXECUTABLE_NAME} ${HEADERS} ${SOURCES})


target_link_libraries(${EXECUTABLE_NAME} sfml-system sfml-window sfml-graphics)
