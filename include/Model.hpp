#pragma once

#include "gl.hpp"
#include "Program.hpp"

namespace omgl
{
  class Model
  {
    public:
    Model(const char* path);
    ~Model();

    private:
    GLuint vao, vbo, ebo;
  };
}