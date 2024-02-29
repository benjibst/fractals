cmake_minimum_required(VERSION 3.27)

set(CMAKE_C_STANDARD 11)

# local glfw repo
add_executable(renderer ${CMAKE_SOURCE_DIR}/glad/src/glad.c
        main.c
        renderer.c
        shader.c
        sierpinski.c
        sierpinskirenderer.c
        utils.c
        geometry.c)

target_include_directories(renderer PUBLIC ${CMAKE_SOURCE_DIR}/glad/include)
target_include_directories(renderer PUBLIC ${CMAKE_SOURCE_DIR}/glfw/include)
if (WIN32)
    target_link_libraries(renderer PUBLIC ${CMAKE_SOURCE_DIR}/glfw/bin/glfw3.lib)
    target_link_libraries(renderer PUBLIC opengl32 user32 gdi32 shell32)
elseif (UNIX)
    target_link_libraries(renderer PUBLIC ${CMAKE_SOURCE_DIR}/glfw/bin/libglfw3.a m)
endif ()





