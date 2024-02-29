cmake_minimum_required(VERSION 3.27)
project(fractals C)

set(CMAKE_C_STANDARD 11)

add_definitions(-DPROJECT_BASE="${PROJECT_SOURCE_DIR}")

add_subdirectory(src)
