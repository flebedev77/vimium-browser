#include "util.h"

void screenPosToNormalisedPos(
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
    printf("Error! Normalised x and normalised y are null");
    return;
  }
  
  (*nx) = ((x / (float)windowWidth)*2.f)-0.5f;
  (*ny) = ((y / (float)windowHeight)*2.f)-0.5f;

  (*nx) = x / (float)windowWidth;
  (*ny) = y / (float)windowHeight;
}
