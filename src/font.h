#pragma once
#include "config.h"
#include "ui/widget.h"
#include "texture.h"
#include "shader.h"
#include "util.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <ft2build.h>
#include FT_FREETYPE_H

typedef struct {
  char textChar;
  Widget widget; 
  int bearingX;
  int bearingY;
  unsigned int advance;
  Texture texture;
} Character;

typedef struct {
  Character* characters; 
  size_t length;
  size_t size;
} Text;

typedef struct {
  FT_Library ftlib;
  Text* texts;
  unsigned int textAmount;

  FT_Face* faces;
  unsigned int faceAmount;
} FontManager;

int font_initFontManager(FontManager* fm);
void font_deleteFontManager(FontManager* fm);

int font_loadFile(
    FontManager* fm,
    FT_Face** face, 
    const char* ttfPath
);

int font_createTextWidget(
    FontManager* fm,
    void* parentApplication,
    unsigned int windowWidth,
    unsigned int windowHeight,
    FT_Face* face,
    unsigned int size,
    float x,
    float y,
    Color3f color,
    char text[]
);

void font_renderTextWidgets(
    FontManager* fm,
    GLFWwindow* window
);
