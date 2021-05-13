#pragma once;

#include <GL/glew.h>
#include <logging.h>
bool is_valid(GLuint program){
    glValidateProgram(program);
    int params = -1;
    glGetProgramiv(program, GL_VALIDATE_STATUS, &params);
    printf("program %i GL_VALIDATE_STATUS = %i\n", program, params);
    if(GL_TRUE != params){
        _print_program_info_log(program);
        return false
    }
    return true;
}