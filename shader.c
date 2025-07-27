#include "shader.h"
#include <stdio.h>
#include <stdlib.h>

// free shader later
shader_t* shader_init(char* v, char* f) {
    printf("Initializing shaders!\n");
    shader_t* shd = malloc(sizeof(shader_t));
    if (!shd) {
        fprintf(stderr, "Unable to allocate memory for {shader_t}");
        exit(EXIT_FAILURE);
    }

    // read shader file
    char* vertex_buffer;
    char* fragment_buffer;
    read_shd_file(&vertex_buffer, v);
    read_shd_file(&fragment_buffer, f);

    unsigned int vertex_shader;
    unsigned int fragment_shader;

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, (const char*const*)vertex_buffer, NULL);
    glCompileShader(vertex_shader);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, (const char*const*)fragment_buffer, NULL);
    glCompileShader(fragment_shader);
    
    shd->ID = glCreateProgram();
    glAttachShader(shd->ID, vertex_shader);
    glAttachShader(shd->ID, fragment_shader);
    glLinkProgram(shd->ID);
    
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return shd;
}

static void read_shd_file(char **shd_buffer, char* shd_file) {    
    printf("Reading shader files\n");
    FILE *fp = fopen(shd_file, "rb");
    if (!fp) {
        fprintf(stderr, "Unable to open file %s\n", shd_file);
        exit(EXIT_FAILURE);
    }

    size_t size;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    if(size == 0) {
        fprintf(stderr, "%s size is 0\n", shd_file);
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    *shd_buffer = malloc(size + 1);
    if (!shd_buffer) {
        fprintf(stderr, "Failed memory allocation for shader buffer");
        fclose(fp);
        free(shd_buffer);
        exit(EXIT_FAILURE);
    }

    fread(*shd_buffer, size, 1, fp);
    (*shd_buffer)[size] = '\0';
    printf("%s\n", *shd_buffer);
    fclose(fp);
}
