#ifndef FRACTALS_SIERPINSKI_H
#define FRACTALS_SIERPINSKI_H

#include "geometry.h"

void sierpinski_dots(unsigned int iterations, Triangle2f base, Vec2f * out_p);
void sierpinski_lines(unsigned iterations, unsigned curr_iteration, Triangle2f base, Triangle2f *out, unsigned idx);


#endif //FRACTALS_SIERPINSKI_H
