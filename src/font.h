#pragma once
#include "config.h"
#include "ui/widget.h"
#include "texture.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <ft2build.h>
#include FT_FREETYPE_H

typedef struct {
  char textChar;
  Widget widget; 
} Character;

typedef struct {
  Character* characters; 
  unsigned int length;
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
    FT_Face* face,
    unsigned int size,
    float x,
    float y,
    char text[]
);
