#include <cstdio>

#include <exception>

#include "Context.hpp"
#include "Font.hpp"

int main()
{
  try
  {
    OMGL::Context ctx(300, 300);
    ctx.makeCurrent();
    while(1) {ctx.swapBuffers(); Sleep(100);}
  }
  catch (OMGL::SystemException& s)
  {
    puts(s.str);
  }
  puts("What");
  return 0;
}
