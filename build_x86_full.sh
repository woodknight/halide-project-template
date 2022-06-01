#!/bin/bash
set -e

rm -rf build
mkdir -p build
cd build
cmake ../ -DCMAKE_EXPORT_COMPILE_COMMANDS=1
make -j16
# ctest --verbose