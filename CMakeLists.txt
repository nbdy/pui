cmake_minimum_required(VERSION 3.0)
project(pui)

option(TESTS "Build tests" OFF)
option(MODULES "Build modules" OFF)
option(DEBUG "Debug build" OFF)
option(PINEPHONE "Build for Pinephone" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-fpermissive -Wno-narrowing -Wno-enum-compare")

# set(CMAKE_SYSROOT /media/data/iso/postmarketos/chroot_rootfs_pine64-pinephone/)

include_directories(libs)
include_directories(ext)

file(GLOB_RECURSE SRCS libs/*.cpp libs/*.h)
file(GLOB HEADERS ext/*.h ext/*.hpp ext/*.cpp)

add_executable(pui main.cpp ${SRCS} ${HEADERS})

add_library(basemodule STATIC
        libs/BaseModule/BaseModule.h libs/BaseModule/BaseModule.cpp
        libs/Utils/Utils.h libs/Utils/Utils.cpp
        ext/loguru/loguru.hpp ext/loguru/loguru.cpp)

target_link_libraries(pui raylib dl pthread)

target_link_libraries(basemodule raylib pthread dl)

if(DEBUG)
    add_compile_definitions(DEBUG)
    add_compile_definitions(ICON_DIRECTORY="${CMAKE_SOURCE_DIR}/icons/")
endif()

if(PINEPHONE)
    add_compile_definitions(PINEPHONE)
    target_link_libraries(pui wayland-client)
    target_link_libraries(basemodule wayland-client)
endif()

if(TESTS)
    add_subdirectory(tests)
endif()

if(MODULES)
    add_subdirectory(modules)
endif()

install(TARGETS pui
        RUNTIME DESTINATION /usr/local/bin/)

install(TARGETS basemodule
        LIBRARY DESTINATION /usr/local/lib/pui/
        PUBLIC_HEADER DESTINATION /usr/local/include/pui/)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/icons/ DESTINATION /var/lib/pui/icons)
install(DIRECTORY DESTINATION /var/lib/pui/log/)
install(DIRECTORY DESTINATION /var/lib/pui/modules/)

unset(CMAKE_SYSROOT CACHE)
unset(SRCS CACHE)

unset(TESTS CACHE)
unset(MODULES CACHE)
unset(DEBUG CACHE)
unset(PINEPHONE CACHE)