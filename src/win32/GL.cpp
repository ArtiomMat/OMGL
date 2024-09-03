#define _OMGL_SOURCE
#include "GL.hpp"

#include <GL/wgl.h>
#include <GL/wglext.h>

#include <string>

void* omglGetProcAddress(const char* str) noexcept
{
  // Code yoinked straight from Khronos OpenGL wiki with some modification
  void* p = (void*) wglGetProcAddress(str);
  if(p == nullptr)
  {
    HMODULE module = LoadLibraryA("opengl32.dll");
    p = (void*) GetProcAddress(module, str);
  }

  return p;
}

// 200+ IQ
template <typename T>
static void ThrowingGetProcAddress(T& f, const char* str)
{
  f = reinterpret_cast<T>(omglGetProcAddress(str));

  if (f == nullptr)
  {
    const char* msg = (std::string("Failed to load ") + str + ".").c_str();
    throw omgl::SystemException(0, msg);
  }
}

#define LOAD(S) ThrowingGetProcAddress(S, #S)

void omglGetAllProcAddresses()
{
  LOAD(glUseProgram);
  LOAD(glBindBuffer);
}