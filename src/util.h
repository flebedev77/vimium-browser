#pragma once
#include <stdio.h>

typedef struct 
{
  float r, g, b;
} Color3f;

void normalisedPosToWindowPos(float x, float y, int windowWidth, int windowHeight, float* wx, float* wy);

void windowPosToNormalisedPos(float x, float y, int windowWidth, int windowHeight, float* nx, float* ny);

