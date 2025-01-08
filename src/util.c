#include "util.h"

void normalisedPosToWindowPos(
  float x,
  float y,
  int windowWidth,
  int windowHeight,
  float* wx,
  float* wy
)
{
  if (!wx || !wy)
  {
    printf("Error! Window x and window y are null");
    return;
  }
  
  (*wx) = (x + 1) * 0.5f * (float)windowWidth;
  (*wy) = (1 - y) * 0.5f * (float)windowHeight;
}

void windowPosToNormalisedPos(
  float x,
  float y,
  int windowWidth,
  int windowHeight,
  float* nx,
  float* ny
)
{
  if (!nx || !ny)
  {
    printf("Error! Normalised x or normalised y are null");
    return;
  } 

  (*nx) = (2.f * x / (float)windowWidth) - 1.f;
  (*ny) = 1.f - (2.f * y / (float)windowHeight);
}
