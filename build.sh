#!/bin/sh
gcc triangle.c shader.c glad.c -o triangle $(pkg-config --cflags --libs glfw3) -lGL
./triangle
