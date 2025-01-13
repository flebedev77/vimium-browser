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
#include "ui/widget.h"
#include "config.h"
#include "shader.h"
#include "texture.h"
#include "font.h"


typedef struct
{
  GLFWwindow* window;
  unsigned int windowWidth;
  unsigned int windowHeight;
  bool isRunning;
  bool isDebug;

  Widget widgets[WIDGET_AMOUNT];
  Texture* loadedTextures;
  FontManager fontManager; 
} Application;

Application application_createApp();
int application_initApp(Application* app, int width, int height);

void application_loopApp(Application* app);
void application_quitApp(Application* app);
