#include "gl.hpp"

#include <string>
#include <sstream>
#include <iostream>

#define LOAD(S) ThrowingGetProcAddress(S, #S)

// 200+ IQ
template <typename T>
static void ThrowingGetProcAddress(T& f, const char* str)
{
  f = reinterpret_cast<T>(omglGetProcAddress(str));

  if (f == nullptr)
  {
    std::string msg = (std::stringstream() << "Failed to load " << str << ".").str();
    throw omgl::SystemException(0, msg.c_str());
  }
}

void omglGetAllProcAddresses()
{
  LOAD(glBufferData);
  LOAD(glGenBuffers);
  LOAD(glBindBuffer);

  LOAD(glCreateShader);
  LOAD(glShaderSource);
  LOAD(glCompileShader);
  LOAD(glGetShaderiv);
  LOAD(glGetShaderInfoLog);
  LOAD(glAttachShader);
  LOAD(glDeleteShader);

  LOAD(glGenVertexArrays);
  LOAD(glBindVertexArray);
  // LOAD(glDrawArrays);
  LOAD(glVertexAttribPointer);
  LOAD(glEnableVertexAttribArray);
  LOAD(glDeleteVertexArrays);

  LOAD(glCreateProgram);
  LOAD(glLinkProgram);
  LOAD(glGetProgramInfoLog);
  LOAD(glGetProgramiv);
  LOAD(glGetProgramBinary);
  LOAD(glProgramBinary);
  LOAD(glUseProgram);
  LOAD(glDeleteProgram);
}
