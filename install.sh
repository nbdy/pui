#!/bin/bash

if [ ! -d ../pui ]; then
  git clone https://github.com/nbdy/pui
  cd pui
  ./setup.sh
fi

./build.sh pp
cd build
sudo make install