cmake_minimum_required(VERSION 3.0)
project(pui)

option(TESTS "Build tests" OFF)
option(MODULES "Build modules" ON)
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
    add_compile_definitions(ICON_DIRECTORY="${CMAKE_SOURCE_DIR}/icons/")
endif()

if(PINEPHONE)
    add_compile_definitions(PINEPHONE)
endif()

if(TESTS)
    add_subdirectory(tests)
endif()

if(MODULES)
    add_subdirectory(modules)
endif()

install(TARGETS pui
        RUNTIME DESTINATION /usr/local/bin/)

add_library(basemodule STATIC
        libs/BaseModule/BaseModule.h libs/BaseModule/BaseModule.cpp
        libs/Utils/Utils.h libs/Utils/Utils.cpp)

install(TARGETS basemodule
        LIBRARY DESTINATION /usr/local/lib/pui/
        PUBLIC_HEADER DESTINATION /usr/local/include/pui/)

unset(CMAKE_SYSROOT CACHE)
unset(SRCS CACHE)

unset(TESTS CACHE)
unset(MODULES CACHE)
unset(DEBUG CACHE)
unset(PINEPHONE CACHE)