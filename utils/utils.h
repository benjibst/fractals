#ifndef UTILS_H
#define UTILS_H
#include <assert.h>
#include <stddef.h>

#define PRINTERR(...) fprintf(stderr, __VA_ARGS__)

char* read_file(const char * path);

typedef struct {
    unsigned int vert;
    unsigned int frag;
} vert_frag_shader_pair;

unsigned int get_vert_frag_shader_program(const char * vert_path, const char * frag_path);

#endif //UTILS_H
