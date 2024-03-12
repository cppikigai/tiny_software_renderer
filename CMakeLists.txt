cmake_minimum_required(VERSION 3.10)

project(tiny_software_renderer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(EXTERNALS_PATH externals)
set(SAMPLES_PATH samples)

add_subdirectory(${EXTERNALS_PATH}/glfw)
add_subdirectory(${EXTERNALS_PATH}/glad)

add_subdirectory(renderer)
add_subdirectory(${SAMPLES_PATH}/demo)