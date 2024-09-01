#pragma once

#ifdef _WIN32
  #define UNICODE
  #include <windows.h>
#else
  #error Not yet
#endif

#include "Exception.hpp"

namespace OMGL
{
  // A wrapper over OpenGL and whatever system window manager is used. This is not a lightweight wrapper.
  class Context
  {
    public:
    // To use the Context you still need to call makeCurrent().
    // Can throw a SystemException, with a code from the system.
    Context(unsigned width, unsigned height);
    ~Context();

    // Make this context the used one, mandetory for it to work.
    void makeCurrent();

    void swapBuffers();

    private:
    #ifdef _WIN32
      MSG msg;
      HWND hWnd = nullptr;
      HDC hDC = nullptr;
      HGLRC hGLRC = nullptr;
    #endif
  };
}