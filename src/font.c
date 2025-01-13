#include "font.h"

int font_initFontManager(FontManager* fm)
{
  assert(fm);

  if (FT_Init_FreeType(&fm->ftlib))
  {
    printf("Failed to init FreeType\n");
    return APPLICATION_ERROR;
  }

  fm->textAmount = 0;
  fm->texts = (Text*)malloc(fm->textAmount * sizeof(Text));

  fm->faceAmount = 0;
  fm->faces = (FT_Face*)malloc(fm->faceAmount * sizeof(FT_Face));

  return APPLICATION_SUCCESS;
}

void font_deleteFontManager(FontManager* fm)
{
  assert(fm);

  free(fm->faces);
  free(fm->texts);
}

int font_loadFile(
    FontManager* fm,
    FT_Face** face, 
    const char* ttfPath
)
{
  assert(fm);
  assert(face);

  FT_Face ftface;
  if (FT_New_Face(fm->ftlib, ttfPath, 0, &ftface))
  {
    if (DEBUG)
    {
      printf("FreeType failed to load font %s\n", ttfPath);
    }
    return APPLICATION_ERROR;
  }  

  fm->faceAmount++;
  fm->faces = (FT_Face*)realloc(
    fm->faces,
    fm->faceAmount * sizeof(FT_Face)
  );
  fm->faces[fm->faceAmount-1] = ftface;
  *face = &fm->faces[fm->faceAmount-1];

  return APPLICATION_SUCCESS;
}

int font_createTextWidget(
    FontManager* fm,
    FT_Face* face,
    unsigned int size,
    float x,
    float y,
    char text[]
)
{
  assert(fm);
  assert(face);

  size_t textLen = strlen(text);

  if (textLen == 0)
  {
    return APPLICATION_ERROR;
  }

  Text textWidget;
  textWidget.characters = (Character*)malloc(
    textLen * sizeof(Character)
  );

  for (size_t i = 0; i < textLen; i++)
  {
    textWidget.characters[i].textChar = text[i];
  }

  return APPLICATION_SUCCESS;
}
