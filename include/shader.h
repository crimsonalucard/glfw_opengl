#pragma once
#include <GL/glew.h>
#include <string>
#include <utils.h>
#include <cstdarg>
#include <initializer_list>
#include <linux/inotify.h>


GLuint getShaderFromFileString(std::string fileName, GLuint GL_TYPE_SHADER);

GLuint createShaderProgram(const std::initializer_list<GLuint> &shaderList);

GLuint createShaderProgramFromFileStrings(std::string vertexShaderString, std::string fragmentShaderString);

void reloadShaderProgramFromFiles(GLuint* shaderProgram, std::string vertexShaderString, std::string fragmentShaderString);