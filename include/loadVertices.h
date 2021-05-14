#pragma once
#include <GL/glew.h>
#include <initializer_list>
#include <array>


struct VertexArray{
    VertexArray(const GLuint index, const GLfloat* vertices, const size_t size);

    const GLuint mIndex;
    const size_t mSize;
    const GLfloat* mVertices;
    const GLuint mVertexBuffer;

};

void attachVertexArrayToVertexAttribute(VertexArray* vertexArray, GLuint vertexAttribute);

GLuint createVertexBufferObject(const GLfloat vertices[], size_t size);
GLuint loadTrianglesVertices(const GLfloat vertices[], const GLfloat colors[], size_t size);