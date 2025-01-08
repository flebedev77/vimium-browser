#include "widget.h"
#include <GL/gl.h>
#include <GL/glext.h>

void widget_init(
  Widget* widget,
  float x,
  float y,
  float w,
  float h,
  int windowWidth,
  int windowHeight
)
{
  assert(widget);

  widget->x = x;
  widget->y = y;
  widget->w = w;
  widget->h = h;

  float trX, trY;
  float brX, brY;
  float blX, blY;
  float tlX, tlY;
  windowPosToNormalisedPos(x + w, y, windowWidth, windowHeight, &trX, &trY);
  windowPosToNormalisedPos(x + w, y + h, windowWidth, windowHeight, &brX, &brY);
  windowPosToNormalisedPos(x, y + h, windowWidth, windowHeight, &blX, &blY);
  windowPosToNormalisedPos(x, y, windowWidth, windowHeight, &tlX, &tlY);

  float verts[] = {
    trX, trY, 0.0f,
    brX, brY, 0.0f,
    blX, blY, 0.0f,
    tlX, tlY, 0.0f
  };

  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
  };


  glGenVertexArrays(1, &widget->meshVAO);
  glBindVertexArray(widget->meshVAO);

  glGenBuffers(1, &widget->meshVBO);
  glBindBuffer(GL_ARRAY_BUFFER, widget->meshVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

  glGenBuffers(1, &widget->meshEBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, widget->meshEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

}

void widget_render(Widget* widget)
{
  assert(widget);

  glBindVertexArray(widget->meshVAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
