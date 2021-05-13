#pragma once

#include <stdarg.h>
#include <time.h>
#include <GL/glew.h>

#define GL_LOG_FILE "gl.log"

bool restart_gl_log() {
    FILE *file = fopen(GL_LOG_FILE, "w");
    if (!file) {
        fprintf(
                stderr,
                "ERROR: could not open GL_LOG_FILE log file %s for writing\n",
                GL_LOG_FILE
        );
        return false;
    }
    time_t now = time(NULL);
    char* date = ctime(&now);
    fprintf(file, "GL_LOG_FILE log, local time %s\n", date);
    fclose(file);
    return true;
}

bool gl_log(const char* message, ...){
    va_list argptr;
    FILE* file = fopen(GL_LOG_FILE, "a");
    if(!file){
        fprintf(
                stderr,
                "ERROR: could not open GL_LOG_FILE %s file for appending\n",
                GL_LOG_FILE
                );
        return false;
    }
    va_start(argptr, message);
    vfprintf(file, message, argptr);
    va_end(argptr);
    fclose(file);
    return true;
}

bool gl_log_err(const char* message, ...){
    va_list argptr;
    FILE* file = fopen(GL_LOG_FILE, "a");
    if(!file){
        fprintf(
                stderr,
                "ERROR: could not open GL_LOG_FILE %s file for appending\n",
                GL_LOG_FILE
                );
        return false;
    }
    va_start(argptr, message);
    vfprintf(file, message, argptr);
    va_end(argptr);
    va_start(argptr, message);
    vfprintf(stderr, message, argptr);
    va_end(argptr);
    fclose(file);
    return true;
}

void log_gl_params(){
    GLenum params[] = {
            GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
            GL_MAX_CUBE_MAP_TEXTURE_SIZE,
            GL_MAX_DRAW_BUFFERS,
            GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
            GL_MAX_TEXTURE_IMAGE_UNITS,
            GL_MAX_TEXTURE_SIZE,
            GL_MAX_VARYING_FLOATS,
            GL_MAX_VERTEX_ATTRIBS,
            GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
            GL_MAX_VERTEX_UNIFORM_COMPONENTS,
            GL_MAX_VIEWPORT_DIMS,
            GL_STEREO,
    };
    const char* names[] = {
            "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
            "GL_MAX_CUBE_MAP_TEXTURE_SIZE",
            "GL_MAX_DRAW_BUFFERS",
            "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
            "GL_MAX_TEXTURE_IMAGE_UNITS",
            "GL_MAX_TEXTURE_SIZE",
            "GL_MAX_VARYING_FLOATS",
            "GL_MAX_VERTEX_ATTRIBS",
            "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
            "GL_MAX_VERTEX_UNIFORM_COMPONENTS",
            "GL_MAX_VIEWPORT_DIMS",
            "GL_STEREO",
    };
    gl_log("GL Context Params: \n");
    for(int i = 0; i < 10; i++){
        int v = 0;
        glGetIntegerv(params[i], &v);
        gl_log("%s %i\n", names[i], v);
    }

    int v[2];
    v[0] = v[1] = 0;
    glGetIntegerv(params[10], v);
    gl_log("%s %i %i\n", names[10], v[0], v[1]);
    unsigned char s = 0;
    glGetBooleanv(params[11], &s);
    gl_log("%s %u\n", names[11], (unsigned int)s);
    gl_log("---------------------------------\n");
}

const char* GL_type_to_string(GLenum type){
    switch(type){
        case GL_BOOL: return "bool";
        case GL_INT: return "int";
        case GL_FLOAT: return "float";
        case GL_FLOAT_VEC2: return "vec2";
        case GL_FLOAT_VEC3: return "vec3";
        case GL_FLOAT_VEC4: return "vec4";
        case GL_FLOAT_MAT2: return "mat2";
        case GL_FLOAT_MAT3: return "mat3";
        case GL_FLOAT_MAT4: return "mat4";
        case GL_SAMPLER_2D: return "sampler2D";
        case GL_SAMPLER_3D: return "sampler3D";
        case GL_SAMPLER_CUBE: return "samplerCube";
        case GL_SAMPLER_2D_SHADOW: return "sampler2DShadow";
        default: break;
    }
    return "other";
}

void _print_shader_info_log(GLuint shaderIndex) {
    int max_length = 2048;
    int actual_length = 0;
    char log[2048];
    glGetShaderInfoLog(shaderIndex, max_length, &actual_length, log);
    printf("shader info log for GL index %u: \n%s\n", shaderIndex, log);
}

void _print_program_info_log(GLuint shaderProgram){
    int max_length = 2048;
    int actual_length = 0;
    char log[2048];
    glGetProgramInfoLog(shaderProgram, max_length, &actual_length, log);
    printf("program info log for GL index %u:\n%s", shaderProgram, log);
}

void print_all(GLuint shaderProgram){
    printf("-----------------------\nshader program %i info:\n", shaderProgram);
    int params = -1;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &params);
    printf("GL_LINK_STATUS = %i\n", params);

    glGetProgramiv(shaderProgram, GL_ATTACHED_SHADERS, &params);
    printf("GL_ATTACHED_SHADERS = %i\n", params);

    glGetProgramiv(shaderProgram, GL_ACTIVE_ATTRIBUTES, &params);
    printf("GL_ACTIVE_ATTRIBUTES = %i\n", params);
    for(GLuint i = 0; i<(GLuint)params; i++){
        char name[64];
        int max_length = 64;
        int actual_length = 0;
        int size = 0;
        GLenum type;
        glGetActiveAttrib(shaderProgram, i, max_length, &actual_length, &size, &type, name);
        if(size > 1){
            for(int j = 0; j <size; j++){
                char long_name[64];
                sprintf(long_name, "%s[%i]", name, j);
                int location = glGetAttribLocation(shaderProgram, long_name);
                printf("  %i) type:%s name:%s location:%i\n", i, GL_type_to_string(type), long_name, location);
            }
        } else {
            int location = glGetAttribLocation(shaderProgram, name);
            printf(" %i) type:%s name:%s location:%i\n", i, GL_type_to_string(type), name, location);
        }
    }
    glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORMS, &params);
    printf("GL_ACTIVE_UNIFORMS = %i\n", params);
    for(GLuint i = 0; i<(GLuint)params; i++){
        char name[64];
        int max_length = 64;
        int actual_length = 0;
        int size = 0;
        GLenum type;
        glGetActiveUniform(shaderProgram, i, max_length, &actual_length, &size, &type, name);
        if(size > 1){
            for(int j = 0; j < size; j++){
                char long_name[64];
                sprintf(long_name, "%s[%i]", name, j);
                int location = glGetUniformLocation(shaderProgram, long_name);
                printf("  %i) type:%s name:%s location:%i\n", i, GL_type_to_string(type), long_name, location);
            }
        } else {
            int location = glGetUniformLocation(shaderProgram, name);
            printf("  %i) type:%s name:%s location:%i\n", i, GL_type_to_string(type), name, location);
        }
    }
    _print_program_info_log(shaderProgram);
}