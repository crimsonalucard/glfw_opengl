#include <loadVertices.h>

static GLuint vertexAttribIndex = 0;

VertexArray::VertexArray(const GLuint index, const GLfloat *vertices, const size_t size) :
        mIndex(index),
        mSize(size),
        mVertices(vertices),
        mVertexBuffer(createVertexBufferObject(mVertices, size)) {
}

GLuint createVertexAttribObject(){
    /* the vertex array object (VAO) is a little descriptor that defines which
    data from vertex buffer objects should be used as input variables to vertex
    shaders. in our case - use our only VBO, and say 'every three floats is a
    variable' */
    GLuint vertex_attribute_object;
    glGenVertexArrays(1, &vertex_attribute_object);
    glBindVertexArray(vertex_attribute_object);
    return vertex_attribute_object;
}

void attachVertexArrayToVertexAttribute(const GLuint& vertexAttributeObject, const VertexArray& vertexArray){
    /* "attribute #0 should be enabled when this vertex_attribute_object is bound" */
    glEnableVertexAttribArray(vertexArray.mIndex);
/* this VBO is already bound, but it's a good habit to explicitly specify which
VBO's data the following vertex attribute pointer refers to */
    glBindBuffer(GL_ARRAY_BUFFER, vertexArray.mVertexBuffer);
/* "attribute #0 is created from every 3 variables in the above buffer, of type
float (i.e. make me vec3s)" */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void attachVertexArrayToVertexAttribute2(const GLuint& vertexAttributeObject, const VertexArray& vertexArray){
    /* "attribute #0 should be enabled when this vertex_attribute_object is bound" */
    glEnableVertexAttribArray(vertexArray.mIndex);
/* this VBO is already bound, but it's a good habit to explicitly specify which
VBO's data the following vertex attribute pointer refers to */
    glBindBuffer(GL_ARRAY_BUFFER, vertexArray.mVertexBuffer);
/* "attribute #0 is created from every 3 variables in the above buffer, of type
float (i.e. make me vec3s)" */
    glVertexAttribPointer(vertexArray.mIndex, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}


GLuint createVertexBufferObject(const GLfloat vertices[], size_t size) {
    GLuint vertex_buffer_object;
    glGenBuffers(1, &vertex_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    return vertex_buffer_object;
}


GLuint loadTrianglesVertices(const GLfloat vertices[], const GLfloat colors[], size_t size) {
    GLuint vertex_attribute_object = createVertexAttribObject();
    VertexArray verticeBuffer = VertexArray{0, vertices, size};
    VertexArray verticeColorBuffer = VertexArray{1, colors, size};
    attachVertexArrayToVertexAttribute(vertex_attribute_object, verticeBuffer);
    attachVertexArrayToVertexAttribute2(vertex_attribute_object, verticeColorBuffer);
    return vertex_attribute_object;
}
