cmake_minimum_required(VERSION 3.2)
project(pong)
#include_directories("./_include")

set(CMAKE_MODULE_PATH $(PROJECT_SOURCE_DIR)/cmake)


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

set(EXECUTABLE_NAME "pong")
set(CMAKE_CXX_FLAGS "-g -DPONG_INTERNAL -DPONG_SLOW")

file(GLOB HEADERS "*.hpp")
file(GLOB SOURCES "*.cpp")

add_executable(${EXECUTABLE_NAME} ${HEADERS} ${SOURCES})


target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${SDL2_LIBRARIES})
