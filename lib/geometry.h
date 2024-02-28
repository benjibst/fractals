#ifndef FRACTALS_GEOMETRY_H
#define FRACTALS_GEOMETRY_H

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

#endif //FRACTALS_GEOMETRY_H
