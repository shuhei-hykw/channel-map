#!/bin/sh

cmake -S . -B .build
cmake --build .build --parallel 4 # n_cpu as you like
cmake --install .build
