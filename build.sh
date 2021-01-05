#!/bin/bash

CMAKE_OPTIONS=""

if [ $1 -eq "pp" ]; then CMAKE_OPTIONS="-DPINEPHONE=ON -DMODULES=ON"; fi

if [ ! -d build ]; then mkdir build; fi
cd build
rm -rf *
cmake .. $CMAKE_OPTIONS
make -j$(nproc)
