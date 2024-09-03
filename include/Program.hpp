#pragma once

#include "gl.hpp"

namespace omgl
{
  class Shader;
  
  class Program
  {
    friend class Shader;
    public:
    Program();
    ~Program();

    void AttachShader(const Shader& s);
    // Links only if any changes have been made to the shaders attached. This logic exists for potentially more complex logic and relationship between Program and Shader, for now it's not something big.
    // Upon linking error logs it out to the thread_local info_log. Return is linking success.
    bool Link();
    void Use();
    
    private:
    // Whether or not has been linked after 
    bool linked = false;
    GLint id = 0;
  };
}