#include "sierpinski.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

void sierpinski(int iterations, Triangle base, Vec2f *fractal)
{
    if (iterations == 0) {
        return;
    }
    double u1 = (double) rand() / RAND_MAX;
    double u2 = 1 - u1;
    fractal[0].x = base.p[0].x + u1 * (base.p[1].x - base.p[0].x) + (u2 * base.p[2].x - base.p[0].x);
    fractal[0].y = base.p[0].y + u1 * (base.p[1].y - base.p[0].y) + (u2 * base.p[2].y - base.p[0].y);
    int curr_vert;
    for (int i = 1; i < iterations; ++i) {
        curr_vert = rand() % 3;
        fractal[i].x = (fractal[i-1].x + base.p[curr_vert].x) / 2;
        fractal[i].y = (fractal[i-1].y + base.p[curr_vert].y) / 2;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <iterations>\n", argv[0]);
        return 1;
    }
    char *end;
    int iterations = strtol(argv[1], &end, 10);
    if (end == argv[1]) {
        printf("Invalid number: %s\n", argv[1]);
        return 1;
    }
    Triangle base;
    base.p[0] = (Vec2f) {-0.5, -sqrt(3)/4};
    base.p[1] = (Vec2f) {0.5, -sqrt(3)/4};
    base.p[2] = (Vec2f) {0, sqrt(3)/4};
    Vec2f *fractal = malloc(iterations * sizeof(Vec2f));
    srand(time(NULL));
    sierpinski(iterations, base, fractal);
    for (int i = 0; i < iterations; ++i) {
        printf("%f, %f;\n", fractal[i].x, fractal[i].y);
    }
    free(fractal);
}
