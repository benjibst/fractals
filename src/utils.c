#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int read_file(const char * path,char** out)
{
    FILE *f = fopen(path, "rb");
    if(!f){
        PRINTERR("Failed to open file %s\n", path);
        return -1;
    }
    fseek(f, 0, SEEK_END);
    long file_size = ftell(f);
    *out = malloc(file_size + 1);
    if (!*out){
        PRINTERR("Failed to allocate memory for file %s\n", path);
        fclose(f);
        return -1;
    }
    rewind(f);
    fread(*out, file_size, 1, f);
    fclose(f);
    (*out)[file_size] = 0;
    return 0;
}

int ipow(int base, int exp)
{
    int result = 1;
    for (;;)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }

    return result;
}




