#!/bin/bash
set -e

rm -rf build_android
mkdir -p build_android/gen_files/

# compile Halide filters
echo "## build halide filters..."
make -j16

# compile others
cd build_android

ANDROID_NDK="${HOME}/Android/Sdk/ndk-bundle"
cmake -DCMAKE_TOOLCHAIN_FILE="$ANDROID_NDK/build/cmake/android.toolchain.cmake" \
      -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
      -DCMAKE_INSTALL_PREFIX="install" \
      -DCMAKE_BUILD_TYPE="Release" \
      -DANDROID_ABI="arm64-v8a" \
      -DANDROID_PLATFORM="android-28" \
      ../

make -j16