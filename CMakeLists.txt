cmake_minimum_required(VERSION 3.0)
project(pui)

set(CMAKE_CXX_STANDARD 17)

add_executable(pui main.cpp)

target_link_libraries(pui raylib)