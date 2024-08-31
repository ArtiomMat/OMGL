#include <cstdio>

#include "DisplayDriver.hpp"
#include "Font.hpp"

int main()
{
  try
  {
    OMGL::Font f("lol");
  }
  catch (...)
  {
    puts("Error!");
  }
  puts("What");
  return 0;
}
