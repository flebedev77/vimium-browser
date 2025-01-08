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
      currentWidget.x,
      currentWidget.y,
      currentWidget.w,
      currentWidget.h,
      width,
      height
    );

  }
}

int application_initShaders()
{
  int  success;
  char infoLog[LOG_MAX_LENGTH];

  const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, LOG_MAX_LENGTH, NULL, infoLog);
    printf("Error compiling vertex shader %s", infoLog);
    return APPLICATION_ERROR;
  }

  const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
    "}\n";

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, LOG_MAX_LENGTH, NULL, infoLog);
    printf("Error compiling fragment shader %s", infoLog);
    return APPLICATION_ERROR;
  }

  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, LOG_MAX_LENGTH, NULL, infoLog);
    return APPLICATION_ERROR;
  }

  glUseProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  return APPLICATION_SUCCESS;
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

  //shaders
  if (application_initShaders() == APPLICATION_ERROR)
  {
    return APPLICATION_ERROR;
  }

  Widget w;
  app_ptr->widgets[0] = w;
  widget_init(&app_ptr->widgets[0], 0, 0, 100, 100, width, height);

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
    glPolygonMode(GL_FRONT_AND_BACK, (*app).isDebug ? GL_LINE : GL_FILL); 
  }
}

void application_loopApp(Application* app_ptr)
{
  assert(app_ptr);
  Application app = *app_ptr;

  app_ptr->isRunning = !glfwWindowShouldClose(app.window);
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
    widget_render(&app_ptr->widgets[i]);
  }

  glfwSwapBuffers(app.window);

  glfwPollEvents();
  usleep(16000);
}

void application_quitApp(Application* app_ptr)
{
  app_ptr->isRunning = false;
  glfwTerminate();
}
