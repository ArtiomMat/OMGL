#include <cstdio>

#include <exception>

#include "ClockDriver.hpp"

#include "Context.hpp"
#include "Font.hpp"

int main()
{
  auto& clockDriver = OMGL::ClockDriver::instance();

  try
  {
    OMGL::Context ctx(300, 300);
    ctx.makeCurrent();
    while (1)
    {
      ctx.swapBuffers();
      ctx.handleEvents();
      clockDriver.sleepRemainder();
    }
  }
  catch (OMGL::SystemException &s)
  {
    puts(s.str);
  }
  puts("What");
  return 0;
}
