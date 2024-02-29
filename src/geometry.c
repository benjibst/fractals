#include "geometry.h"
Vec2f go_along_line(Vec2f* a, Vec2f* b, float c){
    return (Vec2f){X(*a) * (1-c) + X(*b)*c,Y(*a) * (1-c) + Y(*b)*c};
}
