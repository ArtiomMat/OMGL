#pragma once

namespace OMGL
{
  class Context
  {
    public:
    // Can throw a SystemException, with a code from the system.
    Context(unsigned width, unsigned height);
    ~Context();

    // Make this context the used one, mandetory for it to work.
    void makeCurrent();

    void swapBuffers();
  };
}