// Has some shared resources.

#pragma once

#include "gl.hpp"

namespace omgl
{
  constexpr unsigned INFO_LOG_SIZE = 512;
  
  // Used for the various glGetWhateverInfoLog()s
  extern thread_local GLchar info_log[INFO_LOG_SIZE];
}