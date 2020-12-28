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
}

if [ -f /sbin/apk ]; then
  sudo apk add gcc g++ cmake make raylib-wayland-dev git
fi

if [ -f /usr/bin/apt ]; then
  sudo apt install -y cmake build-essential gcc g++ git
fi

install_taskflow_git