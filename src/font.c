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
  if (fm->faces == NULL)
  {
    if (DEBUG)
    {
      printf("Failed to reallocate faces\n");
    }
    return APPLICATION_ERROR;
  }
  fm->faces[fm->faceAmount-1] = ftface;
  *face = &fm->faces[fm->faceAmount-1];

  return APPLICATION_SUCCESS;
}

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
)
{
  assert(fm);
  assert(face);
  assert(parentApplication);

  size_t textLen = strlen(text);

  if (textLen == 0)
  {
    if (DEBUG)
    {
      printf("Text was empty\n");
    }
    return APPLICATION_ERROR;
  }

  Text textWidget;
  textWidget.length = textLen;
  textWidget.size = size;
  textWidget.characters = (Character*)malloc(
    textLen * sizeof(Character)
  );

  if (textWidget.characters == NULL) {
    if (DEBUG) {
      printf("Memory allocation for characters failed\n");
    }
    return APPLICATION_ERROR;
  }

  unsigned int shader;
  if (shader_createText(&shader, color.r, color.g, color.b) == APPLICATION_ERROR)
  {
    if (DEBUG)
    {
      printf("Failed to init shader\n");
    }
    return APPLICATION_ERROR;
  }

  FT_Set_Pixel_Sizes(*face, 0, size);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  for (size_t i = 0; i < textLen; i++)
  {
    Character* character = &textWidget.characters[i];

    (*character).textChar = text[i];

    if (FT_Load_Char(*face, text[i], FT_LOAD_RENDER) && DEBUG)
    {
      printf("FreeType failed to load glyph %s", text[i]);
    }

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        (*face)->glyph->bitmap.width,
        (*face)->glyph->bitmap.rows,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        (*face)->glyph->bitmap.buffer
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    character->texture.textureHandle = texture;
    character->advance = (*face)->glyph->advance.x;
    character->bearingX = (*face)->glyph->bitmap_left;
    character->bearingY = (*face)->glyph->bitmap_top;
    Widget w;
    w.x = x + character->bearingX;
    w.y = y - character->bearingY;
    w.w = (*face)->glyph->bitmap.width;
    w.h = (*face)->glyph->bitmap.rows;//size;
    w.shaderProgram = shader;
    w.texture = &character->texture;
    (*character).widget = w;

    widget_init(&(*character).widget, parentApplication, windowWidth, windowHeight);

    x += (character->advance >> 6);
  }

  fm->textAmount++;
  fm->texts = (Text*)realloc(
    fm->texts,
    fm->textAmount * sizeof(Text)
  );
  fm->texts[fm->textAmount-1] = textWidget;

  return APPLICATION_SUCCESS;
}

void font_renderTextWidgets(
    FontManager* fm,
    GLFWwindow* window
)
{
    assert(fm);
    assert(window);

    for (size_t i = 0; i < fm->textAmount; i++)  
    {
      if (fm->texts[i].length != 0)
      {
        for (size_t j = 0; j < fm->texts[i].length; j++)
        {
            widget_render(&fm->texts[i].characters[j].widget, window);
        }
      }
    }
}
