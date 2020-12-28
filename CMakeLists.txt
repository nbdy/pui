cmake_minimum_required(VERSION 3.0)
project(pui)

option(TESTS "Build tests")
option(MODULES "Build modules")
option(DEBUG "Debug build" ON)
option(PINEPHONE "Build for Pinephone" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-fpermissive -Wnarrowing -Wenum-compare")

# set(CMAKE_SYSROOT /media/data/iso/postmarketos/chroot_rootfs_pine64-pinephone/)

include_directories(libs)
include_directories(ext)

file(GLOB_RECURSE SRCS libs/*.cpp libs/*.h)
file(GLOB HEADERS ext/*.h ext/*.hpp ext/*.cpp)

add_executable(pui main.cpp ${SRCS} ${HEADERS})

target_link_libraries(pui
        raylib dl pthread)

if(DEBUG)
    add_compile_definitions(DEBUG)
endif()

if(PINEPHONE)
    add_compile_definitions(PINEPHONE)
endif()

if(TESTS)
    include(tests/CMakeLists.txt)
endif()

if(MODULES)
    include(modules/CMakeLists.txt)
endif()

unset(CMAKE_SYSROOT CACHE)
unset(SRCS CACHE)
unset(TESTS CACHE)
unset(DEBUG CACHE)
unset(PINEPHONE CACHE)