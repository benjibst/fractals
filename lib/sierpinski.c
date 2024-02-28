#include "sierpinski.h"
#include <stdlib.h>

void sierpinski(unsigned int iterations, Triangle2f base, Vec2f *out_p)
{
    if (iterations == 0) {
        return;
    }
    float u1 = (float) rand() / RAND_MAX;
    float u2 = 1 - u1;
    out_p[0].c[0] = base.p[0].c[0] + u1 * (base.p[1].c[0] - base.p[0].c[0]) + (u2 * base.p[2].c[0] - base.p[0].c[0]);
    out_p[0].c[1] = base.p[0].c[1] + u1 * (base.p[1].c[1] - base.p[0].c[1]) + (u2 * base.p[2].c[1] - base.p[0].c[1]);
    int curr_vert;
    for (unsigned int i = 1; i < iterations; ++i) {
        curr_vert = rand() % 3;
        out_p[i].c[0] = (out_p[i - 1].c[0] + base.p[curr_vert].c[0]) / 2;
        out_p[i].c[1] = (out_p[i - 1].c[1] + base.p[curr_vert].c[1]) / 2;
    }
}
