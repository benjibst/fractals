cmake_minimum_required(VERSION 3.27)

set(CMAKE_C_STANDARD 11)

include_directories(.)
add_library(sierpinski STATIC sierpinski.c)
