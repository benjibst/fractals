#include "sierpinski.h"
#include <stdlib.h>

void sierpinski_dots(unsigned iterations, Triangle2f base, Vec2f *out_p)
{
    if (iterations == 0) {
        return;
    }
    float u1 = (float) rand() / RAND_MAX;
    float u2 = 1 - u1;
    X(out_p[0]) = X(A(base)) + u1 * (X(B(base)) - X(A(base))) + u2 * (X(C(base)) - X(A(base)));
    Y(out_p[0]) = Y(A(base)) + u1 * (Y(B(base)) - Y(A(base))) + u2 * (Y(C(base)) - Y(A(base)));
    int curr_vert;
    for (unsigned i = 1; i < iterations; ++i) {
        curr_vert = rand() % 3;
        X(out_p[i]) = (X(out_p[i - 1]) + X(base.p[curr_vert])) / 2;
        Y(out_p[i]) = (Y(out_p[i - 1]) + Y(base.p[curr_vert])) / 2;
    }
}

void sierpinski_lines(unsigned iterations, unsigned curr_iteration, Triangle2f base, Triangle2f *out, unsigned idx){
    if(curr_iteration==iterations) return;

    A(out[idx]) = go_along_line(&A(base),&B(base),0.5f);
    B(out[idx]) = go_along_line(&A(base),&C(base),0.5f);
    C(out[idx]) = go_along_line(&B(base),&C(base),0.5f);

    Triangle2f base_left = {A(base),A(out[idx]),B(out[idx])};
    Triangle2f base_right = {A(out[idx]),B(base),C(out[idx])};
    Triangle2f base_top = {B(out[idx]),C(out[idx]),C(base)};

    sierpinski_lines(iterations,curr_iteration+1,base_left,out,idx*3+1);
    sierpinski_lines(iterations,curr_iteration+1,base_right,out,idx*3+2);
    sierpinski_lines(iterations,curr_iteration+1,base_top,out,idx*3+3);
}
