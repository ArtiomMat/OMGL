#include "FileDriver.hpp"
#include "Exception.hpp"

#include <windows.h>

namespace omgl
{
  FileDriver::FileDriver()
  {
    // Copy the full EXE file path and remember where it ended
    exe_path_end = GetModuleFileName(NULL, exe_path, PATH_SIZE) - 1;

    // bool found_slash = 0;
    for (; exe_path_end >= 0; exe_path_end--)
    {
      if (exe_path[exe_path_end] == '\\' || exe_path[exe_path_end] == '/')
      {
        // found_slash = 1;
        exe_path[++exe_path_end] = 0;
        break;
      }
    }

    // TODO: If we didn't find a slash it means something went wrong, perhaps exe_path_end was =-1 to begin with
    // if (!found_slash)
    // {
    //   throw SystemException(GetLastError(), "Getting EXE's path failed.");
    // }
  }
}
