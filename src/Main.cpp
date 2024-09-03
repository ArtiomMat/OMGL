#include <cstdio>

#include <iostream>
#include <memory>
#include <exception>

#include "GL.hpp"
#include "ClockDriver.hpp"
#include "Context.hpp"
#include "Font.hpp"

int main()
{
  auto& clockDriver = omgl::ClockDriver::instance();

  omgl::Context ctx(300, 300);
  ctx.MakeCurrent();

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  while (1)
  {
    ctx.SwapBuffers();
    glClear(GL_COLOR_BUFFER_BIT);

    ctx.HandleEvents();

    clockDriver.SleepRemainder();
  }

  std::cout << "What\n";
  return 0;
}
