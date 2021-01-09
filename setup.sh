#!/bin/bash

function install_taskflow_git() {
  cd /tmp/
  git clone https://github.com/taskflow/taskflow/
  cd taskflow
  mkdir build
  cd build
  cmake ..
  make -j $(nproc)
  sudo make install
  cd /tmp/
  rm -rf taskflow
}

function install_raylib_git() {
  cd /tmp/
  git clone https://github.com/raysan5/raylib
  cd raylib
  mkdir build
  cd build
  cmake .. -DWITH_PIC=ON $1
  make -j$(nproc)
  sudo make install
  cd /tmp/
  rm -rf raylib
}

DEPENDENCY_LIST="gcc g++ cmake make git libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev gpsd gpsd-clients"

if [ -f /sbin/apk ]; then
  sudo apk add $DEPENDENCY_LIST gpsd-dev glfw-wayland-dev libexecinfo-dev sway
  sudo adduser $USER input
  sudo adduser $USER video
  if [ ! -f /usr/local/include/raylib.h ]; then install_raylib_git "-DUSE_WAYLAND=ON"; fi
fi

if [ -f /usr/bin/apt ]; then
  sudo apt install -y $DEPENDENCY_LIST build-essential libgl-dev libgps-dev
  if [ ! -f /usr/local/include/raylib.h ]; then install_raylib_git ""; fi
fi

if [ ! -d /usr/local/include/taskflow ]; then install_taskflow_git; fi
