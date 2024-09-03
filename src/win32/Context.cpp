#include <cstdio>


// To define GLenum and all the stuff we need
#include "gl.hpp"
#include "windows.hpp"
#include "Context.hpp"
#include <iostream>

namespace omgl
{
  Context::Context(unsigned width, unsigned height)
  {
    constexpr DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

    constexpr wchar_t CLASS_NAME[] = L"OMGL CLASS";
    WNDCLASSW wc = { };
    wc.lpfnWndProc = DefWindowProcW;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = CLASS_NAME;

    if (!RegisterClassW(&wc))
    {
      throw SystemException(GetLastError(), "Registering class.");
    }

    // Calculate full window size given desired client-area size
    RECT rect{
      .left = 0,
      .top = 0,
      .right = static_cast<LONG>(width),
      .bottom = static_cast<LONG>(height),
    };
    AdjustWindowRect(&rect, style, false);
    unsigned real_width = rect.right - rect.left;
    unsigned real_height = rect.bottom - rect.top;

    hwnd = CreateWindowExW(
      0,
      CLASS_NAME,
      L"OMGL",
      style,

      CW_USEDEFAULT, CW_USEDEFAULT,
      real_width, real_height,

      nullptr,
      nullptr,
      GetModuleHandle(nullptr),
      nullptr
    );
    if (hwnd == nullptr)
    {
      throw SystemException(GetLastError(), "Creating window.");
    }

    ShowWindow(hwnd, SW_SHOWNORMAL);

    hdc = GetDC(hwnd);

    // Now for the OpenGL part
    constexpr PIXELFORMATDESCRIPTOR pfd =
    {
      sizeof(PIXELFORMATDESCRIPTOR),
      1,
      PFD_DRAW_TO_WINDOW                // Flags
      | PFD_SUPPORT_OPENGL
      | PFD_DOUBLEBUFFER,
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

    int pf = ChoosePixelFormat(hdc, &pfd);
    if (!pf)
    {
      throw SystemException(GetLastError(), "Choosing pixel format.");
    }

    if (!SetPixelFormat(hdc, pf, &pfd))
    {
      throw SystemException(GetLastError(), "Setting pixel format.");
    }

    hglrc = wglCreateContext(hdc);
    if (hglrc == nullptr)
    {
      throw SystemException(GetLastError(), "Creating context.");
    }
  }

  void Context::DefaultEventHandler(Context&, const Context::Event& e)
  {
    switch (e.type)
    {
      case Context::Event::Type::Close:
      std::cout << "Close event, exitting...\n";
      exit(0);
      break;

      default:
      break;
    }
  }

  void Context::HandleEvent() noexcept
  {
    if (event.type != Event::Type::_Null)
    {
      if (event_handler != nullptr)
      {
        event_handler(*this, event);
      }
      else
      {
        DefaultEventHandler(*this, event);
      }
    }
  }

  void Context::HandleEvents() noexcept
  {
    event.type = Event::Type::_Null;

    // We handle the events we want to handle here because wndProc is an external
    // function and has no direct way for knowing the context itself.
    while (PeekMessageW(&msg, hwnd, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      switch (msg.message)
      {
        // This is just for me for I3 because it doesn't send WM_CLOSE for some reason!
        case WM_SYSCOMMAND:
        if (msg.wParam == SC_CLOSE)
        {
          event.type = Event::Type::Close;
          HandleEvent();
        }
        break;
        case WM_CLOSE:
        event.type = Event::Type::Close;
        HandleEvent();
        break;

        default:
        DispatchMessageW(&msg);
        return; // Because we dispatch in another case
      }
    }
  }

  bool Context::MakeCurrent() const noexcept
  {
    return wglMakeCurrent(hdc, hglrc);
  }

  bool Context::SwapBuffers() const noexcept
  {
    return ::SwapBuffers(hdc);
  }

  Context::~Context()
  {
    ReleaseDC(hwnd, hdc);
    DestroyWindow(hwnd);
    wglDeleteContext(hglrc);
  }
}