#define _OMGL_SOURCE
#include "GL.hpp"

#include <GL/wgl.h>
#include <GL/wglext.h>

#include "windows.hpp"

#include <iostream>

void* omglGetProcAddress(const char* str) noexcept
{
  // Code yoinked straight from Khronos OpenGL wiki with some modification
  void* p = (void*) wglGetProcAddress(str);
  if(p == nullptr)
  {
    HMODULE module = LoadLibraryW(L"opengl32.dll");
    p = (void*) GetProcAddress(module, str);
  }

  return p;
}