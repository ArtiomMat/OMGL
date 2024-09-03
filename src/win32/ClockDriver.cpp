#include "ClockDriver.hpp"

#include <windows.h>

namespace omgl
{
  ClockDriver::ClockDriver()
  {
    t0 = GetTickCount64();
  }

  Time ClockDriver::now()
  {
    return static_cast<Time>(GetTickCount64() - t0);
  }
  
  void ClockDriver::Sleep(Time t)
  {
    ::Sleep(t);
  }
}
