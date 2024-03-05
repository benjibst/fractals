#include "renderer.h"
#include <stdio.h>
#include "utils.h"
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "sierpinskirenderer.h"

static float scale = 1;
static float x_click_pos = 0;
static float y_click_pos = 0;
static float x_offset = 0;
static float y_offset = 0;
static float x_offset_tmp = 0;
static float y_offset_tmp = 0;
static float x_drag_offset = 0;
static float y_drag_offset = 0;
static int left_click_before = GLFW_RELEASE;

void window_sz_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    double xpos, ypos;
    int w, h;
    glfwGetWindowSize(window, &w, &h);
    glfwGetCursorPos(window, &xpos, &ypos);
    xpos = xpos / w * 2 - 1;
    ypos = -ypos / h * 2 + 1;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

        if (left_click_before == GLFW_RELEASE) {
            left_click_before = GLFW_PRESS;
            x_click_pos = xpos;
            y_click_pos = ypos;
        } else {
            x_drag_offset = xpos - x_click_pos;
            y_drag_offset = ypos - y_click_pos;
            x_offset = x_offset_tmp + x_drag_offset;
            y_offset = y_offset_tmp + y_drag_offset;
        }
    } else {
        left_click_before = GLFW_RELEASE;
        x_offset_tmp = x_offset;
        y_offset_tmp = y_offset;
    }

}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    if (yoffset > 0)
        scale *= 1.1;
    else
        scale /= 1.1;
    if (scale < 0.1)
        scale = 0.1;
}


void Run()
{
    if (glfwInit() == GLFW_FALSE) {
        PRINTERR("Failed to initialize GLFW\n");
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(500, 500, "LearnOpenGL", NULL, NULL);
    if (!window) {
        PRINTERR("Failed to create GLFW window\n");
        glfwTerminate();
        return;
    }
    glfwSetWindowSizeCallback(window, window_sz_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwMakeContextCurrent(window);
    if (!gladLoadGL(glfwGetProcAddress)) {
        PRINTERR("Failed to initialize GLAD\n");
        glfwTerminate();
        return;
    }
    glViewport(0, 0, 500, 500);
    if (init_sierpinski_renderer_lines(15)) {
        glfwTerminate();
        return;
    }
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        sierpinski_draw_lines(glfwGetTime(), scale, x_offset, y_offset);
        glfwSwapBuffers(window);
    }
    glfwTerminate();
}