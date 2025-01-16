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
#include "../texture.h"

typedef void (*WidgetCallback)(void*);

typedef struct 
{
  unsigned int meshVAO; // Vertices
  unsigned int meshVBO; // Vertex positions
  unsigned int meshEBO; // Indicies
  unsigned int shaderProgram;

  bool hasTexture;
  Texture* texture;
  
  WidgetCallback clickCallback;
  WidgetCallback hoverCallback;

  float x, y, w, h;

  bool isHovered;
  bool isDown;

  void* parentApplication;
} Widget;

typedef struct {
  Widget* widgets;
  size_t widgetAmount;
} WidgetManager;

void widget_init(Widget* widget, void* parentApplication, int windowWidth, int windowHeight);
void widget_render(Widget* widget, GLFWwindow* window);
void widget_delete(Widget* widget);

void widget_initManager(WidgetManager* wm);
Widget* widget_addWidget(WidgetManager* wm, Widget w);
void widget_renderManager(WidgetManager* wm, GLFWwindow* window);

void widget_deleteManager(WidgetManager* wm);
