#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "glad/glad.h"

char* read_file(const char * path)
{
    FILE *f = fopen(path, "rb");
    if(!f){
        PRINTERR("Failed to open file %s\n", path);
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    long file_size = ftell(f);
    char *string = malloc(file_size + 1);
    if (!string){
        PRINTERR("Failed to allocate memory for file %s\n", path);
        fclose(f);
        return NULL;
    }
    rewind(f);
    fread(string, file_size, 1, f);
    fclose(f);
    string[file_size] = 0;
    return string;
}

char* opengl_shader_type_str(GLenum type){
    switch(type){
        case GL_VERTEX_SHADER:
            return "GL_VERTEX_SHADER";
        case GL_FRAGMENT_SHADER:
            return "GL_FRAGMENT_SHADER";
        case GL_GEOMETRY_SHADER:
            return "GL_GEOMETRY_SHADER";
        case GL_TESS_CONTROL_SHADER:
            return "GL_TESS_CONTROL_SHADER";
        case GL_TESS_EVALUATION_SHADER:
            return "GL_TESS_EVALUATION_SHADER";
        case GL_COMPUTE_SHADER:
            return "GL_COMPUTE_SHADER";
        default:
            return "UNKNOWN";
    }
}

GLuint compile_opengl_shader(GLenum type, const char * src_path){
    char* shader_src = read_file(src_path);
    if (!shader_src){
        return 0;
    }
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, (const char * const *)&shader_src, NULL);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success){
        char info_log[512];
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        PRINTERR("Failed to compile %s: %s\n", opengl_shader_type_str(type), info_log);
        free(shader_src);
        glDeleteShader(shader);
        return 0;
    }
    free(shader_src);
    return shader;
}

vert_frag_shader_pair get_vert_frag_shaders(const char * vert_path, const char * frag_path){
    return  (vert_frag_shader_pair){
        .vert = compile_opengl_shader(GL_VERTEX_SHADER, vert_path),
        .frag = compile_opengl_shader(GL_FRAGMENT_SHADER, frag_path)
    };
}

unsigned int get_vert_frag_shader_program(const char * vert_path, const char * frag_path){
    vert_frag_shader_pair shaders = get_vert_frag_shaders(vert_path, frag_path);
    if (!shaders.vert || !shaders.frag){
        return 0;
    }
    unsigned int shader_program = glCreateProgram();
    glAttachShader(shader_program, shaders.vert);
    glAttachShader(shader_program, shaders.frag);
    glLinkProgram(shader_program);
    GLint success;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success){
        char info_log[512];
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        PRINTERR("Failed to link shader program: %s\n", info_log);
        return 0;
    }
    glDeleteShader(shaders.vert);
    glDeleteShader(shaders.frag);
    return shader_program;
}



