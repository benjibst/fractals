#ifndef FRACTALS_SIERPINSKI_H
#define FRACTALS_SIERPINSKI_H

typedef struct {
    double x;
    double y;
}Vec2f;

typedef struct {
    Vec2f p[3];
}Triangle;

void sierpinski(int iterations, Triangle base, Vec2f* fractal);

#endif //FRACTALS_SIERPINSKI_H
