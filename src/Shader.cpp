#include "Shader.hpp"

#include <cstring>

#include <memory>
#include <fstream>
#include <iostream>
#include <filesystem>

namespace omgl
{
  Shader::Shader(const char* _path, Type type, bool* success) : path(new char[strlen(_path) + 1])
  {
    GLenum gl_type;
    switch (type)
    {
      case Shader::Type::Vertex:
      gl_type = GL_VERTEX_SHADER;
      break;
      case Shader::Type::Fragment:
      gl_type = GL_FRAGMENT_SHADER;
      break;
      case Shader::Type::Geometry:
      gl_type = GL_GEOMETRY_SHADER;
      break;
      case Shader::Type::Compute:
      gl_type = GL_COMPUTE_SHADER;
      break;
    }

    id = glCreateShader(gl_type);

    if (id == 0)
    {
      throw SystemException(glGetError(), "Creating shader.");
    }

    // Copy the path before anything else
    strcpy(path.get(), _path);


    bool _success = Reload();
    if (success != nullptr)
    {
      *success = _success;
    }
  }

  bool Shader::Reload()
  {
    std::ifstream f;
    f.open(path.get());

    if (!f.is_open())
    {
      std::string msg = (std::stringstream() << "Failed to open '" << path.get() << "'.").str();
      throw omgl::SystemException(0, msg.c_str());
    }

    auto data_size = std::filesystem::file_size(path.get());
    GLchar data[data_size];

    f.read(data, data_size);
    if (f.fail())
    {
      throw ReadException("Reading shader file.");
    }

    GLint gl_data_size = data_size;
    GLchar* data_as_ptr = data; // Because data is an array object, not pointer variable, so can't be referenced
    glShaderSource(id, 1, &data_as_ptr, &gl_data_size);
    glCompileShader(id);

    // Check if compilation went fine
    GLint success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if (!success)
    {
      glGetShaderInfoLog(id, INFO_LOG_SIZE, nullptr, info_log);
    }

    // TODO: Reattach, also what if program attaches a different shader of this type and then this shader still thinks it's attached????

    return success != 0;
  }

  Shader::~Shader()
  {
    if (id)
    {
      glDeleteShader(id);
    }
  }
}
