#ifndef FRACTALS_GEOMETRY_H
#define FRACTALS_GEOMETRY_H


#define X(v)((v).c[0])
#define Y(v)((v).c[1])
#define Z(v)((v).c[2])
#define A(t)((t).p[0])
#define B(t)((t).p[1])
#define C(t)((t).p[2])

typedef struct {
    float c[3];
}Vec3f;
typedef struct {
    float c[2];
}Vec2f;

typedef struct {
    Vec3f p[3];
}Triangle3f;


typedef struct {
    Vec2f p[3];
}Triangle2f;

Vec2f go_along_line(Vec2f* a, Vec2f* b, float c);

#endif //FRACTALS_GEOMETRY_H
