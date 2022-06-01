add_library(timer timer.cpp)
target_include_directories(timer INTERFACE ${PROJECT_SOURCE_DIR})

add_library(file_io file_io.cpp)
target_include_directories(file_io INTERFACE ${PROJECT_SOURCE_DIR})