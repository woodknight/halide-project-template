cmake_minimum_required(VERSION 3.16)

# set clang compiler path
if((NOT APPLE) AND (NOT ANDROID))
    set(CMAKE_C_COMPILER "clang-13")
    set(CMAKE_CXX_COMPILER "clang++-13")
endif()

# project name
project(UPC C CXX)

# enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

# -fPIC
# set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# set build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

#
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# halide
set(HALIDE_INSTALL_DIR "$ENV{HOME}/Applications/Halide/Halide-14.0.0/build/install/")
set(Halide_DIR "${HALIDE_INSTALL_DIR}/lib/cmake/Halide/")
set(HalideHelpers_DIR "${HALIDE_INSTALL_DIR}/lib/cmake/HalideHelpers")
set(HALIDE_INCLUDE_DIR "${HALIDE_INSTALL_DIR}/include/")
set(HALIDE_TOOLS_DIR "${HALIDE_INSTALL_DIR}/share/tools/")

if(NOT ANDROID)    
    find_package(Halide REQUIRED)
endif()

add_subdirectory(src)