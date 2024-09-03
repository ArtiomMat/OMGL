#include "gl.hpp"
#include "shared.hpp"
#include "Program.hpp"
#include "Shader.hpp"

namespace omgl
{
  Program::Program()
  {
    id = glCreateProgram();
  }

  void Program::AttachShader(const Shader& s)
  {
    glAttachShader(id, s.id);
    linked = false;
  }

  bool Program::Link()
  {
    if (linked)
    {
      return true;
    }

    glLinkProgram(id);
    
    GLint success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
      glGetProgramInfoLog(id, INFO_LOG_SIZE, nullptr, info_log);
    }
    
    linked = success;

    return success != 0;
  }

  void Program::Use()
  {
    glUseProgram(id);
  }

  Program::~Program()
  {
    if (id)
    {
      glDeleteProgram(id);
    }
  }
}