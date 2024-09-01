#include <cstdio>

#include <exception>

#include "Context.hpp"
#include "Font.hpp"

int main()
{
  throw OMGL::Exception("lol");
  try
  {
    OMGL::Context ctx(300, 300);
  }
  catch (OMGL::SystemException& s)
  {
    puts(s.str);
  }
  puts("What");
  return 0;
}
