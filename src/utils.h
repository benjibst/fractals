#ifndef UTILS_H
#define UTILS_H
#include <assert.h>
#include <stdio.h>

#define PRINTERR(...) fprintf(stderr, __VA_ARGS__)

int read_file(const char * path,char** out);

int ipow(int base, int exp);

#endif //UTILS_H
