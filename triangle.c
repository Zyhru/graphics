#include "shader.h"
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

    /* Triangle Data */
    float triangle[] = {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,   
        -0.5f, -0.5f, 0.0f,
    };
    /* Shaders */
    shader_t* t_shader = shader_init("shaders/vertex.glsl", "shaders/fragment.glsl");
    if (!t_shader) {
        printf("Failed dude!\n");
        return -1;
    }

    /* OpenGL Create Objects */
    unsigned int VAO;
    unsigned int VBO;

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    /* OpenGL Bind Objects */
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
    
    /* OpenGL Vertex Attrib Pointers */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.5f, 0.2f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(t_shader->ID);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, triangle[0], 3);
        glBindVertexArray(0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    free(t_shader);
    glfwDestroyWindow(window);
}
