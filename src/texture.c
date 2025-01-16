#define STB_IMAGE_IMPLEMENTATION
#include "texture.h"

int texture_init(Texture* tex, const char* filePath)
{
  tex->textureData = stbi_load(
    filePath,
    &tex->width,
    &tex->height,
    &tex->nrChannels,
    0
  );

  if (DEBUG)
  {
    printf("Loaded image %s %dx%dpx\n", filePath, tex->width, tex->height);
  }
  return texture_initFromMemory(tex, tex->textureData);
}

int texture_initFromMemory(Texture* tex, unsigned char* data)
{
  if (tex == NULL)
  {
    return APPLICATION_ERROR;
  }

  tex->textureData = data;

  if (!tex->textureData)
  {
    return APPLICATION_ERROR;
  }

  glGenTextures(1, &tex->textureHandle);
  glBindTexture(GL_TEXTURE_2D, tex->textureHandle);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->width, tex->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->textureData);
  glGenerateMipmap(GL_TEXTURE_2D);

  return APPLICATION_SUCCESS;

}

int texture_delete(Texture* tex)
{
  assert(tex);
  
  glDeleteTextures(1, &tex->textureHandle);
}


void texture_initManager(TextureManager* tm)
{
  assert(tm);

  tm->textureAmount = 0;
  tm->textures = (Texture*)malloc(tm->textureAmount * sizeof(Texture));
}

void texture_deleteManager(TextureManager* tm)
{
  assert(tm);
  free(tm->textures);
}

Texture* texture_addTexture(TextureManager* tm, Texture t)
{
  assert(tm);
  tm->textureAmount++;
  tm->textures = (Texture*)realloc(tm->textures, tm->textureAmount * sizeof(Texture));

  size_t index = tm->textureAmount-1;
  tm->textures[index] = t;
  return &tm->textures[index];
}
