#ifndef FRACTALS_SIERPINSKIRENDERER_H
#define FRACTALS_SIERPINSKIRENDERER_H

#include "glad/glad.h"
#define SIERPINSKI_VERTEX_SHADER_PATH PROJECT_BASE"/shaders/sierpinski.vert"
#define SIERPINSKI_FRAGMENT_SHADER_PATH PROJECT_BASE"/shaders/sierpinski.frag"

void sierpinski_draw();
int init_sierpinski_renderer(unsigned int iterations);


#endif //FRACTALS_SIERPINSKIRENDERER_H
