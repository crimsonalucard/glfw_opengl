#include <shader.h>

void _print_program_info_log(GLuint program){
    int actual_length;
    char log[2048];
    glGetProgramInfoLog(program, 2048, &actual_length, log);
    printf("program info log for GL index %u:\n%s", program, log);
}

void _print_shader_info_log(GLuint shader_index){
    int actual_length;
    char log[2048];
    glGetShaderInfoLog(shader_index, 2048, &actual_length, log);
    printf("shader info log for GL index %u:%s\n", shader_index, log);
}

GLuint getShaderFromFileString(std::string fileName, GLuint GL_TYPE_SHADER) {
    auto shaderSrc = readFromFile(fileName);
    const char *shaderSrcCString = shaderSrc.c_str();
    auto shader = glCreateShader(GL_TYPE_SHADER);
    glShaderSource(shader, 1, &shaderSrcCString, NULL);
    glCompileShader(shader);
    int params = -1;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &params);
    if(GL_TRUE != params){
        fprintf(stderr, "ERROR: GL shader index %i did not compile\n", shader);
        _print_shader_info_log(shader);
        exit(1);
    }
    return shader;
}


GLuint createShaderProgram(const std::initializer_list<GLuint> &shaderList) {
    auto shaderProgram = glCreateProgram();
    for (GLuint shader : shaderList){
        glAttachShader(shaderProgram, shader);
    }

    glBindAttribLocation(shaderProgram, 0, "vertex_position");
    glBindAttribLocation(shaderProgram, 1, "vertex_color");

    glLinkProgram(shaderProgram);
    int params = -1;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &params);
    if(GL_TRUE != params){
        fprintf(stderr, "ERROR: could not link shader program GL index %u\n", shaderProgram);
        _print_program_info_log(shaderProgram);
        exit(1);
    }
    return shaderProgram;
}
