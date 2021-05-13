#include <loadVertices.h>


GLuint loadTrianglesVertices(const GLfloat vertices[], size_t size) {

    GLuint vertex_attribute_object;
    GLuint vertex_buffer_object;
    /* a vertex buffer object (VBO) is created here. this stores an array of
    data on the graphics adapter's memory. in our case - the vertex points */
    glGenBuffers( 1, &vertex_buffer_object );
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object );
    glBufferData( GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW );

    /* the vertex array object (VAO) is a little descriptor that defines which
    data from vertex buffer objects should be used as input variables to vertex
    shaders. in our case - use our only VBO, and say 'every three floats is a
    variable' */
    glGenVertexArrays( 1, &vertex_attribute_object );
    glBindVertexArray(vertex_attribute_object );
    /* "attribute #0 should be enabled when this vertex_attribute_object is bound" */
    glEnableVertexAttribArray( 0 );
    /* this VBO is already bound, but it's a good habit to explicitly specify which
    VBO's data the following vertex attribute pointer refers to */
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object );
    /* "attribute #0 is created from every 3 variables in the above buffer, of type
    float (i.e. make me vec3s)" */
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );

    return vertex_attribute_object;
}
