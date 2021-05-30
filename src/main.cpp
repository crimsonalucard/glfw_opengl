#include <GL/glew.h>
#include <shader.h>
#include <window.h>
#include <initGL.h>
#include <loadVertices.h>
#include <logging.h>
#include <imgui.h>
#include <math.h>


void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void bounce_left_and_right(float velocity, float angular_velocity, float location_matrix[], int shader_location_matrix, float rotation_matrix[], int shader_rotation_matrix){
    static float direction = 1.0;
    static float last_position = -1.0;
    static float last_angle = 0.0f;
    static float previousTime = glfwGetTime();
    float currentTime = glfwGetTime();
    float timePassed = currentTime - previousTime;
    previousTime = currentTime;
    direction = last_position >= 1.0 || last_position <= -1.0 ? -direction : direction;
    float position = velocity * direction * timePassed + last_position;
    float angle = angular_velocity * direction * timePassed + last_angle;
    last_angle = angle;
    last_position = position;
    location_matrix[12] = position;
    rotation_matrix[0] = cos(angle);
    rotation_matrix[1] = -sin(angle);
    rotation_matrix[4] = sin(angle);
    rotation_matrix[5] = cos(angle);
    glUniformMatrix4fv(shader_location_matrix, 1, GL_FALSE, location_matrix);
    glUniformMatrix4fv(shader_rotation_matrix, 1, GL_TRUE, rotation_matrix);
}

int main() {
    IMGUI_CHECKVERSION();
    GLFWwindow *window = createWindow(800, 640, "hello triangle");

    initGlew();

    float location_matrix[] = {
            1.0f, 0.0f, 0.0f, 0.0f, //firstr column
            0.0f, 1.0f, 0.0f, 0.0f, //second column
            0.0f, 0.0f, 1.0f, 0.0f, //3rd
            0.5f, 0.0f, 0.0f, 1.0f //4th
    };
    float angle = 0.0f;
    float rotation_matrix_z[] = {
           cos(angle), -sin(angle), 0.0, 0.0,
           sin(angle), cos(angle), 0.0, 0.0,
           0.0, 0.0, 1.0, 0.0,
           0.0, 0.0, 0.0, 1.0
    };

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

    int shader_location_matrix = glGetUniformLocation(shaderProgram, "location_matrix");
    int shader_rotation_matrix = glGetUniformLocation(shaderProgram, "rotation_matrix");
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(shader_location_matrix, 1, GL_FALSE, location_matrix);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        /* wipe the drawing surface clear */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        bounce_left_and_right(3.0, 7.0, location_matrix, shader_location_matrix, rotation_matrix_z, shader_rotation_matrix);
        glUseProgram(shaderProgram);
        glBindVertexArray(vertex_attribute_object);
        /* draw points 0-3 from the currently bound VAO with current in-use shader */
        glDrawArrays(GL_TRIANGLES, 0, 3);
        /* update other events like input handling */
        glfwPollEvents();
        /* put the stuff we've been drawing onto the display */
        glfwSwapBuffers(window);

        if(glfwGetKey(window, GLFW_KEY_R)){
            reloadShaderProgramFromFiles(&shaderProgram, "vertex.glsl", "fragment.glsl");
        }
    }

    /* close GL context and any other GLFW resources */
    glfwTerminate();
    return 0;
}