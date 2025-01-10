#pragma once
#include <glad.h>
#include <GL/gl.h>
#include <assert.h>
#include "./config.h"
#include "../lib/include/stb_image.h"

typedef struct {
  int width, height, nrChannels;
  unsigned int textureHandle;
  unsigned char* textureData;
} Texture;

int texture_init(Texture* tex, const char* filePath);
int texture_delete(Texture* tex);
