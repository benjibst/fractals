#ifndef FRACTALS_SIERPINSKIRENDERER_H
#define FRACTALS_SIERPINSKIRENDERER_H

#include "glad/gl.h"
#define SIERPINSKI_VERTEX_SHADER_PATH PROJECT_BASE"/shaders/sierpinski.vert"
#define SIERPINSKI_FRAGMENT_SHADER_PATH PROJECT_BASE"/shaders/sierpinski.frag"

int init_sierpinski_renderer_dots(unsigned int iterations);
int init_sierpinski_renderer_lines(unsigned int iterations);
void sierpinski_draw_dots(double time);
void sierpinski_draw_lines(double time, float scale, float x_offset, float y_offset);


#endif //FRACTALS_SIERPINSKIRENDERER_H
