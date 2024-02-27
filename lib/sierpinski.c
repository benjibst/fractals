#include "sierpinski.h"
#include "stdlib.h"

void sierpinski(int iterations, Triangle base, Vec2f *fractal)
{
    if (iterations == 0) {
        return;
    }
    float u1 = (float) rand() / RAND_MAX;
    float u2 = 1 - u1;
    fractal[0].x = base.p[0].x + u1 * (base.p[1].x - base.p[0].x) + (u2 * base.p[2].x - base.p[0].x);
    fractal[0].y = base.p[0].y + u1 * (base.p[1].y - base.p[0].y) + (u2 * base.p[2].y - base.p[0].y);
    int curr_vert;
    for (int i = 1; i < iterations; ++i) {
        curr_vert = rand() % 3;
        fractal[i].x = (fractal[i-1].x + base.p[curr_vert].x) / 2;
        fractal[i].y = (fractal[i-1].y + base.p[curr_vert].y) / 2;
    }
}
