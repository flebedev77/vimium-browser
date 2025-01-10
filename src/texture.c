#define STB_IMAGE_IMPLEMENTATION
#include "texture.h"

int texture_init(Texture* tex, const char* filePath)
{
  if (tex == NULL)
  {
    return APPLICATION_ERROR;
  }

  tex->textureData = stbi_load(
    filePath,
    &tex->width,
    &tex->height,
    &tex->nrChannels,
    0
  );

  glGenTextures(1, &tex->textureHandle);


  stbi_image_free(tex->textureData);

  return APPLICATION_SUCCESS;
}

int texture_delete(Texture* tex)
{
  assert(tex);
  
  glDeleteTextures(1, &tex->textureHandle);
}
