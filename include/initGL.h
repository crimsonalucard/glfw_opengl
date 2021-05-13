#pragma once

#include <GL/glew.h>

void initGlew() {
    /* start GLEW extension handler */
    glewExperimental = GL_TRUE;
    glewInit();

    /* tell GL to only draw onto a pixel if the shape is closer to the viewer
than anything already drawn at that pixel */
    glEnable(GL_DEPTH_TEST); /* enable depth-testing */
    glEnable(GL_CULL_FACE);
    /* with LESS depth-testing interprets a smaller depth value as meaning "closer" */
    glDepthFunc(GL_LESS);

    const GLubyte *renderer;
    const GLubyte *version;

    /* get version info */
    renderer = glGetString(GL_RENDERER); /* get renderer string */
    version = glGetString(GL_VERSION);  /* version as a string */
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);
}