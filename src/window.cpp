#include <window.h>

GLFWwindow* createWindow(int width, int height, std::string title){
    if ( !glfwInit() ) {
        fprintf( stderr, "ERROR: could not start GLFW3\n" );
        return NULL;
    }
    /* Version 4.1 Core is a good default that should run on just about everything. Adjust later to suit project requirements. */
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    GLFWwindow* window = glfwCreateWindow( width, height, title.c_str(), NULL, NULL );
    glfwMakeContextCurrent( window );
    return window;

}