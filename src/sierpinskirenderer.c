#include "sierpinskirenderer.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "sierpinski.h"
#include "utils.h"
#include "shader.h"
#include <math.h>
#include "cglm/call.h"

static GLuint sierpinski_shader_prog = 0;
static GLuint sierpinski_vao = 0;
static unsigned int sierpinski_elements = 0;

int buffer_sierpinski_data_dots(unsigned int iterations)
{
    sierpinski_elements = iterations;
    float height = (float) sqrt(3) / 4;
    Triangle2f base = {
            .p = {
                    {-0.5f, -height},
                    {0.5f,  -height},
                    {0.0f,  +height}
            }
    };
    srand(time(NULL));
    Vec2f *fractal = malloc(iterations * sizeof(Vec2f));
    if (!fractal) {
        PRINTERR("Failed to allocate memory for fractal\n");
        return -1;
    }
    sierpinski_dots(iterations, base, fractal);
    glGenVertexArrays(1, &sierpinski_vao);
    glBindVertexArray(sierpinski_vao);
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, iterations * sizeof(Vec2f), fractal, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof (Vec2f), (void *) 0);
    glEnableVertexAttribArray(0);
    free(fractal);
    return 0;
}

int buffer_sierpinski_data_lines(unsigned iterations){
    float height = (float) sqrt(3) / 4;
    Triangle2f base = {
            .p = {
                    {-0.5f, -height},
                    {0.5f,  -height},
                    {0.0f,  +height}
            }
    };
    srand(time(NULL));
    sierpinski_elements = (ipow(3,iterations)-1)/2;
    Triangle2f *fractal = malloc(sierpinski_elements * sizeof(Triangle2f));
    if (!fractal) {
        PRINTERR("Failed to allocate memory for fractal\n");
        return -1;
    }
    sierpinski_lines(iterations,0, base, fractal,0);
    glGenVertexArrays(1, &sierpinski_vao);
    glBindVertexArray(sierpinski_vao);
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sierpinski_elements * sizeof(Triangle2f), fractal, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof (Vec2f), (void *) 0);
    glEnableVertexAttribArray(0);
    free(fractal);
    return 0;
}

int init_sierpinski_renderer_dots(unsigned int iterations)
{
    if (buffer_sierpinski_data_dots(iterations)) {
        return -1;
    }
    return init_shader_program_vf(&sierpinski_shader_prog, SIERPINSKI_VERTEX_SHADER_PATH, SIERPINSKI_FRAGMENT_SHADER_PATH);

}

int init_sierpinski_renderer_lines(unsigned int iterations)
{
    if (buffer_sierpinski_data_lines(iterations)) {
        return -1;
    }
    return init_shader_program_vf(&sierpinski_shader_prog, SIERPINSKI_VERTEX_SHADER_PATH, SIERPINSKI_FRAGMENT_SHADER_PATH);

}

void sierpinski_draw_dots(double time)
{
    GLint loc = glGetUniformLocation(sierpinski_shader_prog, "vertex_color");
    float red = (float) sin(time) / 2.0f + 0.5f;
    float green = (float) sin(time + 2*M_PI/3) / 2.0f + 0.5f;
    float blue = (float) sin(time + 4*M_PI/3) / 2.0f + 0.5f;
    glUniform4f(loc, red,green, blue, 1.0f);
    glUseProgram(sierpinski_shader_prog);
    glBindVertexArray(sierpinski_vao);
    glDrawArrays(GL_POINTS, 0, sierpinski_elements);
}
void sierpinski_draw_lines(double time, float scale, float x_offset, float y_offset)
{
    mat4 transform = {1,0,0,0,
                0,1,0,0,
                0,0,1,0,
                0,0,0,1};
    glmc_scale(transform, (vec3){scale,scale,scale});
    glmc_translate(transform, (vec3){x_offset/scale,y_offset/scale,0});
    GLint loc = glGetUniformLocation(sierpinski_shader_prog, "vertex_color");
    GLint loc_rot = glGetUniformLocation(sierpinski_shader_prog, "transform");
    float red = (float) sin(time) / 2.0f + 0.5f;
    float green = (float) sin(time + 2*M_PI/3) / 2.0f + 0.5f;
    float blue = (float) sin(time + 4*M_PI/3) / 2.0f + 0.5f;
    glUniformMatrix4fv(loc_rot, 1, GL_FALSE, (float*)transform);
    glUniform4f(loc, red,green, blue, 1.0f);
    glUseProgram(sierpinski_shader_prog);
    glBindVertexArray(sierpinski_vao);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glDrawArrays(GL_TRIANGLES, 0, sierpinski_elements);
}

