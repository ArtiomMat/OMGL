#include <cstdio>


// To define GLenum and all the stuff we need
#include <GL.hpp>

#include <GL/wgl.h>
#include <GL/wglext.h>

#define UNICODE
#include <windows.h>

#include "Context.hpp"

namespace OMGL
{
  static LRESULT CALLBACK wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
  {
    return DefWindowProcW(hWnd, uMsg, wParam, lParam);
  }

  Context::Context(unsigned width, unsigned height)
  {
    constexpr DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;

    constexpr wchar_t CLASS_NAME[] = L"OMGL CLASS";
    WNDCLASSW wc = { };
    wc.lpfnWndProc = wndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;

    if (!RegisterClassW(&wc))
    {
      throw SystemException(GetLastError(), "Registering class.");
    }

    hWnd = CreateWindowExW(
      0,
      CLASS_NAME,
      L"OMGL",
      style,

      0,0, width, height,

      NULL,
      NULL,
      GetModuleHandle(NULL),
      NULL
    );
    if (hWnd == nullptr)
    {
      throw SystemException(GetLastError(), "Creating window.");
    }

    ShowWindow(hWnd, SW_SHOWNORMAL);

    hDC = GetDC(hWnd);

    // Now for the OpenGL part
    PIXELFORMATDESCRIPTOR pfd =
    {
      sizeof(PIXELFORMATDESCRIPTOR),
      1,
      PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
      PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
      32,                   // Colordepth of the framebuffer.
      0, 0, 0, 0, 0, 0,
      0,
      0,
      0,
      0, 0, 0, 0,
      24,                   // Number of bits for the depthbuffer
      8,                    // Number of bits for the stencilbuffer
      0,                    // Number of Aux buffers in the framebuffer.
      PFD_MAIN_PLANE,
      0,
      0, 0, 0
    };

    int pf = ChoosePixelFormat(hDC, &pfd);
    if (!pf)
    {
      throw SystemException(GetLastError(), "Choosing pixel format.");
    }

    if (!SetPixelFormat(hDC, pf, &pfd))
    {
      throw SystemException(GetLastError(), "Setting pixel format.");
    }

    hGLRC = wglCreateContext(hDC);
    if (hGLRC == nullptr)
    {
      throw SystemException(GetLastError(), "Creating context.");
    }
  }

  void Context::makeCurrent()
  {
    wglMakeCurrent(hDC, hGLRC);
  }

  void Context::swapBuffers()
  {
    SwapBuffers(hDC);
  }

  Context::~Context()
  {
    wglDeleteContext(hGLRC);
  }
}