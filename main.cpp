#include <GL/glew.h>
#include <shader.h>
#include <window.h>
#include <initGL.h>
#include <loadVertices.h>


void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {

    GLFWwindow *window = createWindow(800, 640, "hello triangle");

    initGlew();

    /* geometry to use. these are 3 xyz points (9 floats total) to make a triangle */
    GLfloat points[] = {0.0f, 0.5f, 0.0f,
                        -0.5f, -0.5f, 0.0f,
                        0.5f, -0.5f, 0.0f,
    };
    GLfloat colors[] = {1.0f, 0.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 0.0f, 1.0f};
    GLuint vertex_attribute_object = loadTrianglesVertices(points, colors, sizeof(points));


    GLuint vertexShader = getShaderFromFileString("vertex.glsl", GL_VERTEX_SHADER);
    GLuint fragmentShader = getShaderFromFileString("fragment.glsl", GL_FRAGMENT_SHADER);
    GLuint shaderProgram = createShaderProgram({vertexShader, fragmentShader});


    while (!glfwWindowShouldClose(window)) {
        /* wipe the drawing surface clear */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(vertex_attribute_object);
        /* draw points 0-3 from the currently bound VAO with current in-use shader */
        glDrawArrays(GL_TRIANGLES, 0, 3);
        /* update other events like input handling */
        glfwPollEvents();
        /* put the stuff we've been drawing onto the display */
        glfwSwapBuffers(window);
    }

    /* close GL context and any other GLFW resources */
    glfwTerminate();
    return 0;
}