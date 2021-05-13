#include <shader.h>

GLuint getShaderFromFileString(std::string fileName, GLuint GL_TYPE_SHADER) {
    auto shaderSrc = readFromFile(fileName);
    const char *shaderSrcCString = shaderSrc.c_str();
    auto shader = glCreateShader(GL_TYPE_SHADER);
    glShaderSource(shader, 1, &shaderSrcCString, NULL);
    glCompileShader(shader);
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
    return shaderProgram;
}
