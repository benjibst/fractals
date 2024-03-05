cmake_minimum_required(VERSION 3.27)

set(CMAKE_C_STANDARD 11)

# local glfw repo
add_executable(renderer
        ${GLADC}
        main.c
        renderer.c
        shader.c
        sierpinski.c
        sierpinskirenderer.c
        utils.c
        geometry.c)

if (MSVC)
    target_link_libraries(renderer PUBLIC cglm glfw opengl32 user32 gdi32 shell32)
elseif (UNIX)
    target_link_libraries(renderer PUBLIC glfw cglm m)
endif ()





