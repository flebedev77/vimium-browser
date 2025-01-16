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

typedef struct {
  Texture* textures;
  size_t textureAmount;
} TextureManager;

int texture_init(Texture* tex, const char* filePath);
int texture_initFromMemory(Texture* tex, unsigned char* data);
int texture_delete(Texture* tex);

void texture_initManager(TextureManager* tm);
void texture_deleteManager(TextureManager* tm);
Texture* texture_addTexture(TextureManager* tm, Texture t);

