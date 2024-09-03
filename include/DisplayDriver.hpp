// The driver that handles display stuff, the basis for Window
#pragma once

namespace OMGL
{
  class DisplayDriver
  {
    public:
    DisplayDriver(DisplayDriver&) = delete;
    void operator=(const DisplayDriver&) = delete;
    
    unsigned refreshRate;
    union
    {
      struct
      {
        unsigned width, height;
      };
      unsigned size[2];
    };

    static DisplayDriver& instance()
    {
      static DisplayDriver i;
      return i;
    }

    private:
    DisplayDriver();
    ~DisplayDriver();
  };
}
