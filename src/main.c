#include "application.h"
#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>


int main() {
  Application app = application_createApp();

  if (application_initApp(&app, 640, 480) == APPLICATION_ERROR) 
  {
    printf("Error initializing app");
    return 1;
  }
  
  while (app.isRunning)
  {
    application_loopApp(&app);
  }

  application_quitApp(&app);
  return 0;
}
