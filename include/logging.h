#pragma once
#include <iostream>
#include <GL/glew.h>

void print_shader_info_log(GLuint shader_index);
void print_program_info_log(GLuint program);
void print_all(GLuint program);
const char* GL_type_to_string(GLenum type);