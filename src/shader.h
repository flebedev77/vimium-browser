#pragma once
#include <glad.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "config.h"

/* Returns status, whether it fails or succeeds
 * Takes in a pointer for the shader program
 * and desired rgb values
 * */
int shader_createColored(
  unsigned int* shaderProgram,
  float r,
  float g,
  float b
);
