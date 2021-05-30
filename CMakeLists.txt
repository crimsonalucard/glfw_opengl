cmake_minimum_required(VERSION 3.19)
project(opengl_try)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(opengl_try
        src/main.cpp
        include/logging.h
        include/error.h
        src/shader.cpp
        include/shader.h
        include/utils.h
        src/utils.cpp
        include/window.h
        src/window.cpp
        include/initGL.h
        include/loadVertices.h
        src/loadVertices.cpp
        src/logging.cpp
        include/gui.h)

target_include_directories(opengl_try PUBLIC include ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS})
target_link_libraries(opengl_try OpenGL::GL ${GLEW_LIBRARIES} glfw imgui -static-libgcc -static-libstdc++)