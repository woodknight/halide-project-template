#!/bin/bash

# build Halide filters
mkdir -p build_android/gen_files/
echo "## build halide filters..."
make -j16

# build others
cd build_android
make -j16