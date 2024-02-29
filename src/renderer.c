#include "renderer.h"
#include <stdio.h>
#include "utils.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "sierpinskirenderer.h"

void window_sz_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Run() {
    if (glfwInit()==GLFW_FALSE)
    {
        PRINTERR("Failed to initialize GLFW\n");
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(500, 500, "LearnOpenGL", NULL, NULL);
    if (!window)
    {
        PRINTERR("Failed to create GLFW window\n");
        glfwTerminate();
        return;
    }
    glfwSetWindowSizeCallback(window, window_sz_callback);
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        PRINTERR("Failed to initialize GLAD\n");
        glfwTerminate();
        return;
    }
    glViewport(0, 0, 500, 500);
    if(init_sierpinski_renderer_lines(1)){
        glfwTerminate();
        return;
    }
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        sierpinski_draw_lines(glfwGetTime());
        glfwSwapBuffers(window);
    }
    glfwTerminate();
}