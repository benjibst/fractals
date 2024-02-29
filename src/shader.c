#include "shader.h"
#include "utils.h"
#include <stdlib.h>

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

int compile_opengl_shader(GLenum type, const char * src_path, GLuint *shader_out){
    char* shader_src;
    int ret = read_file(src_path,&shader_src);
    if (ret) return ret;
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
        return -1;
    }
    free(shader_src);
    *shader_out = shader;
    return 0;
}


int init_shader_program_vf(GLuint * program, const char * vert_path, const char * frag_path){
    unsigned int v_id,f_id;
    int ret = compile_opengl_shader(GL_VERTEX_SHADER, vert_path, &v_id);
    if (ret)return ret;
    ret = compile_opengl_shader(GL_FRAGMENT_SHADER, frag_path, &f_id);
    if (ret) {
        glDeleteShader(v_id);
        return ret;
    }
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, v_id);
    glAttachShader(shader_program, f_id);
    glLinkProgram(shader_program);
    GLint success;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success){
        char info_log[512];
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        PRINTERR("Failed to link shader program: %s\n", info_log);
        return -1;
    }
    glDeleteShader(v_id);
    glDeleteShader(f_id);
    *program = shader_program;
    return 0;
}