#ifndef SHADER_H
#define SHADER_H


#include <glad/glad.h>

#include <stdio.h>
#include <stdlib.h>
// shader id
// read shader
// error check
// load shader
// shader_t load_shader(const char* v, const char* f);
// shader_t ID(const char* v, const char* f);
// void read_shd_file(char *shd_file);

typedef struct {
    unsigned int ID;
} shader_t;

shader_t* shader_init(char* v, char* f);

/* private functions */
static void read_shd_file(char** shd_buffer, char* shd_file);
static unsigned int generate_id(shader_t *shader);

#endif
