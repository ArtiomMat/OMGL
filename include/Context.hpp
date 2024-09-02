#pragma once

#ifdef _WIN32
  #define UNICODE
  #include <windows.h>
#else
  #error Not yet
#endif

#include <cstdint>
#include "Exception.hpp"

namespace OMGL
{
  // A rather simple wrapper over OpenGL and whatever system window manager is used.
  // Any functions that are ascosiated with the context are included in the class.
  class Context
  {
    public:
    enum class EventType : uint8_t
    {
      _Null,

      Close,
      // Includes mouse keys
      Press, Release,
      MouseMove, // Moving the mouse
    };

    struct Event
    {
      EventType type;
      union
      {
        struct
        {
          int code;
        } press, release;
        struct
        {
          int x, y;
        } move;
      };
    };

    void (*eventHandler) (Context&,Event&) = defaultEventHandler;

    // To use the Context you still need to call makeCurrent().
    // Can throw a SystemException, with a code from the system.
    Context(unsigned width, unsigned height);
    ~Context();

    static void defaultEventHandler(Context&,Event&);

    // Make this context the used one, mandetory for it to work. Success gives true.
    bool makeCurrent() noexcept;
    // Swaps buffers :). Success gives true.
    bool swapBuffers() noexcept;

    // Not OpenGL, rather a window manager thing, handles queued up input and pipes to eventHandler.
    void handleEvents() noexcept;

    private:
    #ifdef _WIN32
      HWND hWnd = nullptr;
      HDC hDC = nullptr;
      HGLRC hGLRC = nullptr;

      MSG msg;
    #endif

    Event event;

    void handleEvent() noexcept;
  };
}