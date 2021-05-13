#include <GL/glew.h>
#include <shader.h>
#include <window.h>
#include <initGL.h>


void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

#include <stdio.h>

int main() {

    GLFWwindow* window = createWindow(800, 640, "hello triangle");

    initGlew();



    GLuint vao;
    GLuint vbo;

    /* geometry to use. these are 3 xyz points (9 floats total) to make a triangle */
    GLfloat points[] = { 0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f };

    /* a vertex buffer object (VBO) is created here. this stores an array of
    data on the graphics adapter's memory. in our case - the vertex points */
    glGenBuffers( 1, &vbo );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, 9 * sizeof( GLfloat ), points, GL_STATIC_DRAW );

    /* the vertex array object (VAO) is a little descriptor that defines which
    data from vertex buffer objects should be used as input variables to vertex
    shaders. in our case - use our only VBO, and say 'every three floats is a
    variable' */
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );
    /* "attribute #0 should be enabled when this vao is bound" */
    glEnableVertexAttribArray( 0 );
    /* this VBO is already bound, but it's a good habit to explicitly specify which
    VBO's data the following vertex attribute pointer refers to */
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    /* "attribute #0 is created from every 3 variables in the above buffer, of type
    float (i.e. make me vec3s)" */
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );


    GLuint vertexShader = getShaderFromFileString("vertex.glsl", GL_VERTEX_SHADER);
    GLuint fragmentShader = getShaderFromFileString("fragment.glsl", GL_FRAGMENT_SHADER);
    GLuint shaderProgram = createShaderProgram({vertexShader, fragmentShader});





    while ( !glfwWindowShouldClose( window ) ) {
        /* wipe the drawing surface clear */
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glUseProgram(shaderProgram );
        glBindVertexArray( vao );
        /* draw points 0-3 from the currently bound VAO with current in-use shader */
        glDrawArrays( GL_TRIANGLES, 0, 3 );
        /* update other events like input handling */
        glfwPollEvents();
        /* put the stuff we've been drawing onto the display */
        glfwSwapBuffers( window );
    }

    /* close GL context and any other GLFW resources */
    glfwTerminate();
    return 0;
}