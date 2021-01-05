#!/bin/bash

if [ $1 -eq "pp" ]; then $1="-DPINEPHONE=ON"; fi

if [ ! -d build ]; then mkdir build; fi
cd build
rm -rf *
cmake .. $1
make -j$(nproc)
