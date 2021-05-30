#include <shader.h>
#include <logging.h>
#include <functional>

GLuint getShaderFromFileString(std::string fileName, GLuint GL_TYPE_SHADER) {
    auto shaderSrc = readFromFile(fileName);
    const char *shaderSrcCString = shaderSrc.c_str();
    auto shader = glCreateShader(GL_TYPE_SHADER);
    glShaderSource(shader, 1, &shaderSrcCString, NULL);
    glCompileShader(shader);
    int params = -1;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &params);
    if(GL_TRUE != params){
        fprintf(stderr, "ERROR: GL shader mIndex %i did not compile\n", shader);
        print_shader_info_log(shader);
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
        fprintf(stderr, "ERROR: could not link shader program GL mIndex %u\n", shaderProgram);
        print_program_info_log(shaderProgram);
        exit(1);
    }
    return shaderProgram;
}

GLuint createShaderProgramFromFileStrings(std::string vertexShaderString, std::string fragmentShaderString){
    auto vertexShader = getShaderFromFileString(vertexShaderString, GL_VERTEX_SHADER);
    auto fragmentShader = getShaderFromFileString(fragmentShaderString, GL_FRAGMENT_SHADER);
    return createShaderProgram({vertexShader, fragmentShader});
}

void reloadShaderProgramFromFiles(GLuint* shaderProgram, std::string vertexShaderString, std::string fragmentShaderString){
    auto newShaderProgram = createShaderProgramFromFileStrings(vertexShaderString, fragmentShaderString);
    if(newShaderProgram){
        glDeleteProgram(*shaderProgram);
        *shaderProgram = newShaderProgram;
    }
}

//computationally expensive only use during development.
bool is_valid(GLuint program){
    glValidateProgram(program);
    int params = -1;
    glGetProgramiv(program, GL_VALIDATE_STATUS, &params);
    printf("program %i GL_VALIDATE_STATUS = %i\n", program, params);
    if(GL_TRUE != params){
        print_program_info_log(program);
        return false;
    }
    return true;
}
