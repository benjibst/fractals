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

target_include_directories(renderer PUBLIC ${CMAKE_SOURCE_DIR}/cglm/include)

if (MSVC)
    target_link_libraries(renderer PUBLIC
            ${CMAKE_SOURCE_DIR}/cglm/bin/libcglm.lib
            glfw opengl32 user32 gdi32 shell32
    )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
elseif (UNIX)
    target_link_libraries(renderer PUBLIC
            glfw
            ${CMAKE_SOURCE_DIR}/cglm/bin/libcglm.a
            m)
endif ()





