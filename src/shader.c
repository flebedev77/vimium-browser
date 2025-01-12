#include "shader.h"

int shader_createFromShader(
  unsigned int* shaderProgram,
  const char* vertexShaderSource,
  const char* fragmentShaderSource
)
{
  int  success;
  char infoLog[LOG_MAX_LENGTH];

  
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

  (*shaderProgram) = glCreateProgram();
  glAttachShader(*shaderProgram, vertexShader);
  glAttachShader(*shaderProgram, fragmentShader);
  glLinkProgram(*shaderProgram);

  glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(*shaderProgram, LOG_MAX_LENGTH, NULL, infoLog);
    return APPLICATION_ERROR;
  }

  glUseProgram(*shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  return APPLICATION_SUCCESS;
}

int shader_createTextured(unsigned int* shaderProgram)
{
  const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec2 aTexCoord;\n"
    "out vec2 TexCoord;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "   TexCoord = aTexCoord;\n"
    "}\0";


  const char *fragmentShaderSource = 
           "#version 330 core\n"
           "out vec4 FragColor;\n"
           "in vec2 TexCoord;\n"
           "uniform sampler2D textureSampler;\n"
           "void main()\n"
           "{\n"
           "    FragColor = texture(textureSampler, TexCoord);\n"
           "}\n";

  return shader_createFromShader(
    shaderProgram,
    vertexShaderSource,
    fragmentShaderSource
  );
}

int shader_createColored(
  unsigned int* shaderProgram,
  float r,
  float g,
  float b
)
{
  const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";


  char formattedFragmentShader[512];

  snprintf(formattedFragmentShader, sizeof(formattedFragmentShader),
           "#version 330 core\n"
           "out vec4 FragColor;\n"
           "void main()\n"
           "{\n"
           "    FragColor = vec4(%f, %f, %f, 1.0f);\n"
           "}\n", r, g, b);
  const char *fragmentShaderSource = formattedFragmentShader;

  return shader_createFromShader(
    shaderProgram,
    vertexShaderSource,
    fragmentShaderSource
  );
}

void shader_delete(unsigned int shaderProgram)
{
  glDeleteShader(shaderProgram);
}
