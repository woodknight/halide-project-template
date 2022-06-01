add_subdirectory(utils)
add_subdirectory(gaussian_blur)

add_executable(test test.cpp)
target_link_libraries(test PRIVATE halide_gaussian_blur Halide::Tools)