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

typedef void (*WidgetCallback)(int);

typedef struct 
{
  unsigned int meshVAO; // Vertices
  unsigned int meshVBO; // Vertex positions
  unsigned int meshEBO; // Indicies
  
  WidgetCallback clickCallback;

  float x, y, w, h;
} Widget;

void widget_init(Widget* widget, float x, float y, float w, float h, int windowWidth, int windowHeight);
void widget_setClickcallback(Widget* widget, WidgetCallback callback);
void widget_render(Widget* widget, GLFWwindow* window);
