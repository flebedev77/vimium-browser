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
#include "../util.h"

typedef struct 
{
  unsigned int meshVAO; // Vertices
  unsigned int meshVBO; // Vertex positions
  unsigned int meshEBO; // Indicies

  float x, y, w, h;
} Widget;

void widget_init(Widget* widget, float x, float y, float w, float h, int windowWidth, int windowHeight);
void widget_render(Widget* widget);
