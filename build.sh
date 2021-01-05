#!/bin/bash

if [ ! -d build ]; then mkdir build; fi
cd build
rm -rf *
cmake .. $1
make -j$(nproc)
