#!/bin/sh

alias cmake=cmake3

cmake -S . -B .build
cmake --build .build
cmake --install .build
