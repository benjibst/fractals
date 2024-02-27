cmake_minimum_required(VERSION 3.27)

set(CMAKE_C_STANDARD 11)

# local glfw repo
add_executable(renderer main.c renderer.c ../glad/src/glad.c)

target_include_directories(renderer PUBLIC ../lib)
target_link_libraries(renderer PUBLIC sierpinski)

target_include_directories(renderer PUBLIC ../glfw/include)
target_link_libraries(renderer PUBLIC ../glfw/bin/glfw3)

target_include_directories(renderer PUBLIC ../glad/include)

target_link_libraries(renderer PUBLIC opengl32 user32 gdi32 shell32)


