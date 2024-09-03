#pragma once

#ifdef _WIN32
  #define UNICODE
  #include <windows.h>
#else
  #error Not yet
#endif

#include <cstdint>
#include "Exception.hpp"

namespace omgl
{
  // A rather simple wrapper over OpenGL and whatever system window manager is used.
  // Any functions that are ascosiated with the context are included in the class.
  class Context
  {
    public:
    struct Event
    {
      enum class Type : uint8_t
      {
        _Null,

        Close,
        // Includes mouse keys
        Press, Release,
        MouseMove, // Moving the mouse
      };

      Type type;
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

    void (*event_handler) (Context&,const Event&) = DefaultEventHandler;

    // To use the Context you still need to call MakeCurrent().
    // Can throw a SystemException, with a code from the system.
    Context(unsigned width, unsigned height);
    ~Context();

    static void DefaultEventHandler(Context&,const Event&);

    // Make this context the used one, mandetory for it to work. Success gives true.
    bool MakeCurrent() const noexcept;
    // Swaps buffers :). Success gives true.
    bool SwapBuffers() const noexcept;

    // Not OpenGL, rather a window manager thing, handles queued up input and pipes to event_handler.
    void HandleEvents() noexcept;

    private:
    #ifdef _WIN32
      HWND hwnd = nullptr;
      HDC hdc = nullptr;
      HGLRC hglrc = nullptr;

      MSG msg;
    #endif

    Event event;

    // Handles the event variable after it is written
    void HandleEvent() noexcept;
  };
}