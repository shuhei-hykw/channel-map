#!/bin/sh

type cmake3 2>/dev/null && alias cmake=cmake3

cmake -S . -B .build
cmake --build .build
cmake --install .build
