add_subdirectory(utils)
add_subdirectory(gaussian_blur)

add_executable(test test.cpp)
if(NOT ANDROID)
    target_link_libraries(test PRIVATE halide_gaussian_blur timer)
else()
    target_include_directories(test
        PRIVATE
        ${HALIDE_INCLUDE_DIR}
        ${PROJECT_BINARY_DIR}/gen_files/
    )
    target_link_libraries(test
        PRIVATE
        ${PROJECT_BINARY_DIR}/gen_files/halide_gaussian_blur.a
        timer
        android log
)
endif()