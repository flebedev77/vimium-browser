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

#define APPLICATION_ERROR -1
#define APPLICATION_SUCCESS 1

#define LOG_MAX_LENGTH 512

typedef struct
{
  GLFWwindow* window;
  bool isRunning;
  unsigned int testTriangleVBO;
  unsigned int testTriangleVAO;
} Application;

Application application_createApp();
int application_initApp(Application* app, int width, int height);

void application_loopApp(Application* app);
void application_quitApp(Application* app);
