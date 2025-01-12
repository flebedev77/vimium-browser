#include "application.h"
#include "ui/widget.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <GLFW/glfw3.h>

Application application_createApp()
{
  Application a;
  a.window = 0;
  a.windowWidth = 0;
  a.windowHeight = 0;
  a.isRunning = true;
  a.isDebug = false;
  return a;
}

void application_on_resize_callback(GLFWwindow* window, int width, int height)
{
  Application* app = (Application*)glfwGetWindowUserPointer(window);
  app->windowWidth = width;
  app->windowHeight = height;
  glViewport(0, 0, width, height);

  for (unsigned int i = 0; i < WIDGET_AMOUNT; i++) 
  {
    Widget currentWidget = app->widgets[i];

    widget_init(
      &app->widgets[i],
      currentWidget.parentApplication,
      width,
      height
    );

  }
}

void onclick(void* app_ptr)
{
  Application* app = (Application*)app_ptr;
  app->isDebug = true;
  glPolygonMode(GL_FRONT_AND_BACK, app->isDebug ? GL_LINE : GL_FILL); 
}

int application_initApp(Application* app_ptr, int width, int height)
{
  assert(app_ptr);

  if (!glfwInit())
  {
    printf("Failed initializing glfw3");
    return APPLICATION_ERROR;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  app_ptr->windowWidth = width;
  app_ptr->windowHeight = height;
  app_ptr->window = glfwCreateWindow(width, height, "Web Browser", NULL, NULL);
  if (!app_ptr->window)
  {
    glfwTerminate();
    printf("Failed opening glfw3 window");
    return APPLICATION_ERROR;
  }

  glfwSetWindowUserPointer(app_ptr->window, app_ptr);
  glfwSetWindowSizeCallback(app_ptr->window, application_on_resize_callback);

  glfwMakeContextCurrent(app_ptr->window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    fprintf(stderr, "Failed to initialize GLAD\n");
    return APPLICATION_ERROR;
  }

  printf("OpenGL %s\n", glGetString(GL_VERSION));

  glViewport(0, 0, width, height);


  unsigned int shader;
  if (shader_createTextured(&shader) == APPLICATION_ERROR)
  {
    return APPLICATION_ERROR;
  }

  app_ptr->loadedTextures = (Texture*)malloc(INITIAL_TEXTURE_AMOUNT * sizeof(Texture));

  if (texture_init(&app_ptr->loadedTextures[0], "../assets/vim.png") == APPLICATION_ERROR)
  {
    return APPLICATION_ERROR;
  }

  Widget w;
  w.x = 0;
  w.y = 0;
  w.w = 300.f;
  w.h = 300.f;
  w.shaderProgram = shader;
  w.texture = &app_ptr->loadedTextures[0];
  w.clickCallback = onclick;
  app_ptr->widgets[0] = w;

  widget_init(&app_ptr->widgets[0], app_ptr, width, height);


  return APPLICATION_SUCCESS;
}

void application_handleInput(GLFWwindow* window, Application* app)
{
  assert(app);
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, true);
  }

  if (
    glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS &&
    glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS
  )
  {
    app->isDebug = !app->isDebug;
  }
}

void application_loopApp(Application* app_ptr)
{
  assert(app_ptr);
  Application app = *app_ptr;

  if (glfwWindowShouldClose(app.window))
  {
    app_ptr->isRunning = false;
  }
  application_handleInput(app.window, app_ptr);

  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  // Immediate mode debug triangle
  /*glColor3f(1.f, 0.f, 0.f);*/
  /*glBegin(GL_TRIANGLES);*/
  /*glVertex2f(0, 0);*/
  /*glVertex2f(1, 0);*/
  /*glVertex2f(1, 1);*/
  /*glEnd();*/

  for (unsigned int i = 0; i < WIDGET_AMOUNT; i++)
  {
    widget_render(&app_ptr->widgets[i], app.window);
  }

  glfwSwapBuffers(app.window);

  glfwPollEvents();
  usleep(16000);
}

void application_quitApp(Application* app_ptr)
{
  for(unsigned int i = 0; i < WIDGET_AMOUNT; i++)
  {
    widget_delete(&app_ptr->widgets[i]);
  }

  free(app_ptr->loadedTextures);

  app_ptr->isRunning = false;
  glfwTerminate();
}
