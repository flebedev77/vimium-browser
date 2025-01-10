#include "widget.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <GLFW/glfw3.h>

void widget_init(
  Widget* widget,
  void* parentApplication,
  int windowWidth,
  int windowHeight
)
{
  assert(widget);
  widget->parentApplication = parentApplication;

  widget->isHovered = false;
  widget->isDown = false;

  if (widget->texture != NULL)
  {
    widget->hasTexture = true;
  } else 
  {
    widget->hasTexture = false;
  }


  float trX, trY;
  float brX, brY;
  float blX, blY;
  float tlX, tlY;
  Widget wid = *widget;
  windowPosToNormalisedPos(wid.x + wid.w, wid.y, windowWidth, windowHeight, &trX, &trY);
  windowPosToNormalisedPos(wid.x + wid.w, wid.y + wid.h, windowWidth, windowHeight, &brX, &brY);
  windowPosToNormalisedPos(wid.x, wid.y + wid.h, windowWidth, windowHeight, &blX, &blY);
  windowPosToNormalisedPos(wid.x, wid.y, windowWidth, windowHeight, &tlX, &tlY);

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
  

  /*texture_init(&tex, "../assets/logo.jpeg");*/
}

void widget_render(Widget* widget, GLFWwindow* window)
{
  assert(widget);
  
  double mouseX, mouseY;
  glfwGetCursorPos(window, &mouseX, &mouseY);
  float mx = (float)mouseX, my = (float)mouseY;


  Widget w = *widget;
  if (
    mx < w.x + w.w &&
    mx + 1 > w.x &&
    my < w.y + w.h &&
    my + 1 > w.y
  )
  {
    if (widget->clickCallback)
    {
      widget->clickCallback(widget->parentApplication);
    }
  }

  if (widget->shaderProgram != 0)
  {
    glUseProgram(widget->shaderProgram);
  } else 
  {
    printf("Widget dosen't have associated shader program! Is the WIDGET_AMOUNT equal to the actual amount of widgets?\n");
  }
  glBindVertexArray(widget->meshVAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void widget_setClickcallback(Widget* widget, WidgetCallback callback)
{
  assert(widget);
  widget->clickCallback = callback;
}

void widget_delete(Widget* widget)
{
  glDeleteVertexArrays(1, &widget->meshVAO);
  glDeleteBuffers(1, &widget->meshVBO);
  glDeleteBuffers(1, &widget->meshEBO);
}
