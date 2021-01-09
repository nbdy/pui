#!/bin/bash

CMAKE_OPTIONS=""

if [ $# -eq 1 ]; then
	if [ $1 = "pp" ]; then CMAKE_OPTIONS="-DPINEPHONE=ON -DMODULES=ON"; fi
fi

if [ ! -d build ]; then mkdir build; fi
cd build
rm -rf *
cmake .. $CMAKE_OPTIONS
make -j$(nproc)