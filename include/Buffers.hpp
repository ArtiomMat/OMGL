#pragma once

#include "gl.hpp"

#include <memory>
#include <cstdint>

namespace omgl
{
  // A lightweight wrapper for the OpenGL buffers as in glGenBuffers
  class Buffers
  {
    public:

    enum class Target : uint8_t
    {
      Array,        // GL_ARRAY_BUFFER
      ElementArray, // GL_ELEMENT_ARRAY_BUFFER
      Unifom,       // GL_UNIFORM_BUFFER
    };
    
    enum class Usage : uint8_t
    {
      StreamDraw,  // GL_STREAM_DRAW
      StaticDraw,  // GL_STATIC_DRAW
      DynamicDraw, // GL_DYNAMIC_DRAW
    };
    
    // n is the number of buffers, buffer_size is the size of each buffer.
    Buffers(unsigned n, unsigned buffer_size);
    ~Buffers();

    // Make sure that it happens after you binded the vertex array.
    void Bind(Target t);

    // Gotta be called after Bind(), a wrapper for glBufferData(). Unique ptr is used because I ain't allowing segfault out in this b. The size of the buffer obviously must be buffer_size.
    void set_data_buffer(std::unique_ptr<char[]> data_buffer);
    // That's it the buffer is yours
    std::unique_ptr<char[]> data_buffer() { return std::move(m_data_buffer); }
    // Get a pointer to the internal buffer, it's what you setup previously
    // const char* data_buffer_peek() { return m_data_buffer.get(); }

    unsigned buffer_size() const { return m_buffer_size; }

    private:
    unsigned m_buffer_size;
    std::unique_ptr<char[]> m_data_buffer;

    unsigned n;
    GLuint id;
  };

  // Literally zero-cost wrapper for Buffers to represent a single buffer.
  class Buffer : Buffers
  {
    public:
    // Check out Buffers, and assume n=1
    inline Buffer(unsigned buffer_size) : Buffers(1, buffer_size) {}
  };
}
