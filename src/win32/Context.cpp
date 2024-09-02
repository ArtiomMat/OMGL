#include <cstdio>


// To define GLenum and all the stuff we need
#include <GL.hpp>

#include "windows.hpp"
#include "Context.hpp"

namespace OMGL
{
  Context::Context(unsigned width, unsigned height)
  {
    constexpr DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

    constexpr wchar_t CLASS_NAME[] = L"OMGL CLASS";
    WNDCLASSW wc = { };
    wc.lpfnWndProc = DefWindowProcW;
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
    constexpr PIXELFORMATDESCRIPTOR pfd =
    {
      sizeof(PIXELFORMATDESCRIPTOR),
      1,
      PFD_DRAW_TO_WINDOW
        | PFD_SUPPORT_OPENGL
        | PFD_DOUBLEBUFFER,             // Flags
      PFD_TYPE_RGBA,                    // RGBA frame buffer.
      32,                               // Frambe buffer bps.
      0, 0, 0, 0, 0, 0,
      0,
      0,
      0,
      0, 0, 0, 0,
      24,                               // Depth buffer bps.
      8,                                // Stencil buffer bps.
      0,                                // No Aux buffers in the framebuffer.
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

  void Context::defaultEventHandler(Context& ctx, Context::Event& e)
  {
    switch (e.type)
    {
      case Context::EventType::Close:
      exit(0);
      break;

      default:
      break;
    }
  }

  void Context::handleEvent() noexcept
  {
    if (event.type != EventType::_Null)
    {
      if (eventHandler != nullptr)
      {
        eventHandler(*this, event);
      }
      else
      {
        defaultEventHandler(*this, event);
      }
    }
  }

  void Context::handleEvents() noexcept
  {
    event.type = EventType::_Null;

    // We handle the events we want to handle here because wndProc is an external
    // function and has no direct way for knowing the context itself.
    while (PeekMessageW(&msg, hWnd, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      switch (msg.message)
      {
        // This is just for me for I3 because it doesn't send WM_CLOSE for some reason!
        case WM_SYSCOMMAND:
        if (msg.wParam == SC_CLOSE)
        {
          event.type = EventType::Close;
          handleEvent();
        }
        break;
        case WM_CLOSE:
        event.type = EventType::Close;
        handleEvent();
        break;

        default:
        DispatchMessageW(&msg);
        return; // Because we dispatch in another case
      }
    }
  }

  bool Context::makeCurrent() noexcept
  {
    return wglMakeCurrent(hDC, hGLRC);
  }

  bool Context::swapBuffers() noexcept
  {
    return SwapBuffers(hDC);
  }

  Context::~Context()
  {
    ReleaseDC(hWnd, hDC);
    DestroyWindow(hWnd);
    wglDeleteContext(hGLRC);
  }
}