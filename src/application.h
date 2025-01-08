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

#define APPLICATION_ERROR -1
#define APPLICATION_SUCCESS 1

#define LOG_MAX_LENGTH 512

#define WIDGET_AMOUNT 2

typedef struct
{
  GLFWwindow* window;
  unsigned int windowWidth;
  unsigned int windowHeight;
  bool isRunning;
  bool isDebug;
  Widget widgets[WIDGET_AMOUNT];
} Application;

Application application_createApp();
int application_initApp(Application* app, int width, int height);

void application_loopApp(Application* app);
void application_quitApp(Application* app);
