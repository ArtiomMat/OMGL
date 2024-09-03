#pragma once

#include "gl.hpp"
#include "shared.hpp"
#include "Exception.hpp"

#include <memory>

namespace omgl
{
  // A rather simple wrapper for OpenGL shaders.
  class Shader
  {
    public:
    enum class Type
    {
      Vertex,
      Fragment,
      Geometry,
      Compute,
    };

    // Same as extended constructor just without success return.
    Shader(const char* path, Type type) : Shader(path, type, nullptr) {}
    // Loads, and compiles the shader. Same throwing and error handling as Reload().
    // success can be nullptr.
    Shader(const char* path, Type type, bool* success);
    ~Shader();

    // Reloads the shader by compiling and doing everything once more. Throws FileException variants. Upon compilation error logs it out to the thread_local info_log. Return is compilation success.
    bool Reload();

    private:
    GLuint id = 0;

    std::unique_ptr<char[]> path;
  };
}
