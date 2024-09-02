#include "ClockDriver.hpp"

namespace OMGL
{
  thread_local Time ClockDriver::beginFrameTime;

  unsigned long long ClockDriver::t0;

  thread_local Time ClockDriver::targetFrameTime = 16;
  thread_local Time ClockDriver::frameTime;

  void ClockDriver::reset()
  {
    beginFrameTime = now();
  }

  Time ClockDriver::sleepRemainder()
  {
    Time delta = now() - beginFrameTime;
    Time sleepTime = targetFrameTime - delta;

    if (sleepTime > 0)
    {
      sleep(sleepTime);
      frameTime = targetFrameTime;
      return sleepTime;
    }
    else
    {
      frameTime = delta; // The real tick time is just delta
    }

    beginFrameTime = now();

    return sleepTime;
  }
}
