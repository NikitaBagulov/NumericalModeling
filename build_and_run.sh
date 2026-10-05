#!/bin/bash

cmake -S . -B build
cmake --build ./build
./build/my_programm

python plot.py