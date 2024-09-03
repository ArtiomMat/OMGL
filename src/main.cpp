#include <cstdio>

#include <iostream>
#include <memory>
#include <exception>

#include "gl.hpp"
#include "ClockDriver.hpp"
#include "Context.hpp"
#include "Font.hpp"

static bool run_loop = true;

static void EventHandler(omgl::Context&, const omgl::Context::Event& e)
{
  switch (e.type)
  {
    case omgl::Context::Event::Type::Close:
    run_loop = false;
    break;

    default:
    break;
  }
}

// The whole rendering routine here
static inline void RenderBackBuffer()
{
  glClear(GL_COLOR_BUFFER_BIT);
}

int main()
{
  auto& clockDriver = omgl::ClockDriver::instance();

  omgl::Context ctx(300, 300);
  ctx.MakeCurrent();
  ctx.event_handler = EventHandler;

  omglGetAllProcAddresses();
  
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  while (run_loop)
  {
    ctx.HandleEvents();

    RenderBackBuffer();
    ctx.SwapBuffers();

    clockDriver.SleepRemainder();
  }

  return 0;
}
