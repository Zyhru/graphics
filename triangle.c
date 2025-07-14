#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
    const int WIDTH = 640;
    const int HEIGHT = 480; 

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Triangle", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create window\n"); 
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n"); 
        return EXIT_FAILURE;
    }

    glViewport(0, 0, WIDTH, HEIGHT);
    
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.5f, 0.2f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
}
