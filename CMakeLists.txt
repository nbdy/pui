cmake_minimum_required(VERSION 3.0)
project(pui)

option(TESTS "Enable tests")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-fpermissive")

# set(CMAKE_SYSROOT /media/data/iso/postmarketos/chroot_rootfs_pine64-pinephone/)

include_directories(libs)
include_directories(ext)

file(GLOB_RECURSE SRCS libs/*.cpp libs/*.h)
file(GLOB HEADERS ext/*.h)

add_executable(pui main.cpp ${SRCS} ${HEADERS})

target_link_libraries(pui
        raylib dl)

if(TESTS)
    include(tests)
endif()

unset(CMAKE_SYSROOT CACHE)
unset(SRCS CACHE)
unset(TESTS CACHE)