#include "Buffers.hpp"

namespace omgl
{
  Buffers::Buffers(unsigned _n, unsigned _buffer_size) : buffer_size(_buffer_size), n(_n)
  {
    glGenBuffers(n, &id);
  }

  void Buffers::Bind(Buffers::Target target)
  {
    GLenum gl_target;
    switch (target)
    {
      case Buffers::Target::Array:
      gl_target = GL_ARRAY_BUFFER;
      break;
      case Buffers::Target::ElementArray:
      gl_target = GL_ELEMENT_ARRAY_BUFFER;
      break;
      case Buffers::Target::Unifom:
      gl_target = GL_UNIFORM_BUFFER;
      break;
    }

    glBindBuffer(gl_target, id);
  }

  Buffers::~Buffers()
  {
    glDeleteBuffers(n, &id);
  }
}