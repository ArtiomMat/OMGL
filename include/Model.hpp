#pragma once

#include "gl.hpp"

namespace omgl
{
  class Model
  {
    public:
    Model(const char* path);
    ~Model();

    GLuint vab, eab;
  };
}