#pragma once

#include "gl.hpp"
#include "shared.hpp"
#include "Exception.hpp"

#include <memory>

namespace omgl
{
  class Program;

  // A rather simple wrapper for OpenGL shaders.
  class Shader
  {
    friend class Program;

    public:
    enum class Type
    {
      Vertex,
      Fragment,
      Geometry,
      Compute,
    };

    // Same as extended constructor just without success return. Throws SystemException if shader fails code is glGetError().
    Shader(const char* path, Type type) : Shader(path, type, nullptr) {}
    // Loads, and compiles the shader. Same throwing and error handling as Reload().
    // success can be nullptr.
    Shader(const char* path, Type type, bool* success);
    ~Shader();

    // Reloads the shader by compiling and doing everything once more. If the shader is attached to a Program object and reloads successfully then it is reattached automatically. Throws FileException variants. Upon compilation error logs it out to the thread_local info_log. Return is compilation success.
    bool Reload();

    private:
    GLuint id = 0;
    GLuint program_id = 0;

    std::unique_ptr<char[]> path;
  };
}
