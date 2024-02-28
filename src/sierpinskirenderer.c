#include "sierpinskirenderer.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "sierpinski.h"
#include "utils.h"
#include <math.h>

static GLuint sierpinski_shader_prog = 0;
static GLuint sierpinski_vao = 0;
static unsigned int sierpinski_iterations = 0;

int buffer_sierpinski_data(unsigned int iterations){
    sierpinski_iterations= iterations;
    float height = (float)sqrt(3)/4;
    Triangle2f base = {
        .p = {
            {-0.5f, -height},
            {0.5f, -height},
            {0.0f, +height}
        }
    };
    srand(time(NULL));
    Vec2f *fractal = malloc(iterations*sizeof(Vec2f));
    if (!fractal){
        PRINTERR("Failed to allocate memory for fractal\n");
        return -1;
    }
    sierpinski(iterations, base, fractal);
    glGenVertexArrays(1, &sierpinski_vao);
    glBindVertexArray(sierpinski_vao);
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, iterations * sizeof(Vec2f), fractal, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    free(fractal);
    return 0;
}

int init_sierpinski_renderer(unsigned int iterations)
{
    if (buffer_sierpinski_data(iterations)){
        return -1;
    }
    GLuint shader = get_vert_frag_shader_program(SIERPINSKI_VERTEX_SHADER_PATH, SIERPINSKI_FRAGMENT_SHADER_PATH);
    if(!shader){
        return -1;
    }
    glUseProgram(shader);
}

void sierpinski_draw(){
    glUseProgram(sierpinski_shader_prog);
    glBindVertexArray(sierpinski_vao);
    glDrawArrays(GL_POINTS, 0, sierpinski_iterations);
}

