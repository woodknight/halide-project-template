if(NOT ANDROID)
    add_executable(halide_gaussian_blur.generator halide_gaussian_blur_generator.cpp)
    target_link_libraries(halide_gaussian_blur.generator PRIVATE Halide::Generator)
    add_halide_library(halide_gaussian_blur FROM halide_gaussian_blur.generator AUTOSCHEDULER Halide::Mullapudi2016 STMT_HTML blur.html)

    add_library(halide_gaussian_blur_wrapper halide_gaussian_blur_wrapper.cpp)
    target_link_libraries(halide_gaussian_blur_wrapper PRIVATE halide_gaussian_blur)
endif()

if(ANDROID)
    add_library(halide_gaussian_blur_wrapper SHARED halide_gaussian_blur_wrapper.cpp)
    target_link_libraries(halide_gaussian_blur_wrapper
        PRIVATE
        ${PROJECT_BINARY_DIR}/gen_files/halide_gaussian_blur.a
        log
    )
    target_include_directories(halide_gaussian_blur_wrapper
        PRIVATE
        ${PROJECT_BINARY_DIR}/gen_files
        ${HALIDE_INCLUDE_DIR}
    )
endif()