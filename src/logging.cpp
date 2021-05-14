#include <shader.h>
#include <logging.h>


void print_program_info_log(GLuint program){
    int actual_length;
    char log[2048];
    glGetProgramInfoLog(program, 2048, &actual_length, log);
    printf("program info log for GL mIndex %u:\n%s", program, log);
}

void print_shader_info_log(GLuint shader_index){
    int actual_length;
    char log[2048];
    glGetShaderInfoLog(shader_index, 2048, &actual_length, log);
    printf("shader info log for GL mIndex %u:%s\n", shader_index, log);
}

const char* GL_type_to_string(GLenum type){
    switch (type) {
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

void print_all(GLuint program) {
    std::cout << "----------------------------------" << std::endl <<
              "shader program " << program << " info:" << std::endl;
    int params = -1;
    glGetProgramiv(program, GL_LINK_STATUS, &params);
    std::cout << "GL_LINK_STATUS = " << params << std::endl;
    glGetProgramiv(program, GL_ATTACHED_SHADERS, &params);
    std::cout << "GL_ATTACHED_SHADERS = " << params << std::endl;
    glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &params);
    std::cout << "GL_ACTIVE_ATTRIBUTES = " << params << std::endl;
    for (GLuint i = 0; i < (GLuint) params; i++) {
        char name[64];
        int max_length = 64;
        int actual_length = 0;
        int size = 0;
        GLenum type;
        glGetActiveAttrib(program, i, max_length, &actual_length, &size, &type, name);
        if (size > 1) {
            for (int j = 0; j < size; j++) {
                char long_name[64];
                sprintf(long_name, "%s[%i]", name, j);
                int location = glGetAttribLocation(program, long_name);
                printf(" i%) type:%s name:%s location:%i\n", i, GL_type_to_string(type), long_name, location);
            }
        } else {
            int location = glGetAttribLocation(program, name);
            printf(" %i) type:%s name:%s location:%i\n", i, GL_type_to_string(type), name, location);
        }
    }
    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &params);
    printf("GL_ACTIVE_UNIFORMS = %i\n", params);
    for (GLuint i = 0; i < (GLuint) params; i++) {
        char name[64];
        int max_length = 64;
        int actual_length = 0;
        int size = 0;
        GLenum type;
        glGetActiveUniform(program, i, max_length, &actual_length, &size, &type, name);
        if (size > 1) {
            for (int j = 0; j < size; j++) {
                char long_name[64];
                sprintf(long_name, "%s[%i]", name, j);
                int location = glGetUniformLocation(program, long_name);
                printf(" i%) type:%s location:%i\n", i, GL_type_to_string(type), name, location);
            }
        } else {
            int location = glGetUniformLocation(program, name);
            printf(" %i) type:%s name:%s location:%i\n", i, GL_type_to_string(type), name, location);
        }
    }
    //not finished .... complete this....
    print_program_info_log(program);
}
