#!/bin/bash

if [ ! -d "build" ]; then ./build.sh pp; fi
cd build
sudo make install