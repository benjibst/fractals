cmake_minimum_required(VERSION 3.27)
project(fractals C)

set(CMAKE_C_STANDARD 11)

find_package(OpenGL REQUIRED)

add_definitions(-DPROJECT_BASE="${PROJECT_SOURCE_DIR}")

set(GLADC "${PROJECT_SOURCE_DIR}/glad/src/glad.c")

add_subdirectory(glfw)
add_subdirectory(src)
