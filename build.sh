#!/bin/bash

if [ ! -d build ]; then make build; fi
cd build
rm -rf *
cmake ..
make -j$(nproc)
