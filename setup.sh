#!/bin/bash

if [ -f /sbin/apk ]; then
  sudo apk add gcc g++ cmake make raylib-wayland-dev git
fi

if [ -f /usr/bin/apt ]; then
  sudo apt install -y cmake build-essential gcc g++ git
fi

git submodule update --init